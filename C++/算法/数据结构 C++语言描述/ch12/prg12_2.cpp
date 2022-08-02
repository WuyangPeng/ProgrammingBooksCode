// File: prg12_2.cpp
// the program declares a hash table with integer data and
// the identity hash function object. it inserts the elements
// from the array intArr into the hash table, noting which
// values are duplicates that do not go into the table. after
// displaying the size of the hash table, a loop prompts the user
// for 2 values. if a value is in the table, the erase() operation
// deletes it. the program terminates by using an iterator to
// traverse and output the elements of the hash table

#include <iostream>

#include "d_hash.h"
#include "d_hashf.h"

using namespace std;
 
int main()
{
	// array that holds 10 integers with some duplicates
	int intArr[] = {20, 16, 9, 14, 8, 17, 3, 9, 16, 12};
	int arrSize = sizeof(intArr)/sizeof(int);
	
	// alias describing integer hash table using identity function
	// object
	typedef hash<int, hFintID> hashTable;

	// hash table with 7 buckets and hash iterator
	hashTable ht(7);
	hashTable::iterator hIter;

	// <iterator,bool> pair for the insert operation
	pair<hashTable::iterator, bool> p;

	int item, i;

	// insert elements from intArr, noting duplicates
	for (i = 0; i < arrSize; i++)
	{
		p = ht.insert(intArr[i]);
		if (p.second == false)
			cout << "Duplicate value " << intArr[i] << endl;
	}

	// output the hash size which reflects duplicates
	cout << "Hash table size " << ht.size() << endl;

	// prompt for item to erase and indicate if not found
	for (i = 1; i <= 2; i++)
	{
		cout << "Enter a number to delete: ";
		cin >> item;

		if ((hIter = ht.find(item)) == ht.end())
			cout << "Item not found" << endl;
		else
			ht.erase(hIter);
	}

	// output the elements using an iterator to scan the table
	for (hIter = ht.begin(); hIter != ht.end(); hIter++)
		cout << *hIter << "  ";
	cout << endl;

	return 0;
}

/*
Run:

Duplicate value 9
Duplicate value 16
Hash table size 8
Enter a number to delete: 10
Item not found
Enter a number to delete: 17
14  8  16  9  3  12  20
*/
