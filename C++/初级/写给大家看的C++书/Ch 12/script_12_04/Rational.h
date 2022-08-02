// Rational.h - Script 12.4

// Created by Andi Signer
// and Larry Ullman.

// This file declares the
// Rational class.
// The class is used to
// represent fractions.

// Check for previous inclusion
// of this file.
#ifndef RATIONAL_H

// If not already defined,
// then define RATIONAL_H now.
#define RATIONAL_H

// Need the iostream file
// as we refer to ostream.
#include <iostream>

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

	// Normalize() will take care of 
	// transforming numerator and denominator 
	// into a well defined format.
	void normalize();
	
	// Attributes:
	int numerator;
	int denominator;

	// The operator<< function will 
	// access the numerator and denominator
	// so we're making it a friend.
	friend std::ostream& operator<<(std::ostream& os, Rational f);
	
};

#endif // End of #ifndef RATIONAL_H
