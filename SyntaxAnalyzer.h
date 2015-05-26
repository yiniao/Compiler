//
// Created by yiniao on 2015/5/7.
//

#ifndef COMPILER_SYNTAXANALYZER_H
#define COMPILER_SYNTAXANALYZER_H

#include <fstream>
#include <queue>
#include <string>
#include <stack>
#include <stdlib.h>


#include "Util.h"
#include "Constant.h"
#include "Pro.h"

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

            string tmp = line.substr(line.find_first_not_of(' '));
            string word = tmp.substr(0, tmp.find(' '));

            string line_num = line.substr(line.rfind(' '));

            words_.push(word);
            line_nums_.push(line_num);
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

            cur_line_num_ = line_nums_.front();
            line_nums_.pop();
        }

    }

    void NextNotPop()
    {
        if (words_.empty()) {
            cur_word_ = " ";
        }
        else {
            cur_word_ = words_.front();
            cur_line_num_ = line_nums_.front();
        }

    }

    void Error(string info)
    {
        cout << "***LINE:" << cur_line_num_ << "  " << info << endl;
        exit(0);
    }

    void AddPro(string name)
    {
        Pro pro;
        pro.name_ = name;
        pros_.push(pro);
    }

    void DelPro()
    {
        pros_.pop();
    }

    Pro& PeekPro()
    {
        return pros_.top();
    }

    void AddVar(unsigned int kind)
    {
        for (auto var : PeekPro().vars_)
        {
            if (cur_word_ == var.first && var.second.kind_ != PARAMETER)
            {
                Error("variable " + cur_word_ + " is redefine");
            }
        }

        cur_var_.name_ = cur_word_;
        cur_var_.kind_ = kind;
        cur_var_.type_ = 0;
        PeekPro().vars_.insert(pair<string, Var>(cur_var_.name_, cur_var_));
    }

    void CheckVar()
    {
        if (cur_word_ == PeekPro().name_) {
            return ;
        }

        for (auto var : PeekPro().vars_)
        {
            if (var.first == cur_word_)
            {
                return ;
            }
            else {
                Error("variable " + cur_word_ + " is not define");
            }
        }
    }

    void PrintVars()
    {
        for(auto var : PeekPro().vars_)
        {
            cout << var.first << endl;
        }
    }

private:
    ifstream           fin_;
    queue<string>      words_;
    queue<string>      line_nums_;
    string             cur_word_;
    string             cur_line_num_;
    char               cur_char_;

    stack<Pro>         pros_;
    //Pro                cur_pro_;
    Var                cur_var_;

private:


    ////////////////////////////////////////////////////////////////////////////////////////
    //
    //                     ��ͨ�½��ݹ����
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
    //                     �½��ݹ����---���� BNF
    //
    ////////////////////////////////////////////////////////////////////////////////////////
    //  Program             -> SubProgram
    //  SubProgram          -> begin  StatementTable  ;  ExecutionTable  end
    //
    //
    //  StatementTable      -> Statement {; Statement}                    //������ݹ�
    //  Statement           -> integer (Variable | function Symbol ( Parameter ) ;  FunctionBody)  //��ȡ������
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


    void Statement();


    void Variable();
    void Symbol();

    void Letter();
    void Digit();

    void LetterOrDigit();

    void FunctionBody();
    void Parameter();

    void Execution();

    void ArithmeticExpression();


    void Term();

    void Factor();


    void ConditionExpression();

    void RelationOperator();
};


#endif //COMPILER_SYNTAXANALYZER_H
