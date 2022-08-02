// Box.h for Ex9_10
#pragma once
#include "Container.h"                 // For CContainer definition
#include <iostream>

class CBox : public CContainer          // Derived class
{
public:

  // Function to show the volume of an object
  virtual void showVolume() const override
  {
    std::cout << "CBox usable volume is " << volume() << std::endl;
  }

  // Function to calculate the volume of a CBox object
  virtual double volume() const override
  {
    return m_Length*m_Width*m_Height;
  }

  // Constructor
  explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0)
    :m_Length{ lv }, m_Width{ wv }, m_Height{ hv } {}

protected:
  double m_Length;
  double m_Width;
  double m_Height;
};
