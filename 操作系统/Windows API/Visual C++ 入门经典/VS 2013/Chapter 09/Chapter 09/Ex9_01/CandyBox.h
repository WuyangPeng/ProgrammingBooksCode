// Header file CandyBox.h in project Ex9_01
#pragma once
#include <cstring>                     // For strlen() and strcpy_s()
#include "Box.h"
class CCandyBox : CBox
{
public:
  char* m_Contents;

  explicit CCandyBox(const char* str = "Candy")               // Constructor
  {
    size_t length{ strlen(str) + 1 };

    m_Contents = new char[length];
    strcpy_s(m_Contents, length, str);
  }

  CCandyBox(const CCandyBox& box) = delete;
  CCandyBox& operator=(const CCandyBox& box) = delete;

  ~CCandyBox()                                                // Destructor
  {
    delete[] m_Contents;
  }
};
