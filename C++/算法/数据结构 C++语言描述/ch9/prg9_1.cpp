// File: prg9_1.cpp
// the program prompts the user for the size of an integer list and
// inserts required number of random integers in the range 0 to 99
// at the front of the list. after displaying the list using
// writeLinkedList(), a loop repeatedly calls the function getMax()
// that returns a pointer to the maximum value. after displaying
// the maximum value, the loop calls function eraseValue() to erase
// the maximum value from the list. output of the program is the
// original list of integers in descending order

#include <iostream>

#include "d_node.h"
#include "d_nodel.h"
#include "d_random.h"

using namespace std;

// return a pointer to the maximum element in the linked list
template <typename T>
node<T> *getMax(node<T> *front);

// if target is in the linked list, remove its first
// occurrence; otherwise, do not modify the list
template <typename T>
void eraseValue(node<T> * & front, const T& target);

int main()
{
	node<int> *front = NULL, *p;
	randomNumber rnd;
	int listCount, i;

	cout << "Enter the size of the list: ";
	cin >> listCount;

	for (i = 0; i < listCount; i++)
		front = new node<int> (rnd.random(100), front);

	cout << "Original List of Values:    ";
	writeLinkedList(front, "  ");
	cout << endl;

	cout << "Output in Descending Order: ";
	while (front != NULL)
	{
		p = getMax(front);
		cout << p->nodeValue << "  ";
		eraseValue(front, p->nodeValue);
	}

	cout << endl;
	return 0;
}

template <typename T>
node<T> *getMax(node<T> *front)
{
	node<T> *curr = front, *maxPtr = front;

	while (curr != NULL)
	{
		if (maxPtr->nodeValue < curr->nodeValue)
			maxPtr = curr;
		curr = curr->next;
	}
	return maxPtr;
}

template <typename T>
void eraseValue(node<T> * & front, const T& target)
{
	// curr moves through list, trailed by prev
   node<T>  *curr = front, *prev = NULL;
	// becomes true if we locate target
	bool foundItem = false;

   // scan until locate item or come to end of list
   while (curr != NULL && !foundItem)
   {
      if (curr->nodeValue == target)	// have a match
		{
         if (prev == NULL)					// remove the first node
            front = front->next;
         else
            prev->next = curr->next;	// erase intermediate node

			delete curr;

			foundItem = true;
		}
      else
      {
         // advance curr and prev
         prev = curr;
         curr = curr->next;
      }
   }
}

/*
Run:

Enter the size of the list: 9
Original List of Values:    62  44  55  40  39  81  30  91  95
Output in Descending Order: 95  91  81  62  55  44  40  39  30
*/
