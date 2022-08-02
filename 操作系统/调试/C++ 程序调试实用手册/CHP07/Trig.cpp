// Trig.cpp
// Assembly Language Program
// illustrates the use of the coprocessor in
// calculating a table of trigonometric
// values (tangent) with the coprocessor
// for angles between 0 and 45 degrees.
// contains no errors

#include <iostream.h>

void main(void)
{

	int angle = 0;
	int radian = 180;
	double ttable[46];

	_asm {

	mov	esi,0			;initialize index register
	mov	cx,46			;prepare to create 46 values
	finit				;initialize coprocessor
more: fldpi				;place pi on stack
	fild	radian		;load radian constant
	fdiv				;divide pi by radian
	fild	angle		;load angle onto stack
	fmul				;convert degrees to radians
	fptan				;calculate tangent
	fdiv				;divide st(1)/st(0) to get value
	fstp	ttable[esi]	;save answer in tangent table
	inc		angle		;next angle
	add		esi,08d		;point to next storage location
	loop	more		;end if cx=0
	fwait				;sync co and micro processors
	
	}

	cout << "Angle   Tangent\n\n";
	for(int i = 0; i<46 ; i++) {
		cout << i <<  "\t" << ttable[i] << "\n";
    }
}