//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 4-4. */
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void displayBag(BagInterface<string>* bagPtr)
{
   cout << "The bag contains " << bagPtr->getCurrentSize()
   << " items:" << endl;
	vector<string> bagItems = bagPtr->toVector();
   
   int numberOfEntries = (int)bagItems.size();
   for (int i = 0; i < numberOfEntries; i++)
   {
      cout << bagItems[i] << " ";
   }  // end for
   cout << endl << endl;
}  // end displayBag

void bagTester(BagInterface<string>* bagPtr)
{
   cout << "isEmpty: returns " << bagPtr->isEmpty()
   << "; should be 1 (true)" << endl;
   
   string items[] = {"one", "two", "three", "four", "five", "one"};
   cout << "Add 6 items to the bag: " << endl;
   for (int i = 0; i < 6; i++)
   {
      bagPtr->add(items[i]);
   }  // end for
   
   displayBag(bagPtr);
   cout << "isEmpty: returns " << bagPtr->isEmpty()
   << "; should be 0 (false)" << endl;
   cout << "getCurrentSize returns : " << bagPtr->getCurrentSize()
   << "; should be 6" << endl;
   cout << "Try to add another entry: add(\"extra\") returns "
   << bagPtr->add("extra") << endl;
}  // end bagTester

int main()
{
   BagInterface<string>* bagPtr = nullptr;
   char userChoice;
   cout << "Enter 'A' to test the array-based implementation\n"
   << " or 'L' to test the link-based implementation: ";
   cin >> userChoice;
   if (toupper(userChoice) == 'A')
   {
      bagPtr = new ArrayBag<string>();
      cout << "Testing the Array-Based Bag:" << endl;
   }
   else
   {
      bagPtr = new LinkedBag<string>();
      cout << "Testing the Link-Based Bag:" << endl;
   }  // end if
   
   cout << "The initial bag is empty." << endl;
   bagTester(bagPtr);
   delete bagPtr;
   bagPtr = nullptr;
   cout << "All done!" << endl;
   
   return 0;
}  // end main

/*
 Enter 'A' to test the array-based implementation
 or 'L' to test the link-based implementation: A
 Testing the Array-Based Bag:
 The initial bag is empty.
 isEmpty: returns 1; should be 1 (true)
 Add 6 items to the bag:
 The bag contains 6 items:
 one two three four five one
 
 isEmpty: returns 0; should be 0 (false)
 getCurrentSize returns : 6; should be 6
 Try to add another entry: add("extra") returns 0
 All done!
 
 
 Enter 'A' to test the array-based implementation
 or 'L' to test the link-based implementation: L
 Testing the Link-Based Bag:
 The initial bag is empty.
 isEmpty: returns 1; should be 1 (true)
 Add 6 items to the bag:
 The bag contains 6 items:
 one five four three two one
 
 isEmpty: returns 0; should be 0 (false)
 getCurrentSize returns : 6; should be 6
 Try to add another entry: add("extra") returns 1
 All done!
 */


