#include "Token.h"

//---------------------------------------------------------
bool Token::GetBool(_iobuf* fileName)
{
    unsigned char buffer = tolower(GetChar(fileName));
    //need to pull out the rest of the word, to keep the file
    //pointing to the correct place
    string temp;
    GetString(fileName,temp);
    
    //if it's an "n(no), f(false), z(zero), or the number 0, return false
    if(buffer == 'n' || 
        buffer == 'f' ||
        buffer == '0' ||
        buffer == 'z')
        return false;
    //if it's a "y(yes), t(true), o(one), or the number 1, return true
    else if(buffer == 'y' || 
        buffer == 't' ||
        buffer == '1' ||
        buffer == 'o')
        return true;
    
    return false;
}

//---------------------------------------------------------
char Token::GetChar(_iobuf* fileName)
{
    unsigned char buffer;
    //get the next non whitespace character
    while(fread(&buffer, 1,1,fileName) == 1 && buffer == ' ');
    return buffer;
}

//---------------------------------------------------------
int Token::GetInt(_iobuf* fileName)
{
    string bufferStr;
    GetString(fileName,bufferStr);
    return atoi(bufferStr.c_str());
}

//---------------------------------------------------------
float Token::GetFloat(_iobuf* fileName)
{
    string bufferStr;
    GetString(fileName,bufferStr);
    return atof(bufferStr.c_str());
}

//---------------------------------------------------------
void Token::GetString(_iobuf* fileName,string& storageStr)
{
    unsigned char buffer;
    while (fread(&buffer, 1,1,fileName) == 1 && buffer != ';')
    {
        storageStr += buffer;
    }
}
