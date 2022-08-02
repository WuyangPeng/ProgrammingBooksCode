/*********************************************************************

  Filename:  stl_strg.cpp
  Section:   18     STL  Strings
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string sentence, words[10];
	int pos = 0, old_pos = 0, nwords, i = 0;

	sentence = "Eskimos have 23 ways to ";
   sentence += "describe snow";

	while (pos < sentence.size()) {
		pos = sentence.find(' ', old_pos);
		words[i++].assign(sentence, old_pos, pos - old_pos);
		cout << words[i - 1] << endl; //print words
		old_pos = pos + 1;
	}
	nwords = i;
	sentence = "C++ programmers ";
	for (i = 1; i < nwords -1; ++i)
		sentence += words[i] + ' ';
	sentence += "windows";
	cout << sentence << endl;
}
