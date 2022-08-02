//Using overloaded functions to say goodnight. 

#include <iostream>
#include <string>

using namespace std;

//four different prototypes, same function name
void SayGoodnight();    
void SayGoodnight(string name1);
void SayGoodnight(string name1, string name2);
void SayGoodnight(int number);

int main()
{
	//call all four overloaded functions
	SayGoodnight();
	SayGoodnight("Bob");
	SayGoodnight("Susan", "Melissa");
	SayGoodnight(5);

	cout << "\nAll done saying Goodnight!  \n";
	return 0;
}

//a standard goodnight message
void SayGoodnight()
{
	cout << "Goodnight! Sleep tight. "
			<< " Don't let the bed bugs bite. ";
}

//say goodnight to one person
void SayGoodnight(string name1)
{
	cout << "\nGoodnight, " << name1 << "!";
}

//say goodnight to two people
void SayGoodnight(string name1, string name2)
{
	cout << "\nGoodnight, " << name1 << " and "
			<< name2 << "!" ;
}

//say goodnight a number of times
void SayGoodnight(int number)
{
	for(int i = 0; i < number; ++ i)
		cout << "\nGoodnight!";
}

