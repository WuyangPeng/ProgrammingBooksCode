//
// RecursiveCallStack.cpp
// Program demonstrates recursive calls
// Chris H. Pappas and William H. Murray, 2000
//

int Factorial( int iCurrentValue );

void main ( void )
{
  int iRecursiveCalculation;

  iRecursiveCalculation = Factorial( 4 );
}

int Factorial( int iCurrentValue )
{
  if( iCurrentValue == 1 )
    return iCurrentValue;
  else
    return iCurrentValue *= 
           Factorial( iCurrentValue - 1 );
}