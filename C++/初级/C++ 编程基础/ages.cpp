#include <iostream>
using namespace std;

int main()
{
  short FirstAge;
  short SecondAge;
  short Result;

  cout << "Please enter the first age: ";
  cin >> FirstAge;
 
  cout << "Please enter the second age: ";
  cin >> SecondAge;

  if (FirstAge > SecondAge)
     Result = FirstAge - SecondAge;
  else
     Result = SecondAge - FirstAge;

  cout << "The difference in ages is: " << Result;   
  return 0;
}
