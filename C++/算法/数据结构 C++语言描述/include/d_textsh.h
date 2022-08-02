#ifndef TEXT_SHAPE_CLASS
#define TEXT_SHAPE_CLASS

#include <string>
#include "d_shape.h"

using namespace std;

class textShape: public shape
{
   public:
      textShape(double x = 0.0, double y = 0.0,
                const string& s ="", shapeColor c = darkgray);
			// constructor. has arguments for the base point,
			// text string and color

      string getText() const;
      void setText(const string& s);
	      // retrieve or set the text
      
      virtual void draw();
			// draw the text

   private:
      string text;
			// text to draw
};

textShape::textShape(double x, double y, const string& s,
                     shapeColor c):
   shape(x,y,c), text(s)
{}
      
string textShape::getText() const
{
   return text;
}

void textShape::setText(const string& s)
{
   text = s;
}

void textShape::draw()
{
   EZDCOLORVAL old_color;
   
   old_color = ezdSetColor(color.convertToEzdColor());
   // execute primitive function and draw the text
   shape_handle = ezdDrawText(text.c_str(), baseX, baseY);
   ezdSetColor(old_color);
}

#endif   // TEXT_SHAPE_CLASS
