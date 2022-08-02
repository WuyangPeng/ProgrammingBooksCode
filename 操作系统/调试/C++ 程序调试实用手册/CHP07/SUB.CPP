// Sub.cpp
// Assembly Language Program
// illustrates debugger use
// contains no errors

#include <iostream.h>

void main(void)
{

	unsigned int num_1=0xABCD8765;
	unsigned int num_2=0x12345678;
	unsigned int result;

	_asm {

	;code to perform actual subtraction
	mov		eax,num_1	;move num_1 into eax register
	sub		eax,num_2	;subtract num_2 from eax
	mov		result,eax	;store eax in result

	}

	cout << hex << result << "\n";
}
