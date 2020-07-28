#ifndef AUTOCORRECT_DUMPABLENODE_HH
#define AUTOCORRECT_DUMPABLENODE_HH

#include <iostream>

struct DumpableNode {
    size_t children_number;
    char value;
    int frequency;
    size_t offset;
} __attribute__ ((packed));

#endif //AUTOCORRECT_DUMPABLENODE_HH
