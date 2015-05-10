//
// Created by yiniao on 2015/5/7.
//

#ifndef COMPILER_SYNTAXANALYZER_H
#define COMPILER_SYNTAXANALYZER_H

#include <fstream>
#include <queue>
#include <string>
#include <stdlib.h>


#include "Util.h"
#include "Constant.h"

using namespace std;

class SyntaxAnalyzer {


public:
    SyntaxAnalyzer(string name)
            :fin_(name)
    {
        Init();
    }

    void Execute();

    void Close() {
        fin_.close();
    }

    void Init()
    {
        string line;
        while (1) {
            getline(fin_, line);
            if (fin_.eof()) {
                break;
            }
            string word = line.substr(0, line.find(' '));
            words_.push(word);
        }
    }

private:

    void Next()
    {
        if (words_.empty()) {
            cur_word_ = " ";
        }
        else {
            cur_word_ = words_.front();
            words_.pop();
        }

    }


    void NextNotPop()
    {
        if (words_.empty()) {
            cur_word_ = " ";
        }
        else {
            cur_word_ = words_.front();
        }

    }

    void Error(string info)
    {
        cout << info << endl;
        exit(0);
    }




private:
    ifstream            fin_;
    queue<string>       words_;
    string             cur_word_;
    char               cur_char_;


private:


    ////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     普通下降递归分析
    //
    ////////////////////////////////////////////////////////////////////////////////////////
    //  Program             -> SubProgram
    //  SubProgram          -> begin  StatementTable  ;  ExecutionTable  end
    //
    //
    //  StatementTable      -> Statement  StatementTableExt
    //  StatementTableExt   -> ;  Statement StatementTableExt | null_string
    //  Statement           -> integer (Variable | function Symbol ( Parameter ) ;  FunctionBody)
    //
    //  Variable            -> Symbol
    //  Symbol              -> Letter SymbolExt
    //  SymbolExt           -> Letter SymbolExt | Digit SymbolExt | null_string
    //  Letter              -> a | b | c ... |z | A |  ... | Z
    //  Digit               -> 1 | 2 | ...  | 9
    //
    //  Parameter           -> Variable
    //  FunctionBody        -> begin StatementTable ; ExecutionTable end
    //
    //
    //  ExecutionTable      -> Execution  ExecutionTableExt
    //  ExecutionTableExt   -> ;   Execution   ExecutionTableExt | null_string
    //  Execution           -> Read | Write | Assignment | Condition
    //
    //  Read                -> read ( Variable )
    //
    //  Write               -> write ( Variable )
    //
    //  Assignment          -> Variable := ArithmeticExpression
    //  ArithmeticExpression          -> Term ArithmeticExpressionExt
    //  ArithmeticExpressionExt          -> - Term ArithmeticExpressionExt | null_string
    //  Term                -> Factor TermExt
    //  TermExt             -> * Factor TermExt | null_string
    //  Factor              -> Variable | Constant | Call
    //
    //      Constant        -> UnsignedInteger
    //      UnsignedInteger -> Digit UnsignedIntegerExt
    //      UnsignedIntegerExt -> Digit UnsignedIntegerExt | null_string
    //
    //      Call            -> Symbol ( ArithmeticExpression )
    //
    //  Condition           -> if ConditionExpression then Execution else Execution
    //  ConditionExpression -> ArithmeticExpression RelationOperator ArithmeticExpression
    //  RelationOperator    -> < | <= | > | >= | = | <>
    //////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     下降递归分析---扩充 BNF
    //
    ////////////////////////////////////////////////////////////////////////////////////////
    //  Program             -> SubProgram
    //  SubProgram          -> begin  StatementTable  ;  ExecutionTable  end
    //
    //
    //  StatementTable      -> Statement {; Statement}                    //消除左递归
    //  Statement           -> integer (Variable | function Symbol ( Parameter ) ;  FunctionBody)  //提取左公因子
    //
    //  Variable            -> Symbol
    //  Symbol              -> Letter { Letter | Digit }
    //  Letter              -> a | b | c ... |z | A |  ... | Z
    //  Digit               -> 1 | 2 | ...  | 9
    //
    //  Parameter           -> Variable
    //  FunctionBody        -> begin StatementTable ; ExecutionTable end
    //
    //
    //  ExecutionTable      -> Execution { ;  Execution }
    //  Execution           -> Read | Write | Assignment | Condition
    //
    //  Read                -> read ( Variable )
    //
    //  Write               -> write ( Variable )
    //
    //  Assignment          -> Variable := ArithmeticExpression
    //  ArithmeticExpression          -> Term { - Term }
    //  Term                -> Factor { * Factor }
    //  Factor              -> Variable | Constant | Call
    //
    //      Constant        ->  Digit { Digit }
    //      Call            -> Symbol ( ArithmeticExpression )
    //
    //  Condition           -> if ConditionExpression then Execution else Execution
    //  ConditionExpression -> ArithmeticExpression RelationOperator ArithmeticExpression
    //  RelationOperator    -> < | <= | > | >= | = | <>
    //////////////////////////////////////////////////////////////////////////////////////////

    void Program();
    void SubProgram();

    void StatementTable();
    void ExecutionTable();


    //void StatementTableExt();
    void Statement();


    void Variable();
    void Symbol();
    //void SymbolExt();
    void Letter();
    void Digit();

    void LetterOrDigit();

    void FunctionBody();
    void Parameter();

    //void ExecutionTableExt();
    void Execution();

    void Read();
    void Write();
    void Assignment();
    void Condition();

    void ArithmeticExpression();
    //void ArithmeticExpressionExt();

    void Term();
    //void TermExt();
    void Factor();

    void Constant();
    void Call();
    void UnsignedInteger();
    //void UnsignedIntegerExt();

    void ConditionExpression();

    void RelationOperator();
};


#endif //COMPILER_SYNTAXANALYZER_H
