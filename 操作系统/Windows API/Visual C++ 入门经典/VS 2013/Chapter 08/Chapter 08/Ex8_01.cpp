// Ex8_01.cpp
// Class with an explicit destructor
#include <iostream>
using std::cout;
using std::endl;

class CBox                     // Class definition at global scope
{
public:
  // Destructor definition
  ~CBox()
  {
    cout << "Destructor called." << endl;
  }

  // Constructor definition
  explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
    m_Length{ lv }, m_Width{ wv }, m_Height{ hv }
  {
    cout << "Constructor called." << endl;
  }

  // Function to calculate the volume of a box
  double volume() const
  {
    return m_Length*m_Width*m_Height;
  }

  // Function to compare two boxes which returns true
  // if the first is greater than the second, and false otherwise
  bool compare(const CBox* pBox) const
  {
    if (!pBox)
      return false;
    return this->volume() > pBox->volume();
  }

private:
  double m_Length;               // Length of a box in inches
  double m_Width;                // Width of a box in inches
  double m_Height;               // Height of a box in inches
};

// Function to demonstrate the CBox class destructor in action
int main()
{
  CBox boxes[5];                 // Array of CBox objects defined
  CBox cigar{ 8.0, 5.0, 1.0 };   // Define cigar box
  CBox match{ 2.2, 1.1, 0.5 };   // Define match box
  CBox* pB1{ &cigar };           // Initialize pointer to cigar object address
  CBox* pB2{};                   // Pointer to CBox initialized to nullptr

  cout << "Volume of cigar is " << pB1->volume() << endl;

  pB2 = boxes;                   // Set to address of array
  boxes[2] = match;              // Set 3rd element to match

  cout << "Volume of boxes[2] is " << (pB2 + 2)->volume() << endl;

  return 0;
}
