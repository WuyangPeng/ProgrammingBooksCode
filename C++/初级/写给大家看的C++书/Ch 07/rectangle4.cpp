// rectangle4.cpp - Script 7.4

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Class declaration.
class Rectangle {

public:
	// Declare the attributes.
	unsigned width, height;
	
	// Constructor:
	Rectangle(unsigned x = 0, unsigned y = 0);
	
	// Declare the methods.
	void setSize(unsigned x, unsigned y);
	unsigned area();
	unsigned perimeter();
	bool isSquare();

}; // Don't forget the semicolon!


// Define the constructor.
Rectangle::Rectangle(unsigned x, unsigned y) {
	width = x;
	height = y;
}

// Define the methods for the Rectangle class.

/* The method setSize() assigns the
 * rectangle's dimensions to the attributes.
 * It takes two arguments, both floats.
 * It returns nothing. 
 */
void Rectangle::setSize(unsigned x, unsigned y) {
	width = x;
	height = y;
}

/* The method area() returns the
 * rectangle's area.
 * It takes two arguments, both floats.
 * It returns a float. 
 */
unsigned Rectangle::area() {
	return (width * height);
}

/* The method perimeter() returns the
 * rectangle's perimeter.
 * It takes two arguments, both floats.
 * It returns a float. 
 */
unsigned Rectangle::perimeter() {
	return (width + width + height + height);
}

/* The method isSquare() returns a
 * Boolean value indicating whether
 * or not the rectangle is also a square.
 * It takes two arguments, both floats.
 * It returns a Boolean. 
 */
bool Rectangle::isSquare() {

	if (width == height) {
		return true; // Square
	} else {
		return false; // Not square
	}
	
}


// Start the main function.
int main() {

	// Create the necessary variables.
	unsigned width = 25;
	unsigned height = 14;

	// Print a little introduction.
	std::cout << "With a width of " << width
	<< " and a height of " << height << "...\n\n";
	
	// Create a new object and assign the values.
	Rectangle myRectangle(width, height);
	/* Alternative to:
	 * Rectangle myRectangle;
	 * myRectangle.setSize(width, height);
	 */
	
	// Print the area.
	std::cout << "The area of the rectangle is " 
	<< myRectangle.area() << ".\n";
		
	// Print the perimeter.
	std::cout << "The perimeter of the rectangle is " 
	<< myRectangle.perimeter() << ".\n";
	
	// Is this a square?
	std::cout << "This rectangle ";
	if (myRectangle.isSquare()) {
		std::cout << "is also";
	} else {
		std::cout << "is not";
	}
	std::cout << " a square.\n\n";

	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
		
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
