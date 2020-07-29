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

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.out)
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


