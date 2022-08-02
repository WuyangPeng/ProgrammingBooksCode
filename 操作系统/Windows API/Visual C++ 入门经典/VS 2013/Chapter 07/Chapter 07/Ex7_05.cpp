// Ex7_05.cpp
// Supplying and using a default constructor
#include <iostream>
using std::cout;
using std::endl;
class CBox                                  // Class definition at global scope
{
public:
  double m_Length{ 1.0 };                   // Length of a box in inches
  double m_Width{ 1.0 };                    // Width of a box in inches
  double m_Height{ 1.0 };                   // Height of a box in inches

  // Constructor definition
  CBox(double lv, double wv, double hv)
  {
    cout << "Constructor called." << endl;
    m_Length = lv;                          // Set values of
    m_Width = wv;                           // data members
    m_Height = hv;
  }

  // Default constructor definition
  CBox()
  {
    cout << "Default constructor called." << endl;
  }

  // Function to calculate the volume of a box
  double volume()
  {
    return m_Length* m_Width* m_Height;
  }
};

int main()
{
  CBox box1{ 78.0, 24.0, 18.0 };            // Define and initialize box1
  CBox box2;                                // Define box2 - no initial values
  CBox cigarBox{ 8.0, 5.0, 1.0 };           // Define and initialize cigarBox

  cout << "Volume of box1 = " << box1.volume() << endl;
  cout << "Volume of cigarBox = " << cigarBox.volume() << endl;

  box2.m_Height = box1.m_Height - 10;       // Define box2
  box2.m_Length = box1.m_Length / 2.0;      // members in
  box2.m_Width = 0.25*box1.m_Length;        // terms of box1
  cout << "Volume of box2 = " << box2.volume() << endl;
  return 0;
}
