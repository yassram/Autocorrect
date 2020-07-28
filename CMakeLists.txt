cmake_minimum_required(VERSION 3.14)

project(Autocorrect)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")

add_executable(TextMiningCompiler
        TextMiningCompiler/src/TextMiningCompiler.cc
        TextMiningCompiler/src/Trie.cc
        TextMiningCompiler/src/Trie.hh
        TextMiningCompiler/src/TrieFactory.hh
        TextMiningCompiler/src/TrieFactory.cc
        common/DumpableNode.hh)

add_executable(TextMiningApp
        TextMiningApp/src/TextMiningApp.cc
        TextMiningApp/src/ApproxSearch.cc
        TextMiningApp/src/ApproxSearch.hh
        common/DumpableNode.hh)
