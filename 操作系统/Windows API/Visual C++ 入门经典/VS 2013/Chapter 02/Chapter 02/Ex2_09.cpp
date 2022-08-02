// Ex2_09.cpp
// Demonstrating type-safe and non-type-safe enumerations
#include <iostream>
        
using std::cout;
using std::endl;
        
// You can define enumerations at global scope
//enum Jewels {Diamonds, Emeralds, Rubies};  // Uncomment this for an error
enum Suit : long {Clubs, Diamonds, Hearts, Spades};
        
int main()
{
  // Using the old enumeration type...
  Suit suit{ Clubs };                        // You can use old enumerator names directly
  Suit another{ Suit::Diamonds };            // or you can qualify them

  // Automatic conversion from enumeration type to integer
   cout << "suit value: " << suit << endl;
   cout << "Add 10 to another: " << another + 10 << endl;

   // Using type-safe enumerations...
   enum class Color : char { Red, Orange, Yellow, Green, Blue, Indigo, Violet };
   Color skyColor{ Color::Blue };             // You must qualify enumerator names
   // Color grassColor{ Green };              // Uncomment for an error

   // No auto conversion to numeric type
   cout << endl
        << "Sky color value: "
        << static_cast<long>(skyColor) << endl;
   
   //cout << skyColor + 10L << endl;         // Uncomment for an error
   cout << "Incremented sky color: "
        << static_cast<long>(skyColor) + 10L // OK with explicit cast
        << endl;

   return 0;
} 
