#include "TrieFactory.hh"

Trie* build(std::string path_to_file) {
    std::ifstream file;
    file.open(path_to_file);
    if (!file.is_open())
        return NULL;

    std::string word;
    std::string frequency;

    Trie *root = new Trie();
    while (file >> word) {
        file >> frequency;
        root->insert(word, std::stoi(frequency));
    }
    return root;
}

size_t dump_to_disk(std::ofstream &binary_file, const Trie &trie, char value) {
    auto children = trie.get_children();
    size_t offset = 0;

    struct DumpableNode node;
    node.children_number = children.size();
    node.value = value;
    node.frequency = trie.get_frequency();
    node.offset = offset;

    const char *buffer = (char*)(&node);
    binary_file.write(buffer, sizeof(struct DumpableNode));
    long offset_position = (long)binary_file.tellp() - sizeof(size_t);

    for(auto it = children.begin(); it != children.end(); ++it) {
        offset += dump_to_disk(binary_file, *(it->second), it->first);
    }

    long end = binary_file.tellp();
    binary_file.seekp(offset_position);
    binary_file.write((char*)(&offset), sizeof(size_t));
    binary_file.seekp(end);

    return sizeof(struct DumpableNode) + offset;
}

void dump_to_disk(const Trie &trie, std::string binary_path) {
    std::ofstream binary_file(binary_path, std::ios::binary);
    if (binary_file.is_open())
        dump_to_disk(binary_file, trie, '\0');
    binary_file.close();
}
