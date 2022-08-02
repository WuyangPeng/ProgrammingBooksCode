#pragma once

#pragma warning(disable: 4786)
#include <list>
#include "utility.h"
#include <string>
using namespace std;

#define MAX_TOKEN_LENGTH	40
#define NO_TOKEN			0

class Token
{
public:

    enum
    {
        TT_NONE,
        TT_POWERUPDIST,
        TT_POWERUPSEEK,
        TT_APPROACHDIST,
        TT_ATTACKDIST,
        TT_MAXSPEED,
        TT_SAFERADIUS,
    };
    
    //constructor/functions
    Token(int type = TT_NONE, char* name = ""){ m_tokenAsStr = new char(MIN(strlen(name),MAX_TOKEN_LENGTH)); 
                                                m_tokenAsStr = name;m_tokenID = type;m_matchPos = 0;}
    ~Token(){}
    virtual void Execute(_iobuf* fileName) {}

    //Additional data acquisition
    float GetFloat(_iobuf* fileName);
    char  GetChar(_iobuf* fileName);
    int   GetInt(_iobuf* fileName);
    bool  GetBool(_iobuf* fileName);
    void  GetString(_iobuf* fileName, string& storageStr);
    
    //data
    int             m_tokenID;
    int             m_matchPos;
    char*           m_tokenAsStr;
    char            m_valueAsStr[MAX_TOKEN_LENGTH];
};

typedef std::list<Token*> TokenList;

