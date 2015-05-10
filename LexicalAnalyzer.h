//
// Created by yiniao on 2015/5/6.
//

#ifndef COMPILER_LEX_H
#define COMPILER_LEX_H

#include <fstream>
#include <iostream>

#include "Constant.h"

#include "Util.h"

using namespace std;

class Lex {
public:
    Lex(string name)
            : fin_(name, ios::binary), fout_(util::ChangeSuffix(name, LEXICAL_ANALYSIS_SUFFIX)),
              ferr_(util::ChangeSuffix(name, ERROR_SUFFIX)), character_(' '), token_(" ")
    {}

    void Execute() {
        while (LexAnalyze());

    }

    bool LexAnalyze();

    bool IsEOF() {
        return fin_.eof();
    }

    void Close() {
        fin_.close();
        fout_.close();
        ferr_.close();
    }

    char GetCharacter() {
        return character_;
    }

    string GetToken() {
        return token_;
    }

    string ToString(short type_num) {
        char buf[25];
        snprintf(buf, 25, "%s  %hd\n",  token_.c_str(), type_num);

        string str(buf);
        return str;
    }


    bool GetNextChar() {
        fin_.get(character_);
        return !fin_.eof();
    }


    bool GetNBC() {
        while (character_ == ' '
               || character_ == '\n'
               || character_ == '\t'
               || character_ == '\r')
        {
            if(!GetNextChar())
                return false;
        }
        return true;
    }

    void Concat() {
        token_ += character_;
    }

    bool IsLetter() {
        return (character_ >= 'a' && character_ <= 'z')
               || (character_ >= 'A' && character_ <= 'Z');

    }

    bool IsDigit() {
        return isdigit(character_);
    }

    void Retract() {
        fin_.seekg(-1, ios::cur);
    }

    short Reserve() {
        try {
            return RESERVE_MAP.at(token_);
        }
        catch (const std::out_of_range& oor) {
            return 0;
        }
    }

    short Symbol() {
        return 0;
    }

    short Constant() {
        return 0;
    }

    void Error() {
        ferr_ << "[ERROR]" << token_ << endl;
    }

private:
    ifstream fin_;
    ofstream fout_;
    ofstream ferr_;

    char     character_;
    string   token_;
};


#endif //COMPILER_LEX_H
