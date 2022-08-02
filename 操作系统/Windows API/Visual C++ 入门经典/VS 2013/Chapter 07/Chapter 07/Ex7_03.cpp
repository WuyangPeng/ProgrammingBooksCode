// Ex7_03.cpp
// Calculating the volume of a box with a member function
#include <iostream>
using std::cout;
using std::endl;

class CBox                               // Class definition at global scope
{
public:
  double m_Length{ 1.0 };                // Length of a box in inches
  double m_Width{ 1.0 };                 // Width of a box in inches
  double m_Height{ 1.0 };                // Height of a box in inches

  // Function to calculate the volume of a box
  double volume()
  {
    return m_Length*m_Width*m_Height;
  }
};

int main()
{
  CBox box1;                             // Declare box1 of type CBox
  CBox box2;                             // Declare box2 of type CBox
  CBox box3;                             // Declare box3 of type CBox

  double boxVolume{ box1.volume() };     // Stores the volume of a box

  cout << "Default box1 volume : " << boxVolume << endl;

  box1.m_Height = 18.0;                  // Define the values
  box1.m_Length = 78.0;                  // of the members of
  box1.m_Width = 24.0;                   // the object box1

  boxVolume = box1.volume();             // Calculate new volume of box1
  cout << "Volume of box1 is now: " << boxVolume << endl;

  box2.m_Height = box1.m_Height - 10;    // Define box2
  box2.m_Length = box1.m_Length / 2.0;   // members in
  box2.m_Width = 0.25*box1.m_Length;     // terms of box1
  cout << "Volume of box2 = " << box2.volume() << endl;

  box3 = box2;
  cout << "Volume of box3 = " << box3.volume() << endl;

  cout << "A CBox object occupies "
    << sizeof box1 << " bytes." << endl;

  return 0;
}
