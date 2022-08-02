#include <fstream>
#include <string>
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

  ofstream prout("lpt1");
 
  prout << "Your age was: " << x << endl;
  prout << "Happy Birthday: your age is now " << y << endl;
  prout << '\f' << endl;

  prout.close();

  return 0;
}

