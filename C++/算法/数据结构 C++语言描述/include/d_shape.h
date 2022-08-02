#ifndef GEOMETRIC_FIGURES_BASE
#define GEOMETRIC_FIGURES_BASE

#include "d_draw.h"

// colors of the shapes
enum drawing_color
{
   white,  blue,   teal,      green,     turquoise, darkgray,
   brown,  purple, lightblue, lightgray, gold,      red,
   orange, pink,   yellow,    black
};

#ifdef _MSC_VER

class shapeColor;

bool operator== (const shapeColor& lhs,
                          const shapeColor& rhs);
bool operator!= (const shapeColor& lhs,
                          const shapeColor& rhs);
bool operator< (const shapeColor& lhs,
                          const shapeColor& rhs);
bool operator<= (const shapeColor& lhs,
                          const shapeColor& rhs);
bool operator> (const shapeColor& lhs,
                          const shapeColor& rhs);
bool operator>= (const shapeColor& lhs,
                          const shapeColor& rhs);
#endif	// _MSC_VER

// wrapper class for the colors
class shapeColor
{
   public:
      // constructor
      shapeColor(drawing_color c = blue);

      // increment and decrement operators
      shapeColor operator++ (int);
      shapeColor& operator++ ();
      shapeColor operator-- (int);
      shapeColor& operator-- ();

      // relational operators
      friend bool operator== (const shapeColor& lhs,
                          const shapeColor& rhs);
      friend bool operator!= (const shapeColor& lhs,
                          const shapeColor& rhs);
      friend bool operator< (const shapeColor& lhs,
                          const shapeColor& rhs);
      friend bool operator<= (const shapeColor& lhs,
                          const shapeColor& rhs);
      friend bool operator> (const shapeColor& lhs,
                          const shapeColor& rhs);
      friend bool operator>= (const shapeColor& lhs,
                          const shapeColor& rhs);

      // convert to Windows definition for colors
      ezdColor convertToEzdColor();

   private:
      drawing_color color;

      // table defining conversion from simple colors
      // to necessary Windows definitions
      static const ezdColor g_aColors[];

};

// ***********************************************************
//      shapeColor class implementation
// ***********************************************************

// color conversion lookup table
const ezdColor shapeColor::g_aColors[] = {
   ezdWhite,
   ezdBlue,
   ezdTeal,
   ezdGreen,
   ezdTurquoise,
   ezdDarkGray,
   ezdBrown,
   ezdPurple,
   ezdLightBlue,
   ezdLightGray,
   ezdGold,
   ezdRed,
   ezdOrange,
   ezdPink,
   ezdYellow,
   ezdBlack
};

// constructor. initialize color
shapeColor::shapeColor(drawing_color c): color(c)
{}

// postfix increment
shapeColor shapeColor::operator++ (int)
{
   drawing_color origColor = color;

   color = drawing_color((color+1) % 16);
   return shapeColor(origColor);
}

// prefix increment
shapeColor& shapeColor::operator++ ()
{
   color = drawing_color((color+1) % 16);
   return *this;
}

// postfix decrement
shapeColor shapeColor::operator-- (int)
{
   drawing_color origColor = color;

   if (color == black)
      color = white;
   else
      color = drawing_color(color-1);
   return shapeColor(origColor);
}

// prefix decrement
shapeColor& shapeColor::operator-- ()
{
   if (color == black)
      color = white;
   else
      color = drawing_color(color-1);
   return *this;
}

// use lookup table to convert to Windows color definitions
ezdColor shapeColor::convertToEzdColor()
{
   return g_aColors[color];
}

// relational operators
bool operator== (const shapeColor& lhs,
                 const shapeColor& rhs)
{
   return lhs.color == rhs.color;
}

bool operator!= (const shapeColor& lhs,
                 const shapeColor& rhs)
{
   return lhs.color != rhs.color;
}

bool operator< (const shapeColor& lhs,
                const shapeColor& rhs)
{
   return lhs.color < rhs.color;
}

bool operator<= (const shapeColor& lhs,
                 const shapeColor& rhs)
{
   return lhs.color <= rhs.color;
}

bool operator> (const shapeColor& lhs,
                const shapeColor& rhs)
{
   return lhs.color > rhs.color;
}

bool operator>= (const shapeColor& lhs,
                 const shapeColor& rhs)
{
   return lhs.color >= rhs.color;
}

// the graphics base class. maintains the base point and fill
// color. has functions to access and change these attributes.
// the graphics classes that draw specific figures inherit
// this class
class shape
{
   public:
      shape(double x, double y, shapeColor c);
		//	the arguments initialize the base point (x,y) and the fill color c

      virtual ~shape();
	      // virtual destructor may be necessary for derived class

      double getX() const;
			// returns the x coordinate of the base point
      double getY() const;
			// returns the y coordinate of the base point

      void move(double x, double y);
			// repositions the base point to the new coordinates (x,y)

      shapeColor getColor() const;
			// returns the current fill color for the figure
      void setColor(shapeColor c);
			// set the fill color of the figure to the value c from the
			// color palette

      virtual void draw() = 0;
	      // draw the shape. must be implemented in a derived class
      
      void erase();
			// removes the figure from the drawing surface

      virtual void update();
	      // update the shape

   protected:
     // location of the base point
      double baseX, baseY;

      // color of the shape
      shapeColor color;

     // handle to the shape
     EZDHANDLE shape_handle;
};

// ***********************************************************
//      shape class implementation
// ***********************************************************

// initialize basepoint coordinates and color.
// specify that no shape has been drawn by setting
// shape_handle to 0
shape::shape(double x, double y, shapeColor c):
      baseX(x), baseY(y), color(c), shape_handle(0)
{}

shape::~shape() {}

double shape::getX() const
{
   return baseX;
}

double shape::getY() const
{
   return baseY;
}

shapeColor shape::getColor() const
{
   return color;
}

void shape::setColor(shapeColor c)
{
   color = c;
}

void shape::move(double x, double y)
{
   baseX = x;
   baseY = y;
}

void shape::erase()
{
   // shape_handle identifies the shape in the window.
   // the shape is defined if shape_handle is not 0
   if (shape_handle != 0)
      ezdDeleteShape(shape_handle); // erase the shape
   shape_handle = 0;                // no shape defined
}

void shape::update()
{
   erase();
   draw();
}

 #endif   // GEOMETRIC_FIGURES_BASE
