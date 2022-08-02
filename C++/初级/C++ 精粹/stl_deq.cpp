/*********************************************************************

  Filename:  stl_deq.cpp
  Section:   17.1   STL Containers
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <deque>
#include <vector>

using namespace std;

const int SIZE = 100;

double sum(const deque<double> &dq)
{
   deque<double>::const_iterator p;
   double s = 0;

   for (p=dq.begin(); p != dq.end(); ++p)
      s += *p ;
   return s;
}

int main()
{
	vector<double> vec(SIZE, 0);   //changed form int to double
	deque<double> deq;             //ditto and later iterator
	int i;
	double sumTotal;
                                 // init and output vec
	for(i = 0; i < SIZE; i++){
	   vec[i] = i * 0.6; cout << vec[i] <<"\t";
	}

   deq.push_front(vec.front()); // add an element to the front
   deq.push_back(vec.back());   // add an element to the back

   // Insert the remaining elements from the vector between
   // the first and last deque elements
   //
   deq.insert(deq.begin()+1, vec.begin()+1, vec.end()-1);

   sumTotal = sum(deq);
   cout << "The sum of the deque is : " << sumTotal << endl;
}
