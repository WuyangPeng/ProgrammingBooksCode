#ifndef KNAPSACK_PROBLEM
#define KNAPSACK_PROBLEM

#include <iostream>
#include <iomanip>
#include <vector>

#include "d_matrix.h"

using namespace std;

// specifies the size and value of an item
class item
{
	public:
		int size, value;
		item(int s = 0, int v = 0) : size(s), value(v)
		{}
};

class knapsack
{
	public:
		knapsack(vector<item>& v, int cap);
			// constructor. assigns v as the item list and calls
			// buildMaxValueMat() to implement the knapsack algorithm 

		void displayKnapsack();
			// displays the capacity, the maximum value, the unused
			// space, and a list of the items with their size and value

		void displayMaxValueMat();
			// output the row/column values in the matrix
	private:
		int capacity;
		int numItems;
		vector<item> itemList;
		matrix<int> maxValueMat;

		void buildMaxValueMat();
			// implements the knapsack algorithm
};

void knapsack::buildMaxValueMat()
{
	int i, cap, testMax;

	// compute entries in the matrix
	for (i = 1; i <= numItems; i++)
		for (cap = 1; cap <= capacity; cap++)
		{
			// keep the same max value by default
			maxValueMat[i][cap] = maxValueMat[i-1][cap];

			// test if itemList[i] fits into the knapsack
			if (cap-itemList[i].size >= 0)
			{
				// test if maximum value increases
				testMax = maxValueMat[i-1][cap-itemList[i].size] + 
								itemList[i].value;
				// if yes, assign new max 
				if (testMax > maxValueMat[i-1][cap])
					maxValueMat[i][cap] = testMax;
			}
		}
}

knapsack::knapsack(vector<item>& v, int cap): 
			 capacity(cap), numItems(v.size())
{
	int i;

	// initialize dimensions for itemList and maxValueMat
	itemList.resize(numItems+1);
	maxValueMat.resize(numItems+1, capacity+1);

	// initialize itemList from v so that item1 = v[0]
	// is in itemList[1], item2 = v[1] is in itemList[2],
	// and so forth
	for (i = 1; i <= numItems; i++)
		itemList[i] = v[i-1];

	// build the matrix
	buildMaxValueMat();
}

void knapsack::displayKnapsack()
{
	int i = numItems, cap = capacity;
	cout << endl << "Capacity: " << capacity << "  Value: "
		  << maxValueMat[numItems][capacity] << endl << endl;
	cout << "Contents: " << endl << endl;

	// scan list of items in reverse order
	while (i > 0)
	{
		// if values in successive rows are not equal,
		// itemList[i] is part of the solution
		if (maxValueMat[i][cap] != maxValueMat[i-1][cap])
		{
			cout << "   item" << i << '(' << itemList[i].size
				  << ',' << itemList[i].value << ')' << endl;
			// look for maximum value remaining space
			cap -= itemList[i].size;
		}
		i--;
	}
	cout << "   Unused capacity: " << cap << endl;
}

void knapsack::displayMaxValueMat()
{
	int i, cap;

	cout << "Maximum value matrix for capacity " << capacity << endl;
	cout << "   ";
	for(i = 1; i <= capacity; i++)
		cout << setw(4) << i;
	cout << endl << endl;

	for (i = 1; i <= numItems; i++)
	{
		cout << i << "  ";
		for (cap = 1; cap <= capacity; cap++)
			cout << setw(4) << maxValueMat[i][cap];
		cout << endl;
	}
	cout << endl;
}

#endif	// KNAPSACK_PROBLEM
