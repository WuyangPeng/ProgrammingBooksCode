// rational2.cpp - Script 9.6

#include <iostream>

#include <string>

// Declare the class.
class Rational {

public:

	// Constructor:
	Rational(int num, int denom);
	
	// The overloaded methods that implement
	// arithmetic functions:
	Rational operator+(Rational rhs);
	Rational operator-(Rational rhs);
	Rational operator*(Rational rhs);
	Rational operator/(Rational rhs);

private:
	// normalize() will take care of transforming
	// numerator and denominator into a well-defined
	// format.
	void normalize();
	
	int numerator;
	int denominator;

	// The operator<< function will 
	// access the numerator and denominator
	// so we're making it a friend.
	friend std::ostream& operator<<(std::ostream& os, Rational f);
	
};


// Define the constructor.
Rational::Rational(int num, int denom) {
	numerator = num;
	denominator = denom;
	normalize();
}

// Overload the operators.
Rational Rational::operator+(Rational rhs) {

	//  a   c   a*d   c*b   a*d + c*b
	//  - + - = --- + --- = ---------
	//  b   d   b*d   b*d      b*d
	
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;
	
	int e = a*d + c*b;
	int f = b*d;

	return Rational(e,f);
}

Rational Rational::operator-(Rational rhs) {

	//  a   c   a   -c
	//  - - - = - + -- 
	//  b   d   b   d 

	rhs.numerator = -rhs.numerator;
	
	return operator+(rhs);
}
	
Rational Rational::operator*(Rational rhs) {

	//  a   c   a*c
	//  - * - = ---
	//  b   d   b*d
	
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;
	
	int e = a*c;
	int f = b*d;
	
	return Rational(e,f);
}

Rational Rational::operator/(Rational rhs) {

	//  a   c   a   d 
	//  - / - = - * - 
	//  b   d   b   c 
	
	int t = rhs.numerator;
	rhs.numerator = rhs.denominator;
	rhs.denominator = t;

	return operator*(rhs);
}
	
	
// Define the methods.
void Rational::normalize() {

	// Check the signs.
	if (denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}

	// Calculate the greatest common denominator of a/b
	// using Euclid's algorithm.
	int a = abs(numerator);
	int b = abs(denominator);
	while (b > 0) {
		int t = a % b;
		a = b;
		b = t;
	}

	numerator /= a;
	denominator /= a;
}

// This is the prototype for operator<<()
std::ostream& operator<<(std::ostream& os, Rational f);


int main() {

	// Create two Rationals: 2/16 and 7/8.
	Rational f1(2,16);
	Rational f2(7,8);

	// Test addition.
	std::cout << f1 << " + " << f2 << " == " << (f1+f2) << "\n";

	// Test subtraction.
	std::cout << f1 << " - " << f2 << " == " << (f1-f2) << "\n";

	// Test multiplication.
	std::cout << f1 << " * " << f2 << " == " << (f1*f2) << "\n";

	// Test division.
	std::cout << f1 << " / " << f2 << " == " << (f1/f2) << "\n";
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
	
} // End of main().

// Define operator<<()
std::ostream& operator<<(std::ostream& os, Rational f) {

	// Write the numerator and denominator 
	// to the given stream.
	os << f.numerator << "/" << f.denominator;
	
	// Return the stream to enable chaining.
	return os;
	
}
