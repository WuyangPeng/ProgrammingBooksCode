#ifdef __BORLANDC__
// suppress the warning message about comparing signed and unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

// File: prg6_1.cpp
// the program prompts the user to enter a string which
// may include blank letters. it scans the individual characters in
// the string and copies all non-blank letters to the list charList.
// a call to the function isPalindrome() with charList as the argument
// determines whether the original string is or is not a palendrome

#include <iostream>
#include <string>
#include <list>
#include <ctype.h>		// for isalpha() and tolower()

// if Microsoft VC++, compensate for a getline() bug in <string>
#ifdef _MSC_VER
#include "d_util.h"
#endif _MSC_VER

using namespace std;

// check whether the values in alist read the same forward and
// backwards.  if so, return true; otherwise return false
template <typename T>
bool isPalindrome(const list<T>& alist);

int main()
{
	string str;
	list<char> charList;				// empty list of characters
	int i;
	char ch;

	// prompt the user to enter a string that may include blanks
	cout << "Enter the string: ";
	getline(cin, str, '\n');;

	// copy all of the non-blank letters as lowercase characters
	// to the list charList
	for (i = 0; i < str.length(); i++)
	{
		ch = str[i];
		if (isalpha(ch))
			charList.push_back(tolower(ch));
	}

	// call isPalindrome() and use the return value to designate
	// whether the string is or is not a palindrome
	if (isPalindrome(charList))
		cout << "'" << str << "' is a palindrome" << endl;
	else
		cout << "'" << str << "' is not a palindrome" << endl;

	return 0;
}

template <typename T>
bool isPalindrome(const list<T>& alist)
{
	list<T> copyList;

	copyList = alist;			// create a copy of the original list

	// check values at ends of list as long as list size > 1
	while (copyList.size() > 1)
	{
		// compare values on opposite ends; if not equal, return false
		if (copyList.front() != copyList.back())
			return false;
		// delete the objects
		copyList.pop_front();
		copyList.pop_back();
	}
	// if still have not returned, list is a palindrome
	return true;
}

/*
Run 1:
Enter the string: A man, a plan, a canal, Panama
'A man, a plan, a canal, Panama' is a palindrome

Run 2:
Enter the string: Go hang a salami, I'm a lasagna hog
'Go hang a salami, I'm a lasagna hog' is a palindrome

Run 3:
Enter the string: palindrome
'palindrome' is not a palindrome
*/
