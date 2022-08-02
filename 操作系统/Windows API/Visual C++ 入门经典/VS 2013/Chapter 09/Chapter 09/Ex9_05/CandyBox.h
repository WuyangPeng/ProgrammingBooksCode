// CandyBox.h in Ex9_04
#pragma once
#include "Box.h"
#include <cstring>                     // For strlen() and strcpy()
#include <iostream>

class CCandyBox : public CBox
{
public:
  char* m_Contents;

  // Derived class function to calculate volume
  double volume() const
  {
    return m_Length*m_Width*m_Height;
  }

  // Constructor to set dimensions and contents with explicit call of CBox constructor
  explicit CCandyBox(double lv, double wv, double hv,
    const char* str = "Candy") : CBox{ lv, wv, hv }
  {
    std::cout << "CCandyBox constructor2 called" << std::endl;
    m_Contents = new char[strlen(str) + 1];
    strcpy_s(m_Contents, strlen(str) + 1, str);
  }

  // Constructor to set contents - calls default CBox constructor automatically
  explicit CCandyBox(const char* str = "Candy")
  {
    std::cout << "CCandyBox constructor1 called" << std::endl;
    m_Contents = new char[strlen(str) + 1];
    strcpy_s(m_Contents, strlen(str) + 1, str);
  }

  // Derived class copy constructor
  CCandyBox(const CCandyBox& initCB)
  {
    std::cout << "CCandyBox copy constructor called" << std::endl;
    size_t length{ strlen(initCB.m_Contents) + 1 };
    m_Contents = new char[length];                            // Get new memory
    strcpy_s(m_Contents, length, initCB.m_Contents);          // Copy string
  }

  CCandyBox& operator=(const CCandyBox& box) = delete;

  ~CCandyBox()                                                // Destructor
  {
    std::cout << "CCandyBox destructor called" << std::endl;
    delete[] m_Contents;
  }
};
