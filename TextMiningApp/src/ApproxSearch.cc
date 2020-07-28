#include "ApproxSearch.hh"

void display_results(std::vector<std::tuple<std::string, int, int>> *results);

void damerau_levenshtein(std::vector<int> *currentRow,
                         struct DumpableNode *node,
                         std::string request,
                         int maxDistance,
                         std::vector<int> previousRow,
                         std::vector<int> prePreviousRow,
                         std::vector<std::tuple<std::string, int, int>> *results,
                         std::string prefix) {

    int columns = request.length() + 1;
    (*currentRow)[0] = previousRow[0] + 1;

    for (int column = 1; column < columns; column++) {
        int insertCost = (*currentRow)[column - 1] + 1;
        int deleteCost = previousRow[column] + 1;
        int replaceCost;

        if (request[column - 1] != prefix.back())
            replaceCost = previousRow[column - 1] + 1;
        else
            replaceCost = previousRow[column - 1];

        (*currentRow)[column] = std::min({insertCost, deleteCost, replaceCost});

        if (prefix.length() != 1 && column > 1 && prefix.back() == request[column - 2] &&
            prefix[prefix.length()-2] == request[column - 1] && request[column - 1] != prefix.back()) {
            (*currentRow)[column] = std::min((*currentRow)[column], prePreviousRow[column - 2] + 1);
        }
    }

    if ((*currentRow)[request.length()] <= maxDistance && node->frequency > 0)
        results->push_back(std::make_tuple(prefix, node->frequency, (*currentRow)[request.length()]));
}


void approx_search_on_ram(struct DumpableNode *node,
                           std::string request,
                           int maxDistance,
                           std::vector<int> previousRow,
                           std::vector<int> prePreviousRow,
                           std::vector<std::tuple<std::string, int, int>> *results,
                           std::string prefix) {

    int columns = request.length() + 1;
    std::vector<int> currentRow(columns);

    damerau_levenshtein(&currentRow, node, request, maxDistance, previousRow,
                        prePreviousRow, results, prefix);

    if (*std::min_element(currentRow.begin(), currentRow.end()) <= maxDistance) {
        struct DumpableNode *sub_trie = node + 1;
        struct DumpableNode *current_child;
        size_t next_child_offset = 0;
        for (size_t i = 0; i < node->children_number; i++) {
            current_child = sub_trie + next_child_offset;
            std::string new_prefix = prefix;
            new_prefix.append(1, current_child->value);
            approx_search_on_ram(current_child, request, maxDistance, currentRow, previousRow,
                                 results, new_prefix);
            next_child_offset += 1 + current_child->offset / sizeof(struct DumpableNode);
        }
    }
}


void approx_search_on_disk(std::ifstream &is,
                     struct DumpableNode *node,
                     std::string request,
                     int maxDistance,
                     std::vector<int> previousRow,
                     std::vector<int> prePreviousRow,
                     std::vector<std::tuple<std::string, int, int>> *results,
                     std::string prefix) {
    int columns = request.length() + 1;
    std::vector<int> currentRow(columns);

    damerau_levenshtein(&currentRow, node, request, maxDistance, previousRow,
                        prePreviousRow, results, prefix);

    if (*std::min_element(currentRow.begin(), currentRow.end()) <= maxDistance) {
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
                approx_search_on_ram(current_child, request, maxDistance, currentRow, previousRow,
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
                approx_search_on_disk(is, &child, request, maxDistance, currentRow, previousRow,
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

void approx_search(std::ifstream &is, std::string request, int maxDistance) {
    std::vector<int> currentRow(request.length() + 1);
    std::iota(std::begin(currentRow), std::end(currentRow), 0);

    std::vector<std::tuple<std::string, int, int>> *results = new std::vector<std::tuple<std::string, int, int>>();

    struct DumpableNode root;
    is.read((char *) &root, sizeof(struct DumpableNode));

    for (size_t i = 0; i < root.children_number; i++){
        struct DumpableNode child;
        is.read((char *) &child, sizeof(struct DumpableNode));

        size_t pos = is.tellg();
        std::string prefix;
        prefix.append(1, child.value);
        approx_search_on_disk(is, &child, request, maxDistance, currentRow,
                        currentRow, results, prefix);
        is.seekg (pos + child.offset);
    }

    display_results(results);

    delete results;
}


