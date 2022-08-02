#include <iostream>
#include <vector>

using namespace std;

/**
   Raise all values in a vector by a given percentage.
   @param v vector of values
   @param p percentage to raise values by
*/
void raise_by_percent(vector<double>& v, double p)
{  
   for (int i = 0; i < v.size(); i++)
      v[i] = v[i] * (1 + p / 100);
}

int main()
{  
   vector<double> salaries(5);
   salaries[0] = 35000.0;
   salaries[1] = 63000.0;
   salaries[2] = 48000.0;
   salaries[3] = 78000.0;
   salaries[4] = 51500.0;

   raise_by_percent(salaries, 4.5);

   for (int i = 0; i < salaries.size(); i++)
      cout << salaries[i] << "\n";

   return 0;
}
