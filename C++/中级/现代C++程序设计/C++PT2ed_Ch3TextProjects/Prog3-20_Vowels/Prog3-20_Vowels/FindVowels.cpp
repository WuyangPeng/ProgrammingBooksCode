//Program to search a string for the 5 vowels, 
//and count the punctuation marks and spaces.

#include <iostream>		//for cout, getline
#include <string>		//for string
#include <cctype>		//for tolower(), ispunct(), isspace()

using namespace std;

int main()
{

	cout << "Welcome to the C++ Vowel Counter Program\n";

	string answer = "yes";	//need to initialize so we get in the loop
	string sentence;
	char letter;

	int aCount, eCount, iCount, oCount, uCount;
	int punctCount, spaceCount;

	while(answer == "yes")
	{
		//Set the count values to zero, 
		//so we get an accurate count with each sentence.
		aCount = eCount = iCount = oCount = uCount = 0;
		punctCount = 0;
		spaceCount = 0;
		
		cout << "Enter a sentence \n==> ";
		getline(cin,sentence);

		for(int i = 0; i < sentence.size(); ++i)
		{
			letter = sentence.at(i);
			letter = tolower(letter);  //convert letter here

			switch(letter)
			{
			case 'a':
				aCount++;
				break;
			case 'e':
				eCount++;
				break;
			case 'i':
				iCount++;
				break;
			case 'o':
				oCount++;
				break;
			case 'u':
				uCount++;
				break;
			}
			if(ispunct(letter) != 0)  //return non-zero if true
				punctCount++;
			
			if(isspace(letter) >0 ) //returns non-zero if true
				spaceCount++;
		}

		cout << "\nResults from: " << sentence;
		cout << "\nA/a " << aCount	
				<< "\nE/e " << eCount
				<< "\nI/i " << iCount
				<< "\nO/o " << oCount
				<< "\nU/u " << uCount 
				<< "\nPunctuation marks " << punctCount
				<< "\nSpaces " << spaceCount << endl;

		cout << "\nDo another sentence?  yes/no ";
		getline(cin,answer);
	}

	return 0;
}