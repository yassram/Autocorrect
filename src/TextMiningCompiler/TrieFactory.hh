#ifndef AUTOCORRECT_TRIEFACTORY_HH
#define AUTOCORRECT_TRIEFACTORY_HH

#include <string>
#include <fstream>
#include "Trie.hh"
#include "../common/DumpableNode.hh"

/**
 * @brief given a dictionary of words, builds the corresponding trie
 *
 * @param pathToFile the path of the dictionary file
 * @return the corresponding trie
 */
Trie* build(std::string pathToFile);

/**
 * @brief maps the trie into a binary file on the disk
 *
 * @param trie the trie we want to dump on the disk
 * @param binaryPath the name of the binary file we want to create
 */
void dumpToDisk(const Trie &trie, std::string binaryPath);

#endif //AUTOCORRECT_TRIEFACTORY_HH
