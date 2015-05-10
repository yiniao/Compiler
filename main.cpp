#include <iostream>
#include "Compiler.h"

using namespace std;



int main() {

//    Lex lex("d:\\Test.pas");
//
//    lex.Execute();

//    SyntaxAnalyzer syntaxAnalyzer("d:\\Test.dyd");
//
//    syntaxAnalyzer.Init();
//    syntaxAnalyzer.Execute();

    Compiler compiler("d:\\Test.pas");
    compiler.Execute();



    return 0;
}

