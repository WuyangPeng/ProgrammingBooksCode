#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

// maintains measurement properties of a rectangle
class rectangle
{
	public:
		// constructor. initializes length and width
		rectangle(double len = 0.0, double wid  = 0.0): length(len), width(wid)
		{}

		// return the area (length * width)
		double area() const
		{ return length * width; }

		// return the perimeter (2 * (length + width))
		double perimeter() const
		{ return 2 * (length + width); }

		// change the dimensions of the rectangle to len and wid
		void setSides(double len, double wid)
		{
			length = len;
			width = wid;
		}

		// return the length of the rectangle
		double getLength() const
		{ return length; } 

		// return the width of the rectangle
		double getWidth() const
		{ return width; } 
	private:
		double length, width;
};

#endif   // RECTANGLE_CLASS
