// BigInt.cpp
// Assembly Language Program
// illustrates the power of assembly language in
// correctly manipulating 256-bit numbers
// with multiple precision arithmetic.
// contains no errors


void main(void)
{

//break up and store the first 256-bit integer number
//1234567891234567ABCDABCDABCDABCDFFFFEEEEDDDDCCCCDDDDCCCCBBBBAAAA
	unsigned __int64 numA1 = 0xDDDDCCCCBBBBAAAA;
	unsigned __int64 numA2 = 0xFFFFEEEEDDDDCCCC;
	unsigned __int64 numA3 = 0xABCDABCDABCDABCD;
	unsigned __int64 numA4 = 0x1234567891234567;

//break up and store the second 256-bit integer number
//22222222222222221111111111111111A1B2C3D4E5F6E5D48888999911112222
	unsigned __int64 numB1 = 0x8888999911112222;
	unsigned __int64 numB2 = 0xA1B2C3D4E5F6E5D4;
	unsigned __int64 numB3 = 0x1111111111111111;
	unsigned __int64 numB4 = 0x2222222222222222;

//prepare storage locations to hold the 256-bit result
	unsigned __int64 ANS1 = 0;
	unsigned __int64 ANS2 = 0;
	unsigned __int64 ANS3 = 0;
	unsigned __int64 ANS4 = 0;

	_asm {

	;start with numA1 and numB1
	mov	eax,dword ptr numA1		;get first 8 digits 
	add eax,dword ptr numB1		;add first 8 digits 
	mov dword ptr ANS1,eax		;save first 8 digits
   	mov	eax,dword ptr numA1 + 4	;get next 8 digits 
	adc eax,dword ptr numB1 + 4	;add next 8 digits + carry
	mov dword ptr ANS1 + 4,eax	;save next 8 digits

	;work with numA2 and numB2 + carry information
	mov	eax,dword ptr numA2		;get next 8 digits 
	adc eax,dword ptr numB2		;add next 8 digits + carry
	mov dword ptr ANS2,eax		;save next 8 digits
   	mov	eax,dword ptr numA2 + 4	;get next 8 digits 
	adc eax,dword ptr numB2 + 4	;add next 8 digits + carry
	mov dword ptr ANS2 + 4,eax	;save next 8 digits

	;work with numA3 and numB3 + carry information
	mov	eax,dword ptr numA3		;get next 8 digits 
	adc eax,dword ptr numB3		;add next 8 digits + carry
	mov dword ptr ANS3,eax		;save next 8 digits
   	mov	eax,dword ptr numA3 + 4	;get next 8 digits 
	adc eax,dword ptr numB3 + 4	;add next 8 digits + carry
	mov dword ptr ANS3 + 4,eax	;save next 8 digits

	;work with numA4 and numB4 + carry information
	mov	eax,dword ptr numA4		;get next 8 digits 
	adc eax,dword ptr numB4		;add next 8 digits + carry 
	mov dword ptr ANS4,eax		;save next 8 digits
   	mov	eax,dword ptr numA4 + 4	;get next 8 digits 
	adc eax,dword ptr numB4 + 4	;add next 8 digits + carry
	mov dword ptr ANS4 + 4,eax	;save next 8 digits
	
	}
}