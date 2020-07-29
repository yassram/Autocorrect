#ifndef AUTOCORRECT_DUMPABLENODE_HH
#define AUTOCORRECT_DUMPABLENODE_HH

#include <iostream>

/**
 * @class DumpableNode
 *
 * @brief used to group elements that are to be compiled in dictionary
 */
struct DumpableNode {
    size_t children_number; /**< the number of children of the node */
    char value; /**< the character value contained in the node */
    int frequency; /**< if a word is formed, its frequency of apparition */
    size_t offset; /**< offset at the end of its children */
} __attribute__ ((packed));

#endif //AUTOCORRECT_DUMPABLENODE_HH
