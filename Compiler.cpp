//
// Created by yiniao on 2015/5/5.
//

#include "Compiler.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"


void Compiler::LexicalAnalysis() {
    Lex lex(filename_);
    lex.Execute();
    lex.Close();
}


void Compiler::SyntaxAnalysis() {
    SyntaxAnalyzer syntaxAnalyzer(util::ChangeSuffix(filename_, LEXICAL_ANALYSIS_SUFFIX));
    syntaxAnalyzer.Execute();
    syntaxAnalyzer.Close();
}

void Compiler::Execute() {
    LexicalAnalysis();
    SyntaxAnalysis();
}
