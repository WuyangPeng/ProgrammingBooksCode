//
// DebuggingSubroutinesR.cpp
// Now using call-by-reference.
// Chris H. Pappas and William H. Murray, 2000
//

#include <iostream>

using namespace std;

//Notice clean alignment of formal
//argument types...

int aSimpleSubroutine( char  &cValue, 
					   int   &iValue,
					   float &fValue );

void main ( void )
{
  char  cValue = 'A';	
  int   iValue = 125;
  float fValue = 1.2345;
  
  aSimpleSubroutine ( cValue,
	                  iValue,
					  fValue  );
}

int aSimpleSubroutine( char  &cValue, 
					   int   &iValue,
					   float &fValue )
{
  //subroutine body
  return iValue;
}
