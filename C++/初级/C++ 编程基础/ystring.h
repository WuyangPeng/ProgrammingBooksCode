#ifndef STRINGY_H
#define STRINGY_H

#include <iostream>
#include <string>

class xstring : public std::string
{
public:

  xstring(short Length);
  xstring(short Length, char Ch);
};

#endif
