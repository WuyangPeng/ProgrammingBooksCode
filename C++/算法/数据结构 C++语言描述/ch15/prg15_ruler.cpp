// File: prg15_ruler.cpp
// the program uses the lineShape and textShape objects
// from the drawing package of Chapter 13 to demonstrate
// the divide and conquer recursive function drawRuler().
// that makes marks every 1/2**h units in the range (low,high).
// to make the marks, drawRuler() calls drawMark() whose arguments
// include the position of the midpoint and h. the height of the mark
// depends on the argument h

#include <string>

#include "d_draw.h"		// drawing library
#include "d_linesh.h"	// lineShape class
#include "d_textsh.h"	// textShape class

using namespace std;

// draw a mark on the ruler at position mid of height
// h * baseHeight
void drawMark(double mid, int h);

// draw a ruler with marks every 1/2**h units
void drawRuler(double low, double high, int h);

int main()
{
	// use to draw the ruler without the marks
	lineShape line(1.0, 4.0, 9.0, 4.0, black);
	// use for labeling each drawing
	string labelStr = "h =  ";
	textShape label(4.75,5,"",black);
	// will cycle through values 1 .. 7
	int h;

	// open the drawing window
	openWindow();

	// draw 7 rulers
	for (h=1;h <= 7;h++)
	{
		// draw the ruler without marks
		line.draw();
		// mark the ruler
		drawRuler(1.0, 9.0, h);

		// put the value of h as an ASCII character into
		// labelStr, assign the string into label and draw
		// the text
		labelStr[4] = char(h + '0');
		label.setText(labelStr);
		label.draw();

		// pause to view the current ruler
		viewWindow();
		// erase the window
		eraseWindow();
	}

	// done. close the window
	closeWindow();

	return 0;
}

void drawMark(double mid, int h)
{
	// use mark to draw the ruler marks. make it
	// static so we only create one object and use
	// it for all function calls
	static lineShape mark(0,0,0,0,black);
	// base length of a mark
	const double baseLength = 0.125;

	// set the end points of the mark and draw it
	mark.move(mid, 4.0 + h*baseLength);
	mark.setEndPoint(mid, 4.0 - h*baseLength);
	mark.draw();
}

void drawRuler(double low, double high, int h)
{
	double midpt;

	if (h >= 1)
	{	
		midpt = (high + low)/2;
		
		// draw the mark at midpt of [low, high)
		drawMark(midpt, h);

		// draw all marks on the left half-line, starting
		// with h-1
		drawRuler(low, midpt, h - 1);
		// draw all marks on the right half-line, starting
		// with h-1
		drawRuler(midpt, high, h - 1);
	}
}
