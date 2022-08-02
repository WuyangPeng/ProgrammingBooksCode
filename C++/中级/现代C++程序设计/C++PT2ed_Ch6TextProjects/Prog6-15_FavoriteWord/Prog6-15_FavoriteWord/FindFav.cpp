//Favorite Word Program Using C-Strings
//Ask the user for a word and a phrase 
//and determine if the word is in the phrase. 

//This version uses C-string arrays and the
//strstr and strcmp functions.

#include <iostream>
#include <string>
using namespace std;

bool FindFavorite(char phrase[], char word[]);

int main( )
{
	char phrase[60],word[20], answer[5];

	do
	{
		cout << "Enter your favorite word ===>  ";
		cin.getline(word,20);

		cout << "Enter a phrase ==>  ";
		cin.getline(phrase,60);

		bool find_it = FindFavorite(phrase,word);
	
		if(find_it == true)
			cout << "\nI see \"" << word << "\" :-) \n";
		else
			cout << "\nI don't see \"" << word << "\" :-(\n";

		cout << "Do it again?   Enter yes or no  ==> ";
		cin.getline(answer,5);
		cout << endl;
		//strcmp returns 0 if C-strings match
	}while(strcmp(answer,"yes")== 0);  
	return 0;
}

bool FindFavorite(char phrase[], char word[])
{
	bool result;
	char* IsItThere;     //declare a character pointer for strstr

	IsItThere = strstr(phrase,word);

	if(IsItThere == NULL)  
		result = false;
	else 
		result = true;
	
	return result;
}

