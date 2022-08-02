#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
   Removes an element from an unordered vector.
   @param v a vector
   @param pos the position of the element to erase
*/
void erase(vector<string>& v, int pos)
{  
   int last_pos = v.size() - 1;
   v[pos] = v[last_pos];
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
   staff[0] = "Hacker, Harry";
   staff[1] = "Reindeer, Rudolf";
   staff[2] = "Cracker, Carl";
   staff[3] = "Lam, Larry";
   staff[4] = "Sandman, Susan";
   print(staff);

   int pos;
   cout << "Remove which element? ";
   cin >> pos;

   erase(staff, pos);
   print(staff);
   return 0;
}
