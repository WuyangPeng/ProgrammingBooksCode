#ifndef RECTANGLESHAPE_CLASS
#define RECTANGLESHAPE_CLASS

#include "d_shape.h"

// declaration of rectShape class with base class shape
class rectShape: public shape
{
   public:
      rectShape(double x = 0.0, double y = 0.0,
                double len = 0.0, double wid = 0.0,
                shapeColor c = darkgray);
			// constructor. has parameters for the base point,
			// length, width and color

      double getLength() const;
      double getWidth() const;
      void setSides(double len, double wid);
	      // retrieve or set rectangle dimensions

      virtual void draw();
	      // draw the rectangle

   private:
      double length, width;
			// rectangle dimensions

};

rectShape::rectShape(double x, double y, double len, double wid,
                     shapeColor c):
            shape(x,y,c), length(len), width(wid)
{}

double rectShape::getLength() const
{
   return length;
}

double rectShape::getWidth() const
{
   return width;
}

void rectShape::setSides(double len, double wid)
{
   length = len;
   width = wid;
}

void rectShape::draw()
{
   EZDCOLORVAL old_color;
   
   old_color = ezdSetColor(color.convertToEzdColor());

   // execute primitive function and draw the rectangle
   shape_handle = ezdDrawRectangle(baseX, baseY,
                                   baseX+length,baseY+width);

   ezdSetColor(old_color);
}

#endif   // RECTANGLESHAPE_CLASS
