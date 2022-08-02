// Ex8_07.cpp : main project file.
// A ref class with the same functionality as the Ex8_11 example in Chapter 8.

#include "stdafx.h"

using namespace System;

ref class Box
{
public:
   Box()
   {
     Box(1.0, 1.0, 1.0);
   }

   Box(double lv, double wv, double hv)
   {
     lv = lv <= 0.0 ? 1.0 : lv;           // Ensure positive
     wv = wv <= 0.0 ? 1.0 : wv;           // dimensions for
     hv = hv <= 0.0 ? 1.0 : hv;           // the object

     lngth = lv>wv ? lv : wv;             // Ensure that
     wdth = wv<lv ? wv : lv;              // length >= width
     hght = hv;
   }

    double Volume() 
    {
      return lngth*wdth*hght;
    }

   property double height
   {
     double get() { return hght; }
   }

    property double width
   {
     double get() { return wdth; }
   }

     property double length
   {
     double get() { return lngth; }
   }

    // Overloaded addition operator
    Box^ operator+(Box^ box)
    {
    // New object has larger length and width of the two,
    // and sum of the two heights
    return gcnew Box(lngth > box->lngth ? lngth : box->lngth,
                     wdth > box->wdth ? wdth : box->wdth,
                     hght + box->hght);
    }

    // Divide one box into another
    int operator/(Box^ box)
    {
    // Temporary for number in horizontal plane this way
    int tc1 = 0;
    // Temporary for number in a plane that way
    int tc2 = 0;

    tc1 = safe_cast<int>(lngth/box->lngth)*
             safe_cast<int>(wdth/box->wdth); 	 // to fit this way

    tc2 = safe_cast<int>(lngth/box->wdth)*
             safe_cast<int>(wdth/box->lngth);  // and that way

    //Return best fit
    return static_cast<int>(hght/box->hght)*(tc1>tc2 ? tc1 : tc2);
    }

    // Post-multiply a box by an integer
    Box^ operator*(int n)
    {
      if(n%2 == 0)
        return gcnew Box(lngth, 2.0*wdth, (n/2)*hght);   // n even
      else
        return gcnew Box(lngth, wdth, n*hght);           // n odd
    }

    // Operator to return the free volume in a packed Box
    double operator%(Box^ box)
    { return Volume() - (this/box)*box->Volume(); }

    // Function for testing if a Box object is >= a constant
    bool operator>=(double value)
    { return value <= this; }

    // Function for testing if a Box object is <= a constant
    bool operator<=(double value)
    { return value >= this; }

    // Function for testing if a constant is > a Box object
    static bool operator>(double value, Box^ box)
    { return value > box->Volume(); }

    // Function for testing if a constant is < Box object
    static bool operator<(double value, Box^ box)
    { return value < box->Volume(); }

    // Function for testing if a Box object is > a constant
    static bool operator>(Box^ box, double value)
    { return value < box; }

    // Function for testing if a Box object is < a constant
    static bool operator<(Box^ box, double value)
    { return value > box; }

    // Function for testing if a constant is >= a Box object
    static bool operator>=(double value, Box^ box)
    { return value >= box->Volume(); }

    // Function for testing if a constant is <= a Box object
    static bool operator<=(double value, Box^ box)
    { return value <= box->Volume(); }

    // Function for testing if a constant is == Box object
    static bool operator==(double value, Box^ box)
    { return value == box->Volume(); }

    // Function for testing if Box object is == a constant
    static bool operator==(Box^ box, double value)
    { return value == box; }

    // CBox multiply operator n*aBox
    static Box^ operator*(int n, Box^ box)
    { return box*n; }

private:
   
   double lngth;             // Length of a box in inches
   double wdth;              // Width of a box in inches
   double hght;              // Height of a box in inches
};

int main(array<System::String ^> ^args)
{
   Box^ candy = gcnew Box(1.5, 1.0, 1.0);             // Candy definition
   Box^ candyBox = gcnew Box(7.0, 4.5, 2.0);          // Candy box definition
   Box^ carton = gcnew Box(30.0, 18.0, 18.0);         // Carton definition

   // Calculate candies per candy box
   int numCandies = candyBox/candy;

   // Calculate candy boxes per carton
   int numCboxes = carton/candyBox;

   // Calculate wasted carton space
   double space = carton%candyBox;

   Console::WriteLine(L"There are {0} candies per candy box", numCandies);
   Console::WriteLine(L"For the standard boxes there are {0} candy boxes per carton", numCboxes);
   Console::WriteLine(L"with {0} cubic inches wasted.", space);

   Console::Write(L"CUSTOM CANDY BOX ANALYSIS (No Waste)");

   // Try the whole range of custom candy boxes
   for(double length = 3.0 ; length <= 7.5 ; length += 0.5)
      for(double width = 3.0 ; width <= 5.0 ; width += 0.5)
         for(double height = 1.0 ; height <= 2.5 ; height += 0.5)
         {
            // Create new box each cycle
            Box^ tryBox = gcnew Box(length, width, height);

            if(carton%tryBox < tryBox->Volume() &&
                               tryBox % candy == 0.0 && tryBox/candy >= 30)
            {
               Console::Write(L"\n\nTrial Box L = {0}", tryBox->length);
               Console::WriteLine(L" W = {0} H = {1}", tryBox->width, tryBox->height);
               Console::Write(L"Trial Box contains {0} candies", tryBox/candy);
               Console::WriteLine(L" and a carton contains {0} candy boxes.", carton/tryBox);
            }
         }
   Console::WriteLine();
   return 0;
}
