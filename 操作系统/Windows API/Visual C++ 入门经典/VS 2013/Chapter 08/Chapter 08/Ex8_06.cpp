// Ex8_06.cpp
// Adding CBox objects
#include <iostream>                    // For stream I/O
#include <algorithm>                   // For min(), max() and swap()
#include <utility>                     // For operator templates
using std::cout;
using std::endl;
using namespace std::rel_ops;

class CBox                             // Class definition at global scope
{
public:
  // Constructor definition
  explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
    m_Length{ std::max(lv, wv) }, m_Width{ std::min(lv, wv) }, m_Height{ hv }
  {
    // height is <= width
    // We need to ensure the height is <= width is <= length
    if (m_Height > m_Length)
    { // height greater than length, so swap them
      std::swap(m_Height, m_Length);
      std::swap(m_Width, m_Height);
    }
    else if (m_Height > m_Width)
    { // height less than or equal to length but greater than width so swap
      std::swap(m_Height, m_Width);
    }
  }

  // Function to calculate the volume of a box
  double volume() const
  {
    return m_Length*m_Width*m_Height;
  }

  // Operator function for 'less than' that
  // compares volumes of CBox objects.
  bool operator<(const CBox& aBox) const
  {
    return this->volume() < aBox.volume();
  }

  // 'Less than' operator function to compare a CBox object volume with a constant
  bool operator<(const double value) const
  {
    return this->volume() < value;
  }

  // 'Greater than' function to compare a CBox object volume with a constant
  bool operator>(const double value) const
  {
    return this->volume() > value;
  }

  // Overloaded equality operator
  bool operator==(const CBox& aBox) const
  {
    return this->volume() == aBox.volume();
  }

  // Function to add two CBox objects
  CBox operator+(const CBox& aBox) const
  {
    // New object has larger length & width, and sum of heights
    return CBox(std::max(m_Length, aBox.m_Length),
      std::max(m_Width, aBox.m_Width),
      m_Height + aBox.m_Height);
  }

  // Function to show the dimensions of a box
  void showBox() const
  {
    cout << m_Length << " " << m_Width << " " << m_Height << endl;
  }

private:
  double m_Length;                     // Length of a box in inches
  double m_Width;                      // Width of a box in inches
  double m_Height;                     // Height of a box in inches
};

// Function comparing a constant with a CBox object
inline bool operator>(const double value, const CBox& aBox)
{
  return value > aBox.volume();
}

int main()
{
  CBox smallBox{ 4.0, 2.0, 1.0 };
  CBox mediumBox{ 10.0, 4.0, 2.0 };
  CBox aBox;
  CBox bBox;
  cout << "smallBox dimensions are ";
  smallBox.showBox();
  cout << "mediumBox dimensions are ";
  mediumBox.showBox();
  aBox = smallBox + mediumBox;
  cout << "aBox dimensions are ";
  aBox.showBox();
  bBox = aBox + smallBox + mediumBox;
  cout << "bBox dimensions are ";
  bBox.showBox();
  return 0;
}
