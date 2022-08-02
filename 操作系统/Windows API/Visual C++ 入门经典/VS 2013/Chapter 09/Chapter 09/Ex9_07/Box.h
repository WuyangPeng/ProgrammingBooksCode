// Box.h in Ex9_07
#pragma once
#include <iostream>

class CBox                             // Base class
{
public:
  // Function to show the volume of an object
  void showVolume() const
  {
    std::cout << "CBox usable volume is " << volume() << std::endl;
  }

  // Function to calculate the volume of a CBox object
  virtual double volume() const
  {
    return m_Length*m_Width*m_Height;
  }

  // Constructor
  explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv } {}

protected:
  double m_Length;
  double m_Width;
  double m_Height;
};
