#include <iostream>
using namespace std;

short Birthday(short age)
{
  age ++;
  return age;
}
 
int main()
{
  short x;
  short y;
 
  x = 46;
  y = Birthday(x);
 
  cout << "Your age was: " << x << endl;
  cout << "Happy Birthday: your age is now " << y << endl;

  return 0;
}
