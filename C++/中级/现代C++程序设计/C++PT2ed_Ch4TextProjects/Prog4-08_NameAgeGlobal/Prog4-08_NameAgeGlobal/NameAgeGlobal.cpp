//Simple Functions and How Old Are You?
//Global variables

#include <iostream>
#include <string>

using namespace std;

//Functions do not pass or return anything
//since they are working with global variables.
void WriteHello();	
void AskForName();
void AskForAge();
void Write();

//global variables
//all functions in this file can see them
int age;
string name;

int main()
{
	//Write a greeting
	WriteHello();			

	//Ask for the user's name
	AskForName();

	//Ask for age
	AskForAge();		

	//Write information
	Write();

	return 0;
}


//Write_Hello writes a greeting message to the screen
void WriteHello()	
{
	cout << "Hello from a C++ function!\n";
}

//AskForAge asks the user for age, returns age.
void AskForAge()		
{
	cout << "How old are you?  ";
	cin >> age;
	cin.ignore();   //remove enter key
}

//AskForName asks the user's name
void AskForName()	
{
	cout << "What is your name?  ";
	getline(cin,name);
}


//Write writes the name and age to the screen
void Write()	
{
	cout << "Hi " << name << "! You are " 
			<< age << " years old.  \n";
}

