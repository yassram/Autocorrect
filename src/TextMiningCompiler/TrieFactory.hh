#ifndef AUTOCORRECT_TRIEFACTORY_HH
#define AUTOCORRECT_TRIEFACTORY_HH

#include <string>
#include <fstream>
#include "Trie.hh"
#include "../common/DumpableNode.hh"

Trie* build(std::string pathToFile);

void dumpToDisk(const Trie &trie, std::string binaryPath);

#endif //AUTOCORRECT_TRIEFACTORY_HH
