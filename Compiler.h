//
// Created by yiniao on 2015/5/5.
//

#ifndef COMPILER_COMPILER_H
#define COMPILER_COMPILER_H

#include <string>
#include <map>

using namespace std;

class Compiler {
public:

    Compiler(string filename)
            : filename_(filename)
    {}

    void Execute();

    void LexicalAnalysis();

    void SyntaxAnalysis();




private:

    string filename_;


};


#endif //COMPILER_COMPILER_H
