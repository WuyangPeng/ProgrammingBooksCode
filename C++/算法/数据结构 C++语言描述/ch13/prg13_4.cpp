// File: prg13_4.cpp
// the function collage() forms a grid of identical
// shapes of the type pointed to by its argument.
// each row of the grid contains 4 figures. each
// of the 15 figures in the grid is draw in a
// different color from the palette. the program
// creates a circle, regular hexagon, and an
// equilateral triangle and calls collage()
// for each figure

#include "d_draw.h"		// for openWindow(), etc.
#include "d_circsh.h"	// use circleShape class
#include "d_polysh.h"	// use polyShape class

void collage(shape *sPtr);

int main()
{
   // pointers in the shape (base) class
	shape *fPtr[3];

	// create a blue circle with radius .75
	fPtr[0] = new circleShape(0, 0, 0.75, blue);
	// create a blue regular hexagon with sides of
	// length .75
   fPtr[1] = new polyShape(0, 0, 6, 0.75, blue);
	// create an equilateral triangle with sides of
	// length 1.5
   fPtr[2] = new polyShape(0, 0, 3, 1.5, blue);

   // open the drawing window
	openWindow();
   
	// create the collage of figures
	for (int i = 0; i < 3; i++)
		collage(fPtr[i]);

	// close the drawing window
	closeWindow();

	return 0;
}

void collage(shape *sPtr)
{
	// the initial color of the shape is blue
	shapeColor c = blue;
	int i;

	// draw 15 shapes, each in a different color
	// arranged in a grid of 4 figures across.
	// the figure base points for the 1st row
	// are (1,1), (3,1), (5,1), (7,1) and
	// for the second row are
	// (1,3), (3,3), (5,3), (7,3), etc.
	for (i = 0; i < 15; i++)
	{
		sPtr->move(2*(i%4) + 1.0, 2*(i/4) + 1.0);
		sPtr->draw();
		c++;
		sPtr->setColor(c);
	}

	viewWindow();
	eraseWindow();
}
