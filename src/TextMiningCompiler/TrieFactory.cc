#include "TrieFactory.hh"

Trie* build(std::string pathToFile) {
    std::ifstream file;
    file.open(pathToFile);
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

size_t dumpToDisk(std::ofstream &binaryFile, const Trie &trie, char value) {
    auto children = trie.getChildren();
    size_t offset = 0;

    struct DumpableNode node;
    node.children_number = children.size();
    node.value = value;
    node.frequency = trie.getFrequency();
    node.offset = offset;

    const char *buffer = (char*)(&node);
    binaryFile.write(buffer, sizeof(struct DumpableNode));
    long offset_position = (long)binaryFile.tellp() - sizeof(size_t);

    for(auto it = children.begin(); it != children.end(); ++it) {
        offset += dumpToDisk(binaryFile, *(it->second), it->first);
    }

    long end = binaryFile.tellp();
    binaryFile.seekp(offset_position);
    binaryFile.write((char*)(&offset), sizeof(size_t));
    binaryFile.seekp(end);

    return sizeof(struct DumpableNode) + offset;
}

void dumpToDisk(const Trie &trie, std::string binaryPath) {
    std::ofstream binaryFile(binaryPath, std::ios::binary);
    if (binaryFile.is_open())
        dumpToDisk(binaryFile, trie, '\0');
    binaryFile.close();
}