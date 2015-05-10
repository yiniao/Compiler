//
// Created by yiniao on 2015/5/6.
//

#include "LexicalAnalyzer.h"

bool Lex::LexAnalyze()
{
    token_.clear();
    if (!GetNextChar())
        return false;

    if (!GetNBC())
        return false;

    switch (character_)
    {
        case 'a' : case 'b' : case 'c' : case 'd' : case 'e' : case 'f' : case 'g' :
        case 'h' : case 'i' : case 'j' : case 'k' : case 'l' : case 'm' : case 'n' :
        case 'o' : case 'p' : case 'q' : case 'r' : case 's' : case 't' :
        case 'u' : case 'v' : case 'w' : case 'x' : case 'y' : case 'z' :
        case 'A' : case 'B' : case 'C' : case 'D' : case 'E' : case 'F' : case 'G' :
        case 'H' : case 'I' : case 'J' : case 'K' : case 'L' : case 'M' : case 'N' :
        case 'O' : case 'P' : case 'Q' : case 'R' : case 'S' : case 'T' :
        case 'U' : case 'V' : case 'W' : case 'X' : case 'Y' : case 'Z' : {

            while (IsDigit() || IsLetter()) {
                Concat();
                if (!GetNextChar())
                    return false;
            }
            Retract();
            short type_num = Reserve();
            if (type_num != 0)
                fout_ << ToString(type_num);
            else {
                fout_ << ToString(RESERVE_MAP.at(SYMBOL));
            }
            break;
        }

        case '0' :
        case '1' : case '2' : case '3' :
        case '4' : case '5' : case '6' :
        case '7' : case '8' : case '9' : {
            while (IsDigit()) {
                Concat();
                if (!GetNextChar())
                    return false;
            }
            Retract();
            fout_ << ToString(RESERVE_MAP.at(CONSTANT));
            break;
        }

        case '<' : {
            Concat();
            if (!GetNextChar())
                return false;
            if (character_ == '=') {
                Concat();
                fout_ << ToString(RESERVE_MAP.at("<="));
            }
            else if (character_ == '>') {
                Concat();
                fout_ << ToString(RESERVE_MAP.at("<>"));
            }
            else {
                Retract();
                fout_ << ToString(RESERVE_MAP.at("<"));
            }

            break;
        }

        case '>' : {
            Concat();
            if (!GetNextChar())
                return false;
            if (character_ == '=') {
                Concat();
                fout_ << ToString(RESERVE_MAP.at(">="));
            }
            else {
                Retract();
                fout_ << ToString(RESERVE_MAP.at(">"));
            }

            break;
        }

        case ':' : {

            Concat();
            if (!GetNextChar())
                return false;
            if (character_ == '=') {
                Concat();
                fout_ << ToString(RESERVE_MAP.at(":="));
            }
            else {
                Error();
            }

            break;
        }

        case '=' : { Concat(); fout_ << ToString(RESERVE_MAP.at("=")); break; }
        case '*' : { Concat(); fout_ << ToString(RESERVE_MAP.at("*")); break; }
        case '-' : { Concat(); fout_ << ToString(RESERVE_MAP.at("-")); break; }
        case '(' : { Concat(); fout_ << ToString(RESERVE_MAP.at("(")); break; }
        case ')' : { Concat(); fout_ << ToString(RESERVE_MAP.at(")")); break; }
        case ';' : { Concat(); fout_ << ToString(RESERVE_MAP.at(";")); break; }

        default: Error();
    }

    return true;
}


