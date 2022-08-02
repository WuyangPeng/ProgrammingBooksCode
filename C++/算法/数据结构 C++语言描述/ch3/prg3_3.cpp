// File: prg3_3.cpp
// prompt for the number of disks and call the function
// hanoi() to solve the Tower of Hanoi puzzle

#include <iostream>
#include <string>

using namespace std;

// move n disks from initNeedle to endNeedle, using tempNeedle
// for intermediate storage of the disks. 
void hanoi(int n, const string& initNeedle,
			  const string& endNeedle, const string& tempNeedle);

int main()
{
   // number of disks and the needle names
   int n;
   string beginneedle  = "A",
          middleneedle = "B",
          endneedle    = "C";

   // prompt for n and solve the puzzle for n disks
   cout << "Enter the number of disks: ";
   cin >> n;
   cout << "The solution for n = " << n << endl;
   hanoi(n, beginneedle, endneedle, middleneedle);

	return 0;
}

void hanoi(int n, const string& initNeedle,
			  const string& endNeedle, const string& tempNeedle)
{
   // stopping condition: move one disk
   if (n == 1)
      cout 	<< "move " << initNeedle << " to "
           	<< endNeedle << endl;
   else
   {
      // move takes n-1 disks from initNeedle to
		// tempNeedle using endNeedle for temporary storage
      hanoi(n-1,initNeedle,tempNeedle,endNeedle);

      // move largest disk to endNeedle
      cout 	<< "move " << initNeedle << " to "
           	<< endNeedle << endl;

      // move takes n-1 disks from tempNeedle to
		// endNeedle using initNeedle for temporary storage
      hanoi(n-1,tempNeedle,endNeedle,initNeedle);
   }
}

/*
Run:

Enter the number of disks: 3
The solution for n = 3
move A to C
move A to B
move C to B
move A to C
move B to A
move B to C
move A to C
*/
