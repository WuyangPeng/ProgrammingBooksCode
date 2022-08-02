#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
   Inserts an element into a vector.
   @param v a vector
   @param pos the position before which to insert the element
   @param s the element to insert
*/
void insert(vector<string>& v, int pos, string s)
{  
   int last = v.size() - 1; 
   v.push_back(v[last]);
   for (int i = last; i > pos; i--)
      v[i] = v[i - 1];
   v[pos] = s;
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
   cout << "Insert before which element? ";
   cin >> pos;

   insert(staff, pos, "New, Nina");
   print(staff);
   return 0;
}
