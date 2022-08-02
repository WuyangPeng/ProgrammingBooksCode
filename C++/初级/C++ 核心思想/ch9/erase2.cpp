#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
   Removes an element from an ordered vector.
   @param v a vector
   @param pos the position of the element to erase
*/
void erase(vector<string>& v, int pos)
{ 
   for (int i = pos; i < v.size() - 1; i++)
      v[i] = v[i + 1];
   v.pop_back();
}

/** 
   Prints all elements in a vector.
   @param v the vector to print
*/
void print(vector<string> v)
{  
   for (int i = 0; i < v.size(); i++)
      cout << "[" << i << "] " << v[i] << "\n";
}

int main()
{  
   vector<string> staff(5);
   staff[0] = "Cracker, Carl";
   staff[1] = "Hacker, Harry";
   staff[2] = "Lam, Larry";
   staff[3] = "Reindeer, Rudolf";
   staff[4] = "Sandman, Susan";
   print(staff);

   int pos;
   cout << "Remove which element? ";
   cin >> pos;

   erase(staff, pos);
   print(staff);
   return 0;
}
