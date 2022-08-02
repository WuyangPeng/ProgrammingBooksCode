//
// RunTimeValueChanges.cpp
// Different ways to reset variable contents
// at run-time.
// Chris H. Pappas and William H. Murray, 2000
//

#include <iostream>

using namespace std;

void main ( void )
{
  char   cResponse = 'Y';	
  
  if ( cResponse == 'Y' )
    cout << "True action taken...\n";
  else
	cout << "False action taken...\n";
}
