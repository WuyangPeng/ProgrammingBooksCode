//static local variable, not explicitly initialized

#include <iostream>
using namespace std;

short mess()
{
  short xyz[1];
  xyz[0] = 5;

  return xyz[0];
}
 
short counter()
{
  static short count[1];

  count[0] ++;
 
  cout << count[0] << " ";

  return 0;
}

int main()
{
  short i;
 
  for (i = 0; i < 10; i ++)
    {
    mess();
    counter();
    }

  cout << endl;

  return 0;
}
