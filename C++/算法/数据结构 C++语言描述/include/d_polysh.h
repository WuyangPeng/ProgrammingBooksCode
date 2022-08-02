#ifndef POLYGONSHAPE_CLASS
#define POLYGONSHAPE_CLASS

#include <vector>
#include <cmath>

#include "d_shape.h"

using namespace std;

// declaration of polygonShape class with base class shape
class polyShape: public shape
{
   public:
      polyShape(double x = 0.0, double y = 0.0,
                int n = 4, double len = 0.0,
                shapeColor c = darkgray);
			// constructor. has arguments for the base point,
			// number of sides, the length of each side and the
			// color

      double getLength() const;
      void setLength(double len);
	      // retrieve or set length of a side

      int getN();
      void setN(int numsides);
	      // retrieve or set number of sides

      virtual void draw();
	      // draw the polygon

   private:
      int numSides;
			// number of sides
      double length;
			// length of each side

      vector<double> point_X;
      vector<double> point_Y;
	      // x and y-coordinates of the vertices

      void buildPoints();
	      // construct the vertices
};

void polyShape::buildPoints()
{
   int side;
   double theta, d;
   const double PI = 3.141592653589793,
                DELTA_THETA = (2.0*PI)/numSides;

   // allocate space for the numSides coordinates
   point_X.resize(numSides);
   point_Y.resize(numSides);

   d = length/(2.0*sin(PI/numSides));
   theta = 0.0;
   for(side = 0; side < numSides; side++)
   {
      point_X[side] = baseX + d*cos(theta);
      point_Y[side] = baseY - d*sin(theta);
      theta += DELTA_THETA;
   }
}

// initialize base class, the number of sides
// and the length of each side
polyShape::polyShape(double x, double y, int n,
                     double len, shapeColor c):
         shape(x,y,c), numSides(n), length(len),
         point_X(0), point_Y(0)
{}

double polyShape::getLength() const
{
   return length;
}

// change the length of a side
void polyShape::setLength(double len)
{
   length = len;
}

int polyShape::getN()
{
   return numSides;
}

void polyShape::setN(int n)
{
   numSides = n;
}

void polyShape::draw()
{
   EZDCOLORVAL old_color;
   
   // build the polygon's points and draw it
   buildPoints();
   old_color = ezdSetColor(color.convertToEzdColor());
   shape_handle = ezdDrawPolygon(numSides, &point_X[0], &point_Y[0]);
   ezdSetColor(old_color);
}

#endif   // POLYGONSHAPE_CLASS
