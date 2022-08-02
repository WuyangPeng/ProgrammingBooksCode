// File: prg9_4.cpp
// the program prompts the user to enter the number of contestants,
// n, in a world cruise contest and generates a random integer, m,
// between 1 and n. a call to the function josephus()
// outputs the winner of the contest. the function
// inserts the numbers 1, 2, 3, ..., n in a doubly
// linked list. a loop moves around the list circularly and
// erases every m th contestant until only 1 remains. this
// is the number of the winner

#include <iostream>

#include "d_dnode.h"
#include "d_nodel.h"
#include "d_random.h"

using namespace std;

// given an n item circular list, solve the Josephus problem
// by deleting every m th person until only one remains.
void josephus(int n, int m);

int main()
{
	// numContestants is number of contestants
	// removeM is the rotation selector
	randomNumber rnd;
	int n, m;

	cout << "Enter the number of contestants: ";
	cin >> n;

	// generate a random number between 1 and numContestants
	m = 1 + rnd.random(n);
	cout << "Generated the random number " << m << endl;

	// solve the Josephus problem and output the cruise winner
	josephus(n, m);

	return 0;
}

void josephus(int n, int m)
{
	// declare the circular doubly linked list dList and scan pointer
	dnode<int> *dList = new dnode<int>, *curr;
	int i, j;

	// initialize the list of contestants 1 2 3 ... n
	for (i = 1; i <= n; i++)
		insert(dList, i);

	// curr moves around the list, starting at person 1
	curr = dList->next;

	// delete all but one person from the list
	for(i=1; i < n; i++)
	{
		// counting current person at curr, visit m persons.
		// we must advance m-1 times.
		for(j=1; j <= m-1; j++)
		{
			// advance the pointer
			curr = curr->next;

			// if curr at the header, move again
			if (curr == dList)
				 curr = curr->next;
		}

		cout << "Delete contestant " << curr->nodeValue << endl;

		// advance curr and erase the node we just left
		curr = curr->next;
		erase(curr->prev);

		// might have deleted the rear of the list, so
		// curr is now at the header. move again
		if (curr == dList)
			curr = curr->next;
	}

	cout << endl << "Contestant " << curr->nodeValue
		  << " wins the cruise" << endl;

	// delete the one remaining node and the list header
	delete curr;
	delete dList;
}

/*
Run:

Enter the number of contestants: 10
Generated the random number 5
Delete contestant 5
Delete contestant 10
Delete contestant 6
Delete contestant 2
Delete contestant 9
Delete contestant 8
Delete contestant 1
Delete contestant 4
Delete contestant 7

Contestant 3 wins the cruise
*/
