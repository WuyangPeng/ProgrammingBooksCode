#include <iostream>
using namespace std;

short count1; // A global variable, not explicitly initialized
short count2 = 5; // A global variable, explicitly initialized

short func1()
{
  short count3; // A local auto variable, not explicitly initialized 
  short count4 = 22; // A local auto variable, explicitly initialized
static short count5; // A local static variable, not explicitly initialized
static short count6 = 9; // A local static variable, explicitly initialized

  count1 ++; // Incrementing the global variable count1.
  count2 ++; // Incrementing the global variable count2.
  count3 ++; // Incrementing the local uninitialized auto variable count3. 
  count4 ++; // Incrementing the local auto variable count4.
  count5 ++; // Incrementing the local static variable count5.
  count6 ++; // Incrementing the local static variable count6.

  cout << "count1 = " << count1 << endl; 
  cout << "count2 = " << count2 << endl; 
  cout << "count3 = " << count3 << endl; 
  cout << "count4 = " << count4 << endl; 
  cout << "count5 = " << count5 << endl; 
  cout << "count6 = " << count6 << endl; 
  cout << endl;

  return 0;
}

int main()
{
  func1();
  func1();

  return 0;
}
