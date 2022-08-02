// Box.h in Ex9_04
#pragma once
#include <iostream>

class CBox
{
public:
  // Base class constructor
  explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv }
  {
    std::cout << "CBox constructor called" << std::endl;
  }

  // CBox destructor - just to track calls
  ~CBox()
  {
    std::cout << "CBox destructor called" << std::endl;
  }

protected:
  double m_Length;
  double m_Width;
  double m_Height;
};
