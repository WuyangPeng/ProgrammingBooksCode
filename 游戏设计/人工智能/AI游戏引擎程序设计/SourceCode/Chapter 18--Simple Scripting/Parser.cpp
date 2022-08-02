#pragma warning(disable: 4786)
#include <algorithm>
#include <list>
#include "Parser.h"
#include "stdio.h"
#include "Tokens.h"
#include "MessagePump.h"

//---------------------------------------------------------
int Parser::CheckForToken(char currentChar)
{
    TokenList::iterator tListiterator;
    for (tListiterator = m_tokenList->begin();tListiterator != m_tokenList->end(); ++tListiterator)
    {
        Token* pToken = *tListiterator;
        if (tolower(currentChar) == tolower(pToken->m_tokenAsStr[pToken->m_matchPos])) 
        { 
            // if the currentChar matches the requested character of the current token,...
            pToken->m_matchPos++; // ...increase the "match-position" counter
            
            if (pToken->m_matchPos == strlen(pToken->m_tokenAsStr)) 
            { // if the counter equals the length of the current token, we found a token. Thus,...
                //...reset the counters of all the other tokens and...
                Reset();
                // ...return the token found
                return pToken->m_tokenID;
            }
        }
        else // if the currentChar does *not* match the requested character of the current token,...
        {
            pToken->m_matchPos = 0; // reset the corresponding counter
        }
    }
    return NO_TOKEN;
}

//---------------------------------------------------------
void ZeroPosition(Token* pToken)
{
    pToken->m_matchPos = 0;
}

//---------------------------------------------------------
void Parser::Reset()
{
    for_each(m_tokenList->begin(),m_tokenList->end(),ZeroPosition);
}

//---------------------------------------------------------
bool Parser::ParseFile(char* fileNameStr)
{
    FILE* pFile;
    if ((pFile = fopen(fileNameStr,"r")) == NULL)
    {
        return false;
    }
    
    char buffer;
    Reset();
    while (fread(&buffer, 1, 1, pFile) == 1)
    {
        int currentToken = CheckForToken(buffer);
        if(currentToken == Token::TT_NONE)
            continue;
        else
        {
            TokenList::iterator tListiterator;
            for (tListiterator = m_tokenList->begin();tListiterator != m_tokenList->end(); ++tListiterator)
            {
                Token* pToken = *tListiterator;
                if(pToken->m_tokenID == currentToken)
                    pToken->Execute(pFile);
            }
        }
    }
        
   fclose(pFile);
    return true;
}