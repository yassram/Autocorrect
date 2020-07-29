#ifndef AUTOCORRECT_TRIEFACTORY_HH
#define AUTOCORRECT_TRIEFACTORY_HH

#include <string>
#include <fstream>
#include "Trie.hh"
#include "../common/DumpableNode.hh"

///
/// \param pathToFile
/// \return
Trie* build(std::string pathToFile);

/// 
/// \param trie
/// \param binaryPath
void dumpToDisk(const Trie &trie, std::string binaryPath);

#endif //AUTOCORRECT_TRIEFACTORY_HH
