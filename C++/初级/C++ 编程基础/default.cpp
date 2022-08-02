#include <iostream>
#include "default.h"
using namespace std;

void Answer(int x)
{
cout << "Here is the answer: " << x << endl;
}

main()
{
  Answer(10);
  Answer();
}