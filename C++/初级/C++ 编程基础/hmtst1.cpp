// hmtst1.cc

#include <iostream>
#include <fstream>
#include <string>
#include "Vec.h"
#include "hmit1.h"
using namespace std;

int main()
{
  HomeItem x;
  HomeItem y;

  ifstream HomeInfo("home1.in");

  HomeInfo >> x;

  HomeInfo >> y;

  cout << "A basic HomeItem: " << endl;
  cout << x;

  cout << endl;

  cout << "A music HomeItem: " << endl;
  cout << y;

  return 0;
}
