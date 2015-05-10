cmake_minimum_required(VERSION 3.1)
project(Compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Compiler.h Compiler.cpp Constant.h LexicalAnalyzer.h LexicalAnalyzer.cpp
                 Util.h Util.cpp SyntaxAnalyzer.h SyntaxAnalyzer.cpp)
add_executable(Compiler ${SOURCE_FILES})