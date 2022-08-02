// RealAdd.cpp
// Assembly Language Program
// illustrates the use of the coprocessor in
// assembly language to perform real number
// arithmetic.
// contains no errors

#include <iostream.h>

void main(void)
{

	double numa = 128.76;
	double numb = -3.5e+1;
	double answer;

	_asm {

	finit			;initialize coprocessor
	fld		numa	;place first real onto stack
	fadd	numb	;add second real to stack
	fstp	answer	;pop and save real answer
	fadd	st(0),st(7)
	fwait			;sync co and micro procesors
	
	}
	cout << answer << "\n";
}