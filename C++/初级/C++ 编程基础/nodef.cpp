#include <iostream>
#include "nodef.h"
using namespace std;

void Answer(int x)
{
cout << "Here is the answer: " << x << endl;
}

void Answer()
{
cout << "Here is the answer: " << 42 << endl;
}

main()
{
  Answer(10);
  Answer();
}