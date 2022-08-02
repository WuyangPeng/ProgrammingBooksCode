//auto local variable, uninitialized

#include <iostream>
using namespace std;

short mess()
{
  short xyz;
  xyz = 5;

  return xyz;
}
 
short counter()
{
  short count;

  count ++;
 
  cout << count << " ";

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
