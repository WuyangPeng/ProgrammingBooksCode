// Ex7_07.cpp
// A class with private members
#include <iostream>
using std::cout;
using std::endl;

class CBox                             // Class definition at global scope
{
public:
  // Constructor definition using an initialization list
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
  double m_Length;                   // Length of a box in inches
  double m_Width;                    // Width of a box in inches
  double m_Height;                   // Height of a box in inches
};

int main()
{
  CBox match{ 2.2, 1.1, 0.5 };        // Declare match box
  CBox box2;                         // Declare box2 - no initial values

  cout << "Volume of match = " << match.volume() << endl;

  // Uncomment the following line to get an error
  // box2.m_Length = 4.0;

  cout << "Volume of box2 = " << box2.volume() << endl;

  return 0;
}
