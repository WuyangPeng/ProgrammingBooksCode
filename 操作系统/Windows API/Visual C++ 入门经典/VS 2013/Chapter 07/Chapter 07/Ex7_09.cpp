// Ex7_09.cpp
// Initializing an object with an object of the same class
#include <iostream>
using std::cout;
using std::endl;

class CBox                             // Class definition at global scope
{
public:
  // Constructor definition
  explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv }
  {
    cout << "Constructor called." << endl;
  }

  // Function to calculate the volume of a box
  double volume()
  {
    return m_Length*m_Width*m_Height;
  }

private:
  double m_Length;                     // Length of a box in inches
  double m_Width;                      // Width of a box in inches
  double m_Height;                     // Height of a box in inches
};

int main()
{
  CBox box1{ 78.0, 24.0, 18.0 };
  CBox box2{ box1 };                   // Initialize box2 with box1

  cout << "box1 volume = " << box1.volume() << endl
    << "box2 volume = " << box2.volume() << endl;

  return 0;
}
