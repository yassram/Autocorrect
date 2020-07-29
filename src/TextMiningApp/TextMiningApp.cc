#include <iostream>
#include <string>
#include "ApproxSearch.hh"

int main(int argc, char const *argv[])
{
    if (argc != 2){
        std::cerr << "Usage: ./TextMiningApp /path/to/dict.bin" << std::endl;
        return 1;
    }

    std::ifstream is(argv[1], std::ios::binary);
    std::string cmd;
    std::string request;
    int distance;
    while(is.is_open()) {
        std::cin >> cmd;
        if (cmd != "approx" )
            break;
        std::cin >> distance;
        std::cin >> request;
        approx_search(is, request, distance);
        is.seekg(0);
        cmd = "";
    }

	return 0;
}
