//
// voidptr.cpp
// Program illustrating void pointers
// Chris H. Pappas and William H. Murray, 2000
//

#include <iostream>
using namespace std;

void printit ( void *pData, char cRunTimeChoice );

void main ( void )
{
  char  *pchar, cRunTimeChoice;
  int   *pivalue;
  float *pfvalue;

  cout << "Please enter the dynamic data type you want to create\n"
       << " press c for char, i for int, or f for float: ";

  cin  >> cRunTimeChoice;

  switch ( cRunTimeChoice ) {

    case 'c': pchar = new char; 
              cout << "\nEnter a character: ";
              cin  >> *pchar;
              printit ( pchar, cRunTimeChoice );
              break;
      
    case 'i': pivalue = new int;
              cout << "\nEnter an integer: "; 
              cin  >> *pivalue;
              printit ( pivalue, cRunTimeChoice );
              break;

    default:  pfvalue = new float;
              cout << "\nEnter a float: ";
              cin  >> *pfvalue;
              printit ( pfvalue, cRunTimeChoice );

    }
}

void printit ( void *pData, char cRunTimeChoice )
{
  cout << "\nThe Dynamic Data type entered was ";

  switch ( cRunTimeChoice ) {
    
    case 'c': cout << "char and a value of: "
                   << *(char *)pData;
                   break;

    case 'i': cout << "int and a value of: "
                   << *(int *)pData;
                   break;
    default:  cout << "float and a value of: "
                   << *(float *)pData;

  }
  delete pData;
}
