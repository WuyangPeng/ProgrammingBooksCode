// Ex7_08.cpp
// Creating a friend function of a class
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;

class CBox                             // Class definition at global scope
{
public:
  // Constructor definition
  CBox(double lv, double wv, double hv) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv }
  {
    cout << "3-arg Constructor called." << endl;
  }

  explicit CBox(double side) : CBox{ side, side, side }
  {
    cout << "1-arg Constructor called." << endl;
  }

  CBox() = default;

  // Function to calculate the volume of a box
  double volume()
  {
    return m_Length*m_Width*m_Height;
  }

private:
  double m_Length;                     // Length of a box in inches
  double m_Width;                      // Width of a box in inches
  double m_Height;                     // Height of a box in inches

  // Friend function
  friend double boxSurface(const CBox& aBox);
};

// friend function to calculate the surface area of a Box object
double boxSurface(const CBox& aBox)
{
  return 2.0*(aBox.m_Length*aBox.m_Width +
    aBox.m_Length*aBox.m_Height +
    aBox.m_Height*aBox.m_Width);
}

int main()
{
  CBox match{ 2.2, 1.1, 0.5 };          // match box using 3-arg constructor
  CBox cube{ 5.0 };                     // Define cube using 1-arg constructor
  CBox box;                             // Define box using default constructor 

  cout << "Volume of match =" << setw(10) << match.volume()
    << "   Surface area = " << boxSurface(match) << endl;


  cout << setw(16) << "Volume of cube  =" << setw(10) << cube.volume()
    << "   Surface area = " << boxSurface(cube) << endl;

  cout << "Volume of box   =" << setw(10) << box.volume()
    << "   Surface area = " << boxSurface(box) << endl;

  return 0;
}
