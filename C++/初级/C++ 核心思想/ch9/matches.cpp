#include <iostream> 
#include <vector> 

using namespace std; 

/** 
   Returns the positions of all values within a range. 
   @param v a vector of floating-point numbers 
   @param low the low end of the range 
   @param high the high end of the range 
   @return a vector of positions of values in the given range 
*/ 
vector<int> find_all_between(vector<double> v, 
   double low, double high) 
{ 
   vector<int> pos;
   for (int i = 0; i < v.size(); i++) 
   { 
      if (low <= v[i] && v[i] <= high) 
         pos.push_back(i); 
   } 
   return pos; 
} 

int main() 
{ 
   vector<double> salaries(5); 
   salaries[0] = 35000.0; 
   salaries[1] = 63000.0; 
   salaries[2] = 48000.0; 
   salaries[3] = 78000.0; 
   salaries[4] = 51500.0; 
   
   vector<int> matches 
      = find_all_between(salaries, 45000.0, 65000.0); 
   
   for (int j = 0; j < matches.size(); j++) 
      cout << salaries[matches[j]] << "\n"; 
   return 0; 
} 
