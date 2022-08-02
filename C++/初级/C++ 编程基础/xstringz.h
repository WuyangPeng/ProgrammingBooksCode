#ifndef XSTRING_H
#define XSTRING_H

#include <iostream>
#include <string>

class xstring : std::string
{
public:
    xstring();
    xstring(const xstring& Str);
    xstring(const std::string& Str); 
    xstring(char* p);
    xstring(unsigned Length, char Ch);
explicit xstring(unsigned Length);
    operator std::string();

    short find_nocase(const xstring& Str);
    bool less_nocase (const xstring& Str);
};

#endif