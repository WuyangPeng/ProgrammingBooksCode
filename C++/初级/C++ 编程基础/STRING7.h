#ifndef XSTRING_H
#define XSTRING_H

#include <iostream>
#include <string>

class xstring : public string
{
public:
    xstring();
    xstring(const xstring& Str);

    xstring(char* p);
explicit xstring(short Length, char Ch=0);

    short find_nocase(const xstring& Str);
    bool less_nocase (const xstring& Str);
};
#endif
