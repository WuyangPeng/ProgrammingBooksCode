// Ex7_10.cpp
// Using the pointer this
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

  // Function to compare two boxes which returns true
  // if the first is greater than the second, and false otherwise
  bool compare(CBox& xBox)
  {
    return this->volume() > xBox.volume();
  }

private:
  double m_Length;                   // Length of a box in inches
  double m_Width;                    // Width of a box in inches
  double m_Height;                   // Height of a box in inches
};

int main()
{
  CBox match{ 2.2, 1.1, 0.5 };           // Define match box
  CBox cigar{ 8.0, 5.0, 1.0 };           // Define cigar box

  if (cigar.compare(match))
    cout << "match is smaller than cigar" << endl;
  else
    cout << "match is equal to or larger than cigar" << endl;

  return 0;
}
