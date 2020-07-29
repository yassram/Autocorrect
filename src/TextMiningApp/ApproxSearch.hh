#ifndef AUTOCORRECT_APPROXSEARCH_HH
#define AUTOCORRECT_APPROXSEARCH_HH

#include <fstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include "../common/DumpableNode.hh"

///
/// \param is
/// \param value
/// \param maxDistance
void approx_search(std::ifstream &is, std::string value, int maxDistance);

#endif //AUTOCORRECT_APPROXSEARCH_HH
