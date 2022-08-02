// Ex8_10.cpp
// Using a class template
#include <iostream>
#include <utility>                                             // For operator overload templates
#include <algorithm>                                           // For max(), swap() used in CBox
using std::cout;
using std::endl;
using namespace std::rel_ops;

class CBox                                                      // Class definition at global scope
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
  double m_Length;                                              // Length of a box in inches
  double m_Width;                                               // Width of a box in inches
  double m_Height;                                              // Height of a box in inches
};

// CSamples class template definition
template <typename T> class CSamples
{
public:
  // Constructors
  CSamples(const T values[], int count);
  CSamples(const T& value);
  CSamples(T&& value);
  CSamples() = default;

  bool add(const T& value);                                     // Insert a value
  bool add(T&& value);                                          // Insert a value with move semantics
  T max() const;                                                // Calculate maximum

private:
  static const size_t maxSamples{ 100 };                        // Maximum number of samples
  T m_Values[maxSamples];                                       // Array to store samples
  int m_Next{};                                               // Index of free location in m_Values
};

// Constructor template definition to accept an array of samples
template<typename T> CSamples<T>::CSamples(const T values[], int count)
{
  m_Next = count < maxSamples ? count : maxSamples;             // Don't exceed the array
  for (int i{}; i < m_Next; i++)                                // Store count of samples
    m_Values[i] = values[i];
}

// Constructor to accept a single sample
template<typename T> CSamples<T>::CSamples(const T& value)
{
  m_Values[0] = value;                                          // Store the sample
  m_Next = 1;                                                   // Next is free
}

// Constructor to accept a temporary sample
template<typename T> CSamples<T>::CSamples(T&& value)
{
  cout << "Move constructor." << endl;
  m_Values[0] = std::move(value);                               // Store the sample
  m_Next = 1;                                                   // Next is free
}

// Function to add a sample
template<typename T> bool CSamples<T>::add(const T& value)
{
  cout << "Add." << endl;
  bool OK{ m_Next < maxSamples };                               // Indicates there is a free place
  if (OK)
    m_Values[m_Next++] = value;                                 // OK true, so store the value
  return OK;
}

template<typename T> bool CSamples<T>::add(T&& value)
{
  cout << "Add move." << endl;
  bool OK{ m_Next < maxSamples };                             // Indicates there is a free place
  if (OK)
    m_Values[m_Next++] = std::move(value);                    // OK true, so store the value
  return OK;
}

// Function to obtain maximum sample
template<typename T> T CSamples<T>::max() const
{
  T theMax{ m_Values[0] };                                    // Set first sample as maximum
  for (int i{ 1 }; i < m_Next; i++)                           // Check all the samples
  if (theMax < m_Values[i])
    theMax = m_Values[i];                                     // Store any larger sample
  return theMax;
}

int main()
{
  CBox boxes[]  {                                             // Create an array of boxes
    CBox{ 8.0, 5.0, 2.0 },                                    // Initialize the boxes...
      CBox{ 5.0, 4.0, 6.0 },
      CBox{ 4.0, 3.0, 3.0 }
  };

  // Create the CSamples object to hold CBox objects
  CSamples<CBox> myBoxes{ boxes, _countof(boxes) };

  CBox maxBox{ myBoxes.max() };                               // Get the biggest box
  cout << "The biggest box has a volume of "                  // and output its volume
    << maxBox.volume() << endl;
  CSamples<CBox> moreBoxes{ CBox{ 8.0, 5.0, 2.0 } };
  moreBoxes.add(CBox{ 5.0, 4.0, 6.0 });
  moreBoxes.add(CBox{ 4.0, 3.0, 3.0 });
  cout << "The biggest box has a volume of "
    << moreBoxes.max().volume() << endl;
  return 0;
}
