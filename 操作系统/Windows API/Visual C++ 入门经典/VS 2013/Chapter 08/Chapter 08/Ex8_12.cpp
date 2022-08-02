// Ex8_12.cpp
// Default values for class template parameters
#include <iostream>
#include <utility>                                                   // For operator overload templates
#include <algorithm>                                                 // For max(), swap() used in CBox
using std::cout;
using std::endl;
using namespace std::rel_ops;

class CBox                                                           // Class definition at global scope
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
  double m_Length;                                                   // Length of a box in inches
  double m_Width;                                                    // Width of a box in inches
  double m_Height;                                                   // Height of a box in inches
};
// CSamples class template definition
template <typename T = double, size_t Size = 100> class CSamples
{
public:
  // Constructors
  CSamples(const T values[], int count);
  CSamples(const T& value);
  CSamples(T&& value);
  CSamples() = default;

  bool add(const T& value);                                          // Insert a value
  bool add(T&& value);                                               // Insert a value with move semantics
  T max() const;                                                     // Calculate maximum

private:
  T m_Values[Size];                                                  // Array to store samples
  int m_Next{};                                                      // Index of free location in m_Values
};

// Constructor template definition to accept an array of samples
template<typename T, size_t Size>
CSamples<T, Size>::CSamples(const T values[], int count)
{
  m_Next = count < Size ? count : Size;                              // Don't exceed the array
  for (int i{}; i < m_Next; i++)                                     // Store count of samples
    m_Values[i] = values[i];
}

// Constructor to accept a single sample
template<typename T, size_t Size>
CSamples<T, Size>::CSamples(const T& value)
{
  m_Values[0] = value;                                               // Store the sample
  m_Next = 1;                                                        // Next is free
}

// Constructor to accept a temporary sample
template<typename T, size_t Size>
CSamples<T, Size>::CSamples(T&& value)
{
  cout << "Move constructor." << endl;
  m_Values[0] = std::move(value);                                    // Store the sample
  m_Next = 1;                                                        // Next is free
}

// Function to add a sample
template<typename T, size_t Size>
bool CSamples<T, Size>::add(const T& value)
{
  cout << "Add." << endl;
  bool OK{ m_Next < Size };                                          // Indicates there is a free place
  if (OK)
    m_Values[m_Next++] = value;                                      // OK true, so store the value
  return OK;
}

template<typename T, size_t Size>
bool CSamples<T, Size>::add(T&& value)
{
  cout << "Add move." << endl;
  bool OK{ m_Next < Size };                                          // Indicates there is a free place
  if (OK)
    m_Values[m_Next++] = std::move(value);                           // OK true, so store the value
  return OK;
}

// Function to obtain maximum sample
template<typename T, size_t Size>
T CSamples<T, Size>::max() const
{
  T theMax{ m_Values[0] };                                           // Set first sample as maximum
  for (int i{ 1 }; i < m_Next; i++)                                  // Check all the samples
  if (theMax < m_Values[i])
    theMax = m_Values[i];                                            // Store any larger sample
  return theMax;
}

int main()
{
  CBox boxes[]  {                                                    // Create an array of boxes
    CBox{ 8.0, 5.0, 2.0 },                                           // Initialize the boxes...
      CBox{ 5.0, 4.0, 6.0 },
      CBox{ 4.0, 3.0, 3.0 }
  };

  // Create the CSamples object to hold CBox objects
  CSamples<CBox> myBoxes{ boxes, _countof(boxes) };

  CBox maxBox{ myBoxes.max() };                                      // Get the biggest box
  cout << "The biggest box has a volume of "                         // and output its volume
    << maxBox.volume() << endl;

  double values[] { 2.5, 3.6, 4.7, -15.0, 6.8, 7.2, -8.1 };
  CSamples<> data{ values, _countof(values) };
  cout << "Maximum double value = " << data.max() << endl;

  // Uncomment next line for an error
  // CSamples <, _countof(values)> baddata{ values, _countof(values) }; 

  int counts[] { 21, 32, 444, 15, 6, 7, 8 };
  CSamples<int, _countof(counts)> dataset{ counts, _countof(counts) };
  cout << "Maximum int value = " << dataset.max() << endl;

  return 0;
}
