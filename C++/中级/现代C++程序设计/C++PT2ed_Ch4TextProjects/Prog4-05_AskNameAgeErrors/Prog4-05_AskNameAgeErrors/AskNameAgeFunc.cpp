//Simple Functions and How Old Are You?
//This does not compile!

#include <iostream>
#include <string>

using namespace std;

//Function prototypes (or declarations)
void WriteHello();	
string AskForName();
int AskForAge();
void Write(string name, int age);

int main()
{
	int age;			//declare our variables here
	string name;

	//Write a greeting
	WriteHello();			

	//Ask for the user's name
	name = AskForName();	

	//Ask for age
	age = AskForAge();		

	//Write information
	Write(name, age);		

	return 0;
}

//Function definitions follow main

//Write_Hello writes a greeting message to the screen
void WriteHello()	
{
	cout << "\n Hello from a C++ function!\n";
}

//AskForAge asks the user for age, returns age.
int AskForAge()		
{
	cout << "\n How old are you?  ";
	cin >> age;
	cin.ignore();   //remove enter key
	return age;
}

//AskForName asks the user's name
string AskForName()	
{
	cout << "\n What is your name?  ";
	getline(cin,name);
	return name;
}


//Write writes the name and age to the screen
void Write(string name, int age)	
{
	cout << "\n Hi " << name << "! You are " 
			<< age << " years old.  \n";
}

