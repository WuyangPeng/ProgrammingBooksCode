#ifdef __BORLANDC__
// suppress the warning message about comparing signed and unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

// File: prg9_3.cpp
// the program prompts the user to enter the number of words
// the program should jumble. in a loop, the user enters the words.
// program inserts each letter of word into a doubly linked list of
// characters based on generating a random integer with value
// 0 or 1. if the value is 0, insert the character at the front of
// the linked list; otherwise, insert it at the back. the function
// insert() from "d_nodel.h" implements list insertion operations.
// displaying the list using the function writeDLinkedList()
// gives a jumbled version of the word. calling the clear()
// deletes the list so the next iteration will create a new list.

#include <iostream>
#include <string>

#include "d_node.h"		// node class
#include "d_nodel.h"		// for writeDLinkedList(), insert(), erase()
#include "d_random.h"	// use random integers

using namespace std;

// clear the list
template <typename T>
void clear(dnode<T> *header);

int main()
{
   // header node for list holding jumbled characters
   dnode<char> *header = new dnode<char>;
   string word;
   int numWords, i, j;
	randomNumber rnd;

   // prompt for the number of words to enter
	cout << "How many words will you enter? ";
	cin >> numWords;
	cout << endl;

   for (i = 0; i < numWords; i++)
   {
		cout << "Word: ";
		cin >> word;

      // use rnd.random(2) to determine if the char is inserted
      // at the front (value = 0) or back (value = 1) of the list
      for (j = 0; j < word.length(); j++)
         if (rnd.random(2) == 0)
				// insert at the front of the list
            insert(header->next, word[j]);
         else
				// insert at the back of the list
         	insert(header, word[j]);

      // output the word and its jumbled variation
      cout << "Word/Jumbled Word: " << word << "   ";
      writeDLinkedList(header);
      cout << endl << endl;

      // clear the list in preparation for the next word
      clear(header);
   }

   return 0;
}

template <typename T>
void clear(dnode<T> *header)
{
	// repeatedly remove the first node in the list
	// until the list is empty. this condition occurs
	// when the header points to itself
	while(header->next != header)
		erase(header->next);
}

/*
Run:

How many words will you enter? 4

Word: C++
Word/Jumbled Word: C++   +  C  +

Word: before
Word/Jumbled Word: before   o  f  e  b  r  e

Word: jumbled
Word/Jumbled Word: jumbled   d  b  j  u  m  l  e

Word: link
Word/Jumbled Word: link   k  n  i  l
*/
