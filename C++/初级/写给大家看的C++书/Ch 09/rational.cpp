// rational.cpp - Script 9.5

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

	void print();
        
private:
	// normalize() will take care of transforming
	// numerator and denominator into a well-defined
	// format.
	void normalize();
	
	int numerator;
	int denominator;
};

// Define the constructor.
Rational::Rational(int num, int denom) {

	// Assign the values.
	numerator = num;
	denominator = denom;
	
	// Call normalize() in case the user
	// passed "garbage" to the object.
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
	
	// Calculate the new numerator and denominator.
	int e = a*d + c*b;
	int f = b*d;

	// Return the resulting Rational
	return Rational(e,f);
}

Rational Rational::operator-(Rational rhs) {

	//  a   c   a   -c
	//  - - - = - + -- 
	//  b   d   b   d 

	// Change the sign of the right-hand side.
	rhs.numerator = -rhs.numerator;
	
	// Now just add the two, using the operator+ method call.
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
	
	// Calculate the new numerator and denominator.
	int e = a*c;
	int f = b*d;
	
	// Return the resulting Rational.
	return Rational(e,f);
}

Rational Rational::operator/(Rational rhs) {

	//  a   c   a   d 
	//  - / - = - * - 
	//  b   d   b   c 
	
	// Invert the right-hand side
	int t = rhs.numerator;
	rhs.numerator = rhs.denominator;
	rhs.denominator = t;

	// Now just multiply the Rationals.
	return operator*(rhs);
}
	
// Define the methods.
void Rational::print() {
    std::cout << numerator << "/" << denominator;
}

void Rational::normalize() {

	// Check the signs.
	if (denominator < 0) {
		// "Move" the sign to the nominator.
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

	// Divide both numbers by a.
	numerator /= a;
	denominator /= a;
}


int main() {

	// Create two Rationals: 2/16 and 7/8.
	Rational f1(2,16);
	Rational f2(7,8);

	// Test addition.
	Rational res = f1 + f2;
	f1.print(); 
	std::cout << " + "; 
	f2.print();
	std::cout << " == "; 
	res.print();
	std::cout << "\n";
    
	// Test subtraction.
	res = f1 - f2;
	f1.print(); 
	std::cout << " - "; 
	f2.print();
	std::cout << " == "; 
	res.print();
	std::cout << "\n"; 
    
	// Test multiplication.
	res = f1 * f2;
	f1.print(); 
	std::cout << " * "; 
	f2.print();
	std::cout << " == "; 
	res.print();
	std::cout << "\n"; 
    
	// Test division.
	res = f1 / f2;
	f1.print(); 
	std::cout << " / "; 
	f2.print();
	std::cout << " == "; 
	res.print();
	std::cout << "\n"; 
    
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
