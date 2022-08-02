// Ex7_06.cpp
// Supplying default values for constructor arguments
#include <iostream>
using std::cout;
using std::endl;

class CBox                             // Class definition at global scope
{
public:
  double m_Length;                     // Length of a box in inches
  double m_Width;                      // Width of a box in inches
  double m_Height;                     // Height of a box in inches

  // Constructor definition
  CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0)
  {
    cout << "Constructor called." << endl;
    m_Length = lv;                     // Set values of
    m_Width = wv;                      // data members
    m_Height = hv;
  }

  // Function to calculate the volume of a box
  double volume()
  {
    return m_Length*m_Width*m_Height;
  }
};

int main()
{
  CBox box2;                           // Declare box2 - no initial values        
  cout << "Volume of box2 = " << box2.volume() << endl;

  return 0;
}
