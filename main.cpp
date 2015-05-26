#include <iostream>
#include "Compiler.h"
#include "Pro.h"
#include "LexicalAnalyzer.h"
#include <map>
#include <stack>

using namespace std;

int main() {

//    Lex lex("e:\\Test.pas");
//
//    lex.Execute();

//    SyntaxAnalyzer syntaxAnalyzer("e:\\Test.dyd");
//
//    syntaxAnalyzer.Init();
//    syntaxAnalyzer.Execute();

    Compiler compiler("e:\\Test.pas");
    compiler.Execute();




    return 0;
}

