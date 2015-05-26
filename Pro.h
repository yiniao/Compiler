//
// Created by yiniao on 2015/5/26.
//

#ifndef COMPILER_PRO_H
#define COMPILER_PRO_H

#include <map>
#include <string>
#include "Var.h"

using namespace std;

class Pro {
public:
    string           name_;
    map<string, Var> vars_;

//    unsigned int     type_;
//    unsigned int     level_;
//    unsigned int     fadr_;
//    unsigned int     ladr_;
};


#endif //COMPILER_PRO_H
