#include "ApproxSearch.hh"

void display_results(std::vector<std::tuple<std::string, int, int>> *results);

void damerau_levenshtein(std::vector<int> *current_row,
                         struct DumpableNode *node,
                         std::string request,
                         int max_distance,
                         std::vector<int> previous_row,
                         std::vector<int> pre_previous_row,
                         std::vector<std::tuple<std::string, int, int>> *results,
                         std::string prefix) {

    int columns = request.length() + 1;
    (*current_row)[0] = previous_row[0] + 1;

    for (int column = 1; column < columns; column++) {
        int insert_cost = (*current_row)[column - 1] + 1;
        int delete_cost = previous_row[column] + 1;
        int replace_cost;

        if (request[column - 1] != prefix.back())
            replace_cost = previous_row[column - 1] + 1;
        else
            replace_cost = previous_row[column - 1];

        (*current_row)[column] = std::min({insert_cost, delete_cost, replace_cost});

        if (prefix.length() != 1 && column > 1 && prefix.back() == request[column - 2] &&
            prefix[prefix.length()-2] == request[column - 1] && request[column - 1] != prefix.back()) {
            (*current_row)[column] = std::min((*current_row)[column], pre_previous_row[column - 2] + 1);
        }
    }

    auto frequency = node->frequency;
    if ((*current_row)[request.length()] <= max_distance && node->frequency > 0)
        results->push_back(std::make_tuple(prefix, frequency, (*current_row)[request.length()]));
}


void approx_search_on_ram(struct DumpableNode *node,
                           std::string request,
                           int max_distance,
                           std::vector<int> previous_row,
                           std::vector<int> pre_previous_row,
                           std::vector<std::tuple<std::string, int, int>> *results,
                           std::string prefix) {

    int columns = request.length() + 1;
    std::vector<int> current_row(columns);

    damerau_levenshtein(&current_row, node, request, max_distance, previous_row,
                        pre_previous_row, results, prefix);

    if (*std::min_element(current_row.begin(), current_row.end()) <= max_distance) {
        struct DumpableNode *sub_trie = node + 1;
        struct DumpableNode *current_child;
        size_t next_child_offset = 0;
        for (size_t i = 0; i < node->children_number; i++) {
            current_child = sub_trie + next_child_offset;
            std::string new_prefix = prefix;
            new_prefix.append(1, current_child->value);
            approx_search_on_ram(current_child, request, max_distance, current_row, previous_row,
                                 results, new_prefix);
            next_child_offset += 1 + current_child->offset / sizeof(struct DumpableNode);
        }
    }
}


void approx_search_on_disk(std::ifstream &is,
                     struct DumpableNode *node,
                     std::string request,
                     int max_distance,
                     std::vector<int> previous_row,
                     std::vector<int> pre_previous_row,
                     std::vector<std::tuple<std::string, int, int>> *results,
                     std::string prefix) {
    int columns = request.length() + 1;
    std::vector<int> current_row(columns);

    damerau_levenshtein(&current_row, node, request, max_distance, previous_row,
                        pre_previous_row, results, prefix);

    if (*std::min_element(current_row.begin(), current_row.end()) <= max_distance) {
        if (node->offset < 8*1024*1024) {
            size_t nb_sub_trie = node->offset / sizeof(struct DumpableNode);
            struct DumpableNode sub_trie[nb_sub_trie];
            is.read((char*)sub_trie, node->offset);

            struct DumpableNode *current_child;
            size_t next_child_offset = 0;
            for (size_t i = 0; i < node->children_number; i++) {
                current_child = sub_trie + next_child_offset;
                std::string new_prefix = prefix;
                new_prefix.append(1, current_child->value);
                approx_search_on_ram(current_child, request, max_distance, current_row, previous_row,
                                      results, new_prefix);
                next_child_offset += 1 + current_child->offset / sizeof(struct DumpableNode);
            }
        } else {
            for (size_t i = 0; i < node->children_number; i++) {
                struct DumpableNode child;
                is.read((char *) &child, sizeof(struct DumpableNode));

                size_t pos = is.tellg();
                std::string new_prefix = prefix;
                new_prefix.append(1, child.value);
                approx_search_on_disk(is, &child, request, max_distance, current_row, previous_row,
                                results, new_prefix);
                is.seekg(pos + child.offset);
            }
        }
    }
}


bool sort_result(std::tuple<std::string, int, int> tuple1,
                 std::tuple<std::string, int, int> tuple2){
    if (std::get<2>(tuple1) != std::get<2>(tuple2))
        return std::get<2>(tuple1) < std::get<2>(tuple2);
    if (std::get<1>(tuple1) != std::get<1>(tuple2))
        return std::get<1>(tuple1) > std::get<1>(tuple2);
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

void display_results(std::vector<std::tuple<std::string, int, int>> *results) {
    std::sort(results->begin(), results->end(), sort_result);
    std::cout << "[";
    for(auto it = results->begin(); it != results->end(); ++it)
    {
        if (it != results->begin())
            std::cout << ",";
        std::cout << "{";
        std::cout << "\"word\":\"" << std::get<0>(*it) << "\",";
        std::cout << "\"freq\":" << std::get<1>(*it) << ",";
        std::cout << "\"distance\":" << std::get<2>(*it);
        std::cout << "}";
    }
    std::cout << "]" << std::endl;
}

void approx_search(std::ifstream &is, std::string request, int max_distance) {
    std::vector<int> current_row(request.length() + 1);
    std::iota(std::begin(current_row), std::end(current_row), 0);

    std::vector<std::tuple<std::string, int, int>> *results = new std::vector<std::tuple<std::string, int, int>>();

    struct DumpableNode root;
    is.read((char *) &root, sizeof(struct DumpableNode));

    for (size_t i = 0; i < root.children_number; i++){
        struct DumpableNode child;
        is.read((char *) &child, sizeof(struct DumpableNode));

        size_t pos = is.tellg();
        std::string prefix;
        prefix.append(1, child.value);
        approx_search_on_disk(is, &child, request, max_distance, current_row,
                        current_row, results, prefix);
        is.seekg (pos + child.offset);
    }

    display_results(results);

    delete results;
}


