#ifndef LINESHAPE_CLASS
#define LINESHAPE_CLASS

#include "d_shape.h"

// declaration of lineShape class with base class shape
class lineShape: public shape
{
   public:
      lineShape(double x = 0.0, double y = 0.0,
                double x2 = 0.0, double y2 = 0.0,
                shapeColor c = darkgray);
			// constructor. has arguments for base point,
			// the second point on the line and the color

      // line data access member functions
      double getEndX() const;
      double getEndY() const;
      void setEndPoint(double x, double y);
	      // retrieve or set length of the second point

      virtual void draw();
	      // draw the line

   private:
      double endX, endY;
	      // second point on the line
};

lineShape::lineShape(double x, double y, double x2, double y2,
                     shapeColor c):
        shape(x,y,c), endX(x2), endY(y2)
{}

double lineShape::getEndX() const
{
   return endX;
}

double lineShape::getEndY() const
{
   return endY;
}

// change the end point. must recompute length
void lineShape::setEndPoint(double x, double y)
{
   endX = x;
   endY = y;
}

void lineShape::draw()
{
   EZDCOLORVAL old_color;
   
   old_color = ezdSetColor(color.convertToEzdColor());
   shape_handle = ezdDrawLine(baseX, baseY, endX, endY);
   ezdSetColor(old_color);
}

#endif   // LINESHAPE_CLASS
