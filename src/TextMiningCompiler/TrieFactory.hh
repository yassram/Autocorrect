#ifndef AUTOCORRECT_TRIEFACTORY_HH
#define AUTOCORRECT_TRIEFACTORY_HH

#include <string>
#include <fstream>
#include "Trie.hh"
#include "../common/DumpableNode.hh"

/**
 * @brief given a dictionary of words, builds the corresponding trie
 *
 * @param path_to_file the path of the dictionary file
 * @return the corresponding trie
 */
Trie* build(std::string path_to_file);

/**
 * @brief maps the trie into a binary file on the disk
 *
 * @param trie the trie we want to dump on the disk
 * @param binary_path the name of the binary file we want to create
 */
void dump_to_disk(const Trie &trie, std::string binary_path);

#endif //AUTOCORRECT_TRIEFACTORY_HH
