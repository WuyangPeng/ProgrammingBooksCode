// File: prg13_2.cpp
// draw a 4 x 4 blue square centered at (5,4) in the drawing window.
// draw with a light gray circle with radius .125 centered at (5,4).
// after .1 seconds, draw the circle with the same center having a
// radius of .125 + .125. after pausing .1 seconds, continue this
// process with a circle whose radius increase by .125 until it
// reaches a radius of 2. at this point, the circle is inscribed in
// the square. draw the diagonals of the square and output the message
// "That's All Folks" below the square

#include "d_draw.h"		// graphics library
#include "d_rectsh.h"	// rectShape class
#include "d_circsh.h"	// circleShape class
#include "d_linesh.h"	// lineShape class
#include "d_textsh.h"	// textShape class

int main()
{
	// the light blue 4 x 4 square
	rectShape square(3.0,2.0,4.0,4.0,blue);

	// circle that grows to size of the square
	circleShape circ(5.0,4.0,0,lightgray);

	// diagonal lines in the square
	lineShape diag1(3.0,2.0,7.0,6.0,black), 
		       diag2(3.0,6.0,7.0,2.0,black);

	// display message after the circle hits the bulls-eye
	textShape text(4.1,6.4,"That's All Folks", black);

	// initial radius of the circle
	double r = 0.125;

	// open the drawing window and draw the square
	openWindow();
	square.draw();

	do
	{
		// set the radius and draw the circle
		circ.setRadius(r);
		circ.draw();

		// increase radius by 0.125
		r += 0.125;

		// pause 1/10 second and then proceed
		delayWindow(.1);
	} while (r <= 2.0);

	// draw the diagonals for the square
	diag1.draw();
	diag2.draw();

	// draw the label "That's All Folks"
	text.draw();

	// pause to view the final figure
	viewWindow();

	// shutdown the drawing system
	closeWindow();

	return 0;
}
