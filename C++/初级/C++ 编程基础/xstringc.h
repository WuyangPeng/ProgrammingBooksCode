#ifndef XSTRING_H
#define XSTRING_H

#include <iostream>
#include <string>

class xstring : public std::string
{
public:
    xstring();
    xstring(const xstring& Str);
    xstring(char* p);

    short find_nocase(const xstring& Str);
    bool less_nocase (const xstring& Str);
};
#endif