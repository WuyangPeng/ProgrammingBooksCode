// Ex7_11.cpp
// Using an array of class objects
#include <iostream>
using std::cout;
using std::endl;
class CBox                             // Class definition at global scope
{
public:
  // Constructor definition
  explicit CBox(double lv, double wv = 1.0, double hv = 1.0) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv }
  {
    cout << "Constructor called." << endl;
  }

  CBox()                             // Default constructor
  {
    cout << "Default constructor called." << endl;
    m_Length = m_Width = m_Height = 1.0;
  }

  // Function to calculate the volume of a box
  double volume() const
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
  CBox boxes[5];                       // Array of CBox objects declared
  CBox cigar(8.0, 5.0, 1.0);           // Define cigar box
  cout << "Volume of boxes[3] = " << boxes[3].volume() << endl
    << "Volume of cigar = " << cigar.volume() << endl;

  return 0;
}
