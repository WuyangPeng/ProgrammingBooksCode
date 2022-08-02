#include <iostream>

using namespace std;

/**
   A class that describes triangle shapes like this:
   []
   [][]
   [][][]
   . . .
*/   
class Triangle
{
public:
   Triangle(int w);
   int get_area() const;
private:
   int width;  
};

/**
   Constructs a triangle with a given width.
   @param w the width of the triangle base
*/
Triangle::Triangle(int w)
{
   width = w;
}

/**
   Computes the area of the triangle shape.
   @return the area
*/
int Triangle::get_area() const
{
   if (width <= 0) return 0;
   if (width == 1) return 1;
   Triangle smaller_triangle(width - 1);
   int smaller_area = smaller_triangle.get_area();
   return smaller_area + width;
}

int main()
{
   Triangle t(4);
   cout << "Area: " << t.get_area() << "\n";
   return 0;
}

