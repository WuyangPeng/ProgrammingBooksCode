// Ex6_05.cpp
// Nested try blocks
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
        
int main()
{
  int height {};
  const int minHeight { 9 };                     // Minimum height in inches
  const int maxHeight { 100 };                   // Maximum height in inches
  const double inchesToMeters { 0.0254 };
  char ch { 'y' };
        
  try                                            // Outer try block
  {
    while('y' == ch || 'Y' == ch)
    {
      cout << "Enter a height in inches: ";
      cin >> height;                             // Read the height to be
                                                 // converted
        
      try                                        // Defines try block in which
      {                                          // exceptions may be thrown
        if(height > maxHeight)
           throw "Height exceeds maximum";       // Exception thrown
        if(height < minHeight)
           throw height;                         // Exception thrown
        
         cout << static_cast<double>(height)*inchesToMeters
              << " meters" << endl;
      }
      catch(const char aMessage[])               // start of catch block which
      {                                          // catches exceptions of type
        cout << aMessage << endl;                // const char[]
      }
      cout << "Do you want to continue(y or n)?";
      cin >> ch;
    }
  }
  catch(int badHeight)
  {
    cout << badHeight << " inches is below minimum" << endl;
  }
  return 0;
}
