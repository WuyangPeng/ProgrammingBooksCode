// Can.h for Ex9_12
#pragma once
#define _USE_MATH_DEFINES              // For constants in math.h
#include <math.h>
#include "Container.h"                 // For CContainer definition

class CCan : public CContainer
{
public:
  // Function to calculate the volume of a can
  virtual double volume() const override
  {
    return 0.25*M_PI*m_Diameter*m_Diameter*m_Height;
  }

  // Constructor
  explicit CCan(double hv = 4.0, double dv = 2.0) : m_Height{ hv }, m_Diameter{ dv } {}

  ~CCan()
  {
    std::cout << "CCan destructor called" << std::endl;
  }

protected:
  double m_Height;
  double m_Diameter;
};
