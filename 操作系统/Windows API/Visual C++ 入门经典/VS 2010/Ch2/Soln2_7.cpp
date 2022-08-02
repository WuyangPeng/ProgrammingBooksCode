// Soln2_7.cpp : main project file.

#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
  double length1 = 10.5;            // Length of room1
  double width1 = 17.6;             // Width of room1
  double area1 = length1*width1;    // Calculate area
  Console::WriteLine(L"Area of room1 is {0} ", Math::Round(area1));

  double length2 = 12.7;            // Length of room2
  double width2 = 18.9;             // Width of room2
  double area2 = length2*width2;    // Calculate area
  Console::WriteLine(L"Area of room2 is {0} ", Math::Round(area2));

  double length3 = 10.5;            // Length of room3
  double width3 = 17.6;             // Width of room3
  double area3 = length3*width3;    // Calculate area
  Console::WriteLine(L"Area of room3 is {0} ", Math::Round(area3));

  double totalArea = area1 + area2 + area3;
  Console::WriteLine(L"Total area of three rooms is {0} ", Math::Round(totalArea));
  Console::WriteLine(L"Average room area is {0} ", Math::Round(totalArea/3.0));

  Console::ReadLine();
  return 0;
}
