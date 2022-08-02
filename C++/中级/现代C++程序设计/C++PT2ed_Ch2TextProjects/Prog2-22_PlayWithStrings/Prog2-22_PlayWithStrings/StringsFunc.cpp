//C++ string objects, size and searching

#include <iostream>		//for cout, cin, getline
#include <string>		//for string

using namespace std;

int main()
{
	//declare 2 string objects
	string sentence;
	string word;

	cout << "C++ String Demo";
	
	//ask the user to enter a sentence and a word
	//use getline function to read from input into string
	cout << "\n\nPlease enter a sentence  \n ==> ";
	getline(cin, sentence);

	cout << "\nPlease enter a word  ==> ";
	getline(cin,word);

	//Ask each object to tell us how many chars are
	//in its data.

	int sentSize = sentence.size();
	int wordSize = word.size();

	//Search to find where the word is in the sentence.
	//Ask the sentence object to find the word???
	int wordInSentence = sentence.find(word);

	cout << "String Demo Results"
			<< "\nSentence: " << sentence
			<< "\nWord: " << word
			<< "\nSentence size " << sentSize
			<< "\nWord size " << wordSize
			<< "\nWord location in Sentence: " 
			<< "(-1 not in sentence ): " << wordInSentence << endl;

	return 0;
}


