// Ex7_12.cpp
// Using a static member to count objects
#include <iostream>
using std::cout;
using std::endl;

class CBox                             // Class definition at global scope
{
public:
  static int objectCount;              // Count of objects in existence

  // Constructor definition
  explicit CBox(double lv, double wv = 1.0, double hv = 1.0) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv }
  {
    cout << "Constructor called." << endl;
    objectCount++;
  }

  CBox()                               // Default constructor
  {
    cout << "Default constructor called." << endl;
    m_Length = m_Width = m_Height = 1.0;
    objectCount++;
  }

  // Function to calculate the volume of a box
  double volume() const
  {
    return m_Length*m_Width*m_Height;
  }

private:
  double m_Length;                     // Length of a box in inches
  double m_Width;                      // Width of a box in inches
  double m_Height;                     // Height of a box in inches
};

int CBox::objectCount{};              // Initialize static member of CBox class

int main()
{
  CBox boxes[5];                       // Array of CBox objects defined
  CBox cigar{ 8.0, 5.0, 1.0 };         // Declare cigar box

  cout << "Number of objects (accessed through class) = "
    << CBox::objectCount << endl;

  cout << "Number of objects (accessed through object) = "
    << boxes[2].objectCount << endl;

  return 0;
}
