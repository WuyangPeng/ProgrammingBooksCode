// Rational.cpp - Script 12.3

// Created by Andi Signer
// and Larry Ullman.

// This file implements the
// Rational class.
// The class is used to
// represent fractions.

// Need the header file.
#include "Rational.h"

// Need the iostream file
// as we refer to ostream.
#include <iostream>

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

// Define operator<<()
std::ostream& operator<<(std::ostream& os, Rational f) {

	// Write the numerator and denominator 
	// to the given stream.
	os << f.numerator << "/" << f.denominator;
	
	// Return the stream to enable chaining.
	return os;
	
}
