//Favorite Word Program using C++ strings.
//Ask the user for a word and a phrase 
//and determine if the word is in the phrase. 

//This version uses C++ string objects and the
//string class' find function.

#include <iostream>
#include <string>
using namespace std;

bool FindFavorite(string phrase, string word);

int main( )
{
	string phrase,word, answer;

	do
	{
		cout << "Enter your favorite word ===>  ";
		getline(cin,word);

		cout << "Enter a phrase ==>  ";
		getline(cin, phrase);

		bool find_it = FindFavorite(phrase,word);
	
		if(find_it == true)
			cout << "\nI see \"" << word << "\" :-) \n";
		else
			cout << "\nI don't see \"" << word << "\" :-(\n";


		cout << "Do it again?   Enter yes or no  ==> ";
		getline(cin, answer);
		cout << endl;

		//can just compare using == operator
	}while(answer == "yes");  
	return 0;
}

#include <vector>
bool FindFavorite(string phrase, string word)
{
	bool result;
	int WhereIsIt;		//find searches the phrase,
						//returns location if in phrase
						//-1 if not there

	WhereIsIt = phrase.find(word);

	if(WhereIsIt == -1)  
		result = false;
	else 
		result = true;
	
	return result;
}

