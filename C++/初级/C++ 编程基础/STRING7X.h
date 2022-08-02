#ifndef STRING7X_H
#define STRING7X_H

#include <iostream>
#include <cstring>

class string
{
public:

  string(short Length);
  string(short Length, char Ch);

private:
  short m_Length;
  char* m_Data;
};

#endif
