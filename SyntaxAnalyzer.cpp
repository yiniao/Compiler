//
// Created by yiniao on 2015/5/7.
//

#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

void SyntaxAnalyzer::Execute() {
    Program();
}

void SyntaxAnalyzer::Program() {
    SubProgram();
}


void SyntaxAnalyzer::SubProgram() {
    Next();
    if (cur_word_ == "begin") {
        StatementTable();
        //Next();                                        // <====================
        if (cur_word_ == ";") {
            ExecutionTable();
            Next();
            if (cur_word_ == "end") {
                cout << "[INFO] -- Syntax Right !!!" << endl;
            }
            else {
                Error("[ERROR] -- 1: begin end not match");
            }
        }
        else {
            Error("[ERROR] -- 1: lack of \";\"");
        }
    }
    else {
        Error("[ERROR] -- lack of \"begin\"");
    }
}


void SyntaxAnalyzer::StatementTable() {
    Statement();
    NextNotPop();                           // <----
    while (cur_word_ == ";") {
        Next();                             // <----

        if (words_.front() != "integer") {
            break;
        }


        Statement();
        NextNotPop();
    }
}


void SyntaxAnalyzer::ExecutionTable() {
    Execution();
    NextNotPop();                          // <----
    while ( cur_word_ == ";") {            //     -
        Next();                            // <----

        Execution();
        NextNotPop();
    }
}


void SyntaxAnalyzer::Statement() {
    Next();
    if (cur_word_ == "integer") {
        NextNotPop();                         //  <----
        if ( cur_word_ == "function") {       //      -
            Next();                           //  <----


            Symbol();
            Next();
            if ( cur_word_ == "(") {
                Parameter();
                Next();
                if ( cur_word_ == ")") {
                    Next();
                    if ( cur_word_ == ";") {
                        FunctionBody();
                    }
                    else {
                        Error("[ERROR] -- 2: lack of \";\"");
                    }
                }
                else {
                    Error("[ERROR] -- 1: lack of \")\"");
                }
            }
            else {
                Error("[ERROR] -- 1: lack of \"(\" ");
            }
        }
        else {
            Variable();
        }
    }
    else {
        Error("[ERROR] -- declaration lack of \"integer\"");
    }
}

void SyntaxAnalyzer::FunctionBody() {
    Next();
    if ( cur_word_ == "begin") {
        StatementTable();
        //Statement();
        //Next();                                       // <====================
        if ( cur_word_ == ";") {
            ExecutionTable();
            //Execution();
            Next();
            if (cur_word_ != "end") {
                Error("[ERROR] -- 2: begin end not match");
            }
        }
        else {
            Error("[ERROR] -- 3: lack of \";\"");
        }
    }
    else {
        Error("[ERROR] -- lack of \"begin\"");
    }
}

void SyntaxAnalyzer::Execution() {
    NextNotPop();
    if ( cur_word_ == "read" || cur_word_ == "write") {
        Next();


        Next();
        if ( cur_word_ == "(") {
            Variable();
            Next();
            if (cur_word_ != ")") {
                Error("[ERROR] -- 2: lack of \")\"");
            }
        }
        else {
            Error("[ERROR] -- 2: lack of \"(\"");
        }
    }
    else if ( cur_word_ == "if") {
        Next();



        ConditionExpression();
        Next();
        if ( cur_word_ == "then") {
            Execution();
            Next();
            if ( cur_word_ == "else") {
                Execution();
            }
            else {
                Error("[ERROR] -- lack of \"else\"");
            }
        }
        else {
            Error("[ERROR] -- lack of \"then\"");
        }
    }
    else {
        Variable();
        Next();
        if ( cur_word_ == ":=" ) {
            ArithmeticExpression();
        }
        else {
            Error("[ERROR] -- \":=\" is error");
        }
    }
}

void SyntaxAnalyzer::ConditionExpression() {
    ArithmeticExpression();
    RelationOperator();
    ArithmeticExpression();
}

void SyntaxAnalyzer::ArithmeticExpression() {
    Term();
    NextNotPop();
    while ( cur_word_ == "-" ) {
        Next();

        Term();
        NextNotPop();
    }
}

void SyntaxAnalyzer::Term() {
    Factor();
    NextNotPop();
    while ( cur_word_ == "*" ) {
        Next();

        Factor();
        NextNotPop();
    }
}

void SyntaxAnalyzer::Factor() {
    NextNotPop();
    string::iterator it = cur_word_.begin();

    cur_char_ = *it;

    LetterOrDigit();

    if (isdigit(cur_char_)) {
        for (it++; it != cur_word_.end(); it++)
        {
            cur_char_ = *it;
            Digit();
        }
        Next();
    }
    else if (cur_char_ > 'a' && cur_char_ < 'z'
             || cur_char_ > 'A' && cur_char_ < 'Z') {
        Symbol();

        NextNotPop();
        if ( cur_word_ == "(") {
            Next();

            ArithmeticExpression();
            Next();
            if ( cur_word_ != ")") {
                Error("[ERROR] -- 3: lack of \")\"");
            }
        }
    }
}

void SyntaxAnalyzer::RelationOperator() {
    Next();
    if ( !(cur_word_ == "<"
           || cur_word_ == "<="
           || cur_word_ == ">"
           || cur_word_ == ">="
           || cur_word_ == "<>"))
    {
        Error("[ERROR] -- relation operator is error");
    }
}

void SyntaxAnalyzer::Parameter() {
    Symbol();
}

void SyntaxAnalyzer::Variable() {
    Symbol();
}

void SyntaxAnalyzer::Symbol() {
    Next();
    string::iterator it = cur_word_.begin();

    cur_char_ = *it;
    Letter();


    for (it++; it != cur_word_.end(); it++)
    {
        cur_char_ = *it;
        LetterOrDigit();
    }
}


void SyntaxAnalyzer::Digit() {
    if (!isdigit(cur_char_)) {
        Error("[ERROR] -- not a digit");
    }
}

void SyntaxAnalyzer::Letter() {
    if (!(cur_char_ > 'a' && cur_char_ < 'z'
          || cur_char_ > 'A' && cur_char_ < 'Z'))
    {
        Error("[ERROR] -- symbol's first char is not letter");
    }
}


void SyntaxAnalyzer::LetterOrDigit() {
    if (!(cur_char_ > 'a' && cur_char_ < 'z'
          || cur_char_ > 'A' && cur_char_ < 'Z'
          || isdigit(cur_char_)))
    {
        Error("[ERROR] -- symbol's first char is not letter or digit");
    }
}

