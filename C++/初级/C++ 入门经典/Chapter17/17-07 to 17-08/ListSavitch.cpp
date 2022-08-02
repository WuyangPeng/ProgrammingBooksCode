//DISPLAY 17.5 Program Using the GenericList Class Template
//Program to demonstrate use of the class template GenericList.
#include <iostream>
#include "genericlist.h"
#include "genericlist.cpp"
using namespace std;
using namespace listsavitch;

int main( )
{
    GenericList<int> firstList(2);
    firstList.add(1);
    firstList.add(2);
    cout << "firstList = \n"
         << firstList;

    GenericList<char> secondList(10);
    secondList.add('A');
    secondList.add('B');
    secondList.add('C');
    cout << "secondList = \n"
         << secondList;

	return 0;
}


