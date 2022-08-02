// Header file CandyBox.h in project Ex9_02
#pragma once
#include "Box.h"
#include <cstring>                     // For strlen() and strcpy_s()
class CCandyBox : public CBox
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
