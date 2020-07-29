#ifndef AUTOCORRECT_APPROXSEARCH_HH
#define AUTOCORRECT_APPROXSEARCH_HH

#include <fstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include "../common/DumpableNode.hh"

/**
 * @brief displays all the words at a certain distance of the requested word
 *
 * given the word, the distance and a stream of the binary file containing
 * the dictionary, goes through the dictionary, uses the damerau-
 * levenshtein algorithm to determine if a word is at a certain distance
 * of the request and adds it to a lists of words which are then displayed
 * on the standard output.
 *
 * @param is the stream of the dictionary
 * @param request the word we want to approximate
 * @param max_distance the distance of approximation
 */
void approx_search(std::ifstream &is, std::string request, int max_distance);

#endif //AUTOCORRECT_APPROXSEARCH_HH
