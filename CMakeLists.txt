cmake_minimum_required(VERSION 3.14)

project(Autocorrect)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")
SET(EXECUTABLE_OUTPUT_PATH ../)

add_executable(TextMiningCompiler
        src/TextMiningCompiler/TextMiningCompiler.cc
        src/TextMiningCompiler/Trie.cc
        src/TextMiningCompiler/Trie.hh
        src/TextMiningCompiler/TrieFactory.hh
        src/TextMiningCompiler/TrieFactory.cc
        src/common/DumpableNode.hh)

add_executable(TextMiningApp
        src/TextMiningApp/TextMiningApp.cc
        src/TextMiningApp/ApproxSearch.cc
        src/TextMiningApp/ApproxSearch.hh
        src/common/DumpableNode.hh)

add_custom_target(check
        COMMAND ${CMAKE_BINARY_DIR}/../tests/testsuite.sh
        DEPENDS TextMiningApp TextMiningCompiler)