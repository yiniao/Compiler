//
// Created by yiniao on 2015/5/5.
//

#ifndef COMPILER_CONSTANT_H
#define COMPILER_CONSTANT_H

#include <string>
#include <map>

using namespace std;

const string SOURCE_SUFFIX = "pas";
const string LEXICAL_ANALYSIS_SUFFIX = "dyd";
const string GRAMMATICAL_ANALYSIS_SUFFIX = "dys";
const string ERROR_SUFFIX = "err";

const unsigned int VARIABLE = 0;
const unsigned int PARAMETER = 1;

const string SYMBOL = "symbol";
const string CONSTANT = "constant";

const static map<string, short> RESERVE_MAP{
        {"begin" , 1},      {"end"   , 2},  {"integer" , 3},
        {"if"    , 4},      {"then"  , 5},  {"else"  , 6},
        {"function" , 7},   {"read"   , 8}, {"write"  , 9},
        {SYMBOL , 10},      {CONSTANT, 11}, {"=", 12},
        {"<>", 13},         {"<=", 14},     {"<", 15},
        {">=", 16},         {">", 17},      {"-", 18},
        {"*", 19},          {":=", 20},     {"(", 21},
        {")", 22},          {";", 23}                       };



#endif //COMPILER_CONSTANT_H
