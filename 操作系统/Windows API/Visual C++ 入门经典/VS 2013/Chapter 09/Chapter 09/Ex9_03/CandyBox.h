// CandyBox.h in Ex9_03
#pragma once
#include <cstring>                     // For strlen() and strcpy()
#include <iostream>
#include "Box.h"
class CCandyBox : public CBox
{
public:
  char* m_Contents;

  // Constructor to set dimensions and contents
  // with explicit call of CBox constructor
  CCandyBox(double lv, double wv, double hv, const char* str = "Candy")
    : CBox{ lv, wv, hv }
  {
    std::cout << "CCandyBox constructor2 called" << std::endl;
    size_t length{ strlen(str) + 1 };
    m_Contents = new char[length];
    strcpy_s(m_Contents, length, str);
  }

  // Constructor to set contents
  // calls default CBox constructor automatically
  explicit CCandyBox(const char* str = "Candy")
  {
    std::cout << "CCandyBox constructor1 called" << std::endl;
    size_t length{ strlen(str) + 1 };
    m_Contents = new char[length];
    strcpy_s(m_Contents, length, str);
  }

  CCandyBox(const CCandyBox& box) = delete;
  CCandyBox& operator=(const CCandyBox& box) = delete;

  ~CCandyBox()                                 // Destructor
  {
    delete[] m_Contents;
  }
};
