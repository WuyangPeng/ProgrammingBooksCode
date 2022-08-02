/*********************************************************************

  Filename:  stl_iter.cpp
  Section:   17.2   STL  Iterators
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream>
#include <set>
using namespace std;

int main()
{
   int primes[4] ={2, 3, 5, 7}, *ptr = primes;
   set<int, greater<int> > s;
   set<int, greater<int> > ::
         const_iterator  const_s_it;

   while (  ptr != primes + 4 )
      s.insert(*ptr++);
   cout << "The primes below 10 : " << endl;
   for (const_s_it = s.begin();
        const_s_it != s.end(); ++const_s_it)
      cout << *const_s_it << '\t';
}
