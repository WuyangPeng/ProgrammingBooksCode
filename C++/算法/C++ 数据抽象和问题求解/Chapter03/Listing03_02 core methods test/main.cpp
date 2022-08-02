//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
#include <iostream>
#include <string>
#include "ArrayBag.h"
using namespace std;

void displayBag(ArrayBag<string>& bag)
{
   cout << "The bag contains " << bag.getCurrentSize()
        << " items:" << endl;
   vector<string> bagItems = bag.toVector();
   int numberOfEntries = (int)bagItems.size();
   for (int i = 0; i < numberOfEntries; i++)
   {
      cout << bagItems[i] << " ";
   }  // end for
   cout << endl << endl;
}  // end displayBag

void bagTester(ArrayBag<string>& bag)
{
   cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 1 (true)" << endl;
   displayBag(bag);
   
   string items[] = {"one", "two", "three", "four", "five", "one"};
   cout << "Add 6 items to the bag: " << endl;
   for (int i = 0; i < 6; i++)
   {
      bag.add(items[i]);
   }  // end for
   
   displayBag(bag);
   
   cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 0 (false)" << endl;
   
   cout << "getCurrentSize: returns " << bag.getCurrentSize()
        << "; should be 6" << endl;
   
   cout << "Try to add another entry: add(\"extra\") returns "
        << bag.add("extra") << endl;
} // end bagTester

int main()
{
   ArrayBag<string> bag;
   cout << "Testing the Array-Based Bag:" << endl;
   cout << "The initial bag is empty." << endl;
   bagTester(bag);
   cout << "All done!" << endl;
   
   return 0;
} // end main

/*
 Testing the Array-Based Bag:
 The initial bag is empty.
 isEmpty: returns 1; should be 1 (true)
 The bag contains 0 items:
 
 
 Add 6 items to the bag:
 The bag contains 6 items:
 one two three four five one
 
 isEmpty: returns 0; should be 0 (false)
 getCurrentSize: returns 6; should be 6
 Try to add another entry: add("extra") returns 0
 All done!
*/
