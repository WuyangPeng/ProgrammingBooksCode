#ifndef CIRCLESHAPE_CLASS
#define CIRCLESHAPE_CLASS

#include "d_shape.h"

// declaration of circleShape class with base class shape
class circleShape: public shape
{
   public:
      circleShape(double x = 0.0, double y = 0.0,
                  double r = 0.0, shapeColor c = darkgray);
	      // arguments for the base point, radius and color

      double getRadius() const;
      void setRadius(double r);
	      // retrieve or set the radius

      virtual void draw();
	      // draw the circle

   private:
      double radius;
			// radius of the circle
};

circleShape::circleShape(double x, double y, double r,
                     shapeColor c): shape(x,y,c), radius(r)
{}

// read the radius value; return value of private radius data
double circleShape::getRadius() const
{
   return radius;
}

// change the radius value of the current object
void circleShape::setRadius(double r)
{
   radius = r;          // assign r as the new radius
}

// draw the circleShape with center at (x,y), given radius
// and color
void circleShape::draw()
{
   EZDCOLORVAL old_color;
   
   old_color = ezdSetColor(color.convertToEzdColor());
   shape_handle = ezdDrawCircle(baseX, baseY, radius);
   ezdSetColor(old_color);
}

#endif   // CIRCLESHAPE_CLASS
