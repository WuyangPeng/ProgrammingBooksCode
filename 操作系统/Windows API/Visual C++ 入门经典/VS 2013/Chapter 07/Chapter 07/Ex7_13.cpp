// Ex7_13.cpp
// Exercising the indirect member access operator
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
  double m_Length;                                  // Length of a box in inches
  double m_Width;                                   // Width of a box in inches
  double m_Height;                                  // Height of a box in inches
};
int main()
{
  CBox boxes[5];                                    // Array of CBox objects defined
  CBox match{ 2.2, 1.1, 0.5 };                      // Declare match box
  CBox cigar{ 8.0, 5.0, 1.0 };                      // Declare cigar Box
  CBox* pB1{ &cigar };                              // Initialize pointer to cigar object address
  CBox* pB2{};                                      // Pointer to CBox initialized to nullptr
  cout << "Address of cigar is " << pB1 << endl     // Display address
    << "Volume of cigar is " << pB1->volume()       // Volume of object pointed to
    << endl;
  pB2 = &match;

  if (pB2->compare(pB1))                            // Compare via pointers
    cout << "match is greater than cigar" << endl;
  else
    cout << "match is less than or equal to cigar" << endl;

  pB1 = boxes;                                      // Set to address of array
  boxes[2] = match;                                 // Set 3rd element to match

  // Now access through pointer
  cout << "Volume of boxes[2] is " << (pB1 + 2)->volume() << endl;
  return 0;
}
