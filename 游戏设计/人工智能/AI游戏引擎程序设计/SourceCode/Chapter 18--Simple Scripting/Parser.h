#pragma once

#include "Token.h"

using namespace std;

class Parser
{
public:
    Parser(TokenList *tList = NULL):m_tokenList(tList){}
    int         CheckForToken(char currentChar);
    bool        ParseFile(char* fileNameStr);
    void        Reset();
    void        SetTokenList(TokenList *tList){m_tokenList = tList;}
    
protected:
    TokenList*  m_tokenList;
};


