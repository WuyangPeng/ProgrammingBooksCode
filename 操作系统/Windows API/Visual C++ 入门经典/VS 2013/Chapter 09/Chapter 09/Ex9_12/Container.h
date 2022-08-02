// Container.h for Ex9_12
#pragma once
#include <iostream>

class CContainer        // Generic base class for specific containers
{
public:
  // Function for calculating a volume - no content
  // This is defined as a 'pure' virtual function, signified by '= 0'
  virtual double volume() const = 0;

  // Function to display a volume
  virtual void showVolume() const
  {
    std::cout << "Volume is " << volume() << std::endl;
  }

//  virtual ~CContainer()           // Comment out the next line and uncomment this for correct operation
  ~CContainer()
  {
    std::cout << "CContainer destructor called" << std::endl;
  }
};
