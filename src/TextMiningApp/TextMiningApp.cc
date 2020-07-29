#include <iostream>
#include <string>
#include <sstream>
#include "ApproxSearch.hh"

int main(int argc, char const *argv[])
{
    if (argc != 2){
        std::cerr << "Usage: ./TextMiningApp /path/to/dict.bin" << std::endl;
        return 1;
    }

    std::ifstream is(argv[1], std::ios::binary);
    std::string request;
    std::cin >> request;
    while(request == "approx" && is.is_open())
    {
        std::cin >> request;
        int distance;
        std::istringstream iss(request);
        iss >> distance;
        if (iss.fail())
            return 0;
        std::cin >> request;
        approx_search(is, request, distance);
        is.seekg(0);

        std::cin >> request;
    }

	return 0;
}