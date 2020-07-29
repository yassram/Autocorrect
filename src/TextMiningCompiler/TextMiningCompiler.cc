#include <iostream>
#include "Trie.hh"
#include "TrieFactory.hh"

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin" << std::endl;
        return 1;
    }

    Trie *root = build(argv[1]);
    dump_to_disk(*root, argv[2]);

    delete root;
    return 0;
}
