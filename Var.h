//
// Created by yiniao on 2015/5/26.
//

#ifndef COMPILER_VAR_H
#define COMPILER_VAR_H

#include <string>

using namespace std;

class Var {
public:
    string       name_;
    unsigned int kind_;
    unsigned int type_;

//    string       proc_;
//    unsigned int level_;
//    unsigned int adr_;
};


#endif //COMPILER_VAR_H
