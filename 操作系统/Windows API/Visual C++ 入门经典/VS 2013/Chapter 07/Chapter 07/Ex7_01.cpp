// Ex7_01.cpp
// Exercising structures in the yard
#include <iostream>
using std::cout;
using std::endl;

// Definition of a struct to represent rectangles
struct Rectangle
{
  int left;                                        // Top-left point
  int top;                                         // coordinate pair

  int right;                                       // Bottom-right point
  int bottom;                                      // coordinate pair
};

// Prototype of function to calculate the area of a rectangle
long area(const Rectangle& aRect);

// Prototype of a function to move a rectangle
void moveRect(Rectangle& aRect, const int x, const int y);

int main(void)
{
  Rectangle yard{ 0, 0, 100, 120 };
  Rectangle pool{ 30, 40, 70, 80 };
  Rectangle hut1, hut2;

  hut1.left = 70;
  hut1.top = 10;
  hut1.right = hut1.left + 25;
  hut1.bottom = 30;

  hut2 = hut1;                                     // Define hut2 the same as hut1
  moveRect(hut2, 10, 90);                          // Now move it to the right position

  cout << "Coordinates of hut2 are "
    << hut2.left << "," << hut2.top << " and "
    << hut2.right << "," << hut2.bottom << endl;

  cout << "The area of the yard is " << area(yard) << endl;

  cout << "The area of the pool is " << area(pool) << endl;

  return 0;
}

// Function to calculate the area of a rectangle
long area(const Rectangle& aRect)
{
  return (aRect.right - aRect.left)*(aRect.bottom - aRect.top);
}

// Function to Move a Rectangle
void moveRect(Rectangle& aRect, const int x, const int y)
{
  const int length{ aRect.right - aRect.left };    // Get length of rectangle
  const int width{ aRect.bottom - aRect.top };     // Get width of rectangle

  aRect.left = x;                                  // Set top-left point
  aRect.top = y;                                   // to new position
  aRect.right = x + length;                        // Get bottom-right point as
  aRect.bottom = y + width;                        // increment from new position
  return;
}
