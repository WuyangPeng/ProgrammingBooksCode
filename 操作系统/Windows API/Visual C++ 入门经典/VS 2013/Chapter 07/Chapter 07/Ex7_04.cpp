// Ex7_04.cpp
// Using a constructor
#include <iostream>
using std::cout;
using std::endl;
class CBox                           // Class definition at global scope
{
public:
  double m_Length{ 1.0 };             // Length of a box in inches
  double m_Width{ 1.0 };              // Width of a box in inches
  double m_Height{ 1.0 };             // Height of a box in inches

  // Constructor definition
  CBox(double lv, double wv, double hv)
  {
    cout << "Constructor called." << endl;
    m_Length = lv;                   // Set values of
    m_Width = wv;                    // data members
    m_Height = hv;
  }

  // Function to calculate the volume of a box
  double volume()
  {
    return m_Length* m_Width* m_Height;
  }

};

int main()
{
  CBox box1{ 78.0, 24.0, 18.0 };          // Declare and initialize box1
  CBox cigarBox{ 8.0, 5.0, 1.0 };         // Declare and initialize cigarBox

  cout << "Volume of box1 = " << box1.volume() << endl;
  cout << "Volume of cigarBox = " << cigarBox.volume() << endl;
  return 0;
}
