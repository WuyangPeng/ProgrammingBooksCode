// Loop.cpp
// Assembly Language Program
// illustrates the use of a loop in assembly language
// to fill a table with sequentially higher numbers.
// contains no errors

#include <iostream.h>

void main(void)
{

	int etable[100];

	_asm {

	;code to generate a table of sequential even numbers
	mov		esi,00h		;initialize index register
	mov		ecx,100		;prepare to generate 100 numbers
more: mov	etable[esi],esi	;use index value as number, too
	add		esi,04h		;now point to next storage location
	loop	more		;repeat if cx is not zero
	
	}

	// print values in table
	for (int i=0; i<100 ; i++) {
		cout << hex << etable[i] << "\n";
	}
}