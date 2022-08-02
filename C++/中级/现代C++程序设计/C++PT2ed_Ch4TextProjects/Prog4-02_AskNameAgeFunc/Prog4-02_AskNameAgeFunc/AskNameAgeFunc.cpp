//Simple Functions and How Old Are You?

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
	int age;
	string name;

	//Write a greeting
	WriteHello();			//call, no inputs, no return value

	//Ask for the user's name
	name = AskForName();	//call, returns name

	//Ask for age
	age = AskForAge();		//call, value assign into age

	//Write information
	Write(name, age);		//call, pass name, age to Write

	return 0;
}

//Function definitions follow main

//Write_Hello writes a greeting message to the screen
void WriteHello()	
{
	cout << "Hello from a C++ function!\n";
}

//AskForAge asks the user for age, returns age.
int AskForAge()		
{
	int age;
	cout << "How old are you?  ";
	cin >> age;
	cin.ignore();   //remove enter key
	return age;
}

//AskForName asks the user's name
string AskForName()	
{
	string name;
	cout << "What is your name?  ";
	getline(cin,name);
	return name;
}


//Write writes the name and age to the screen
void Write(string name, int age)	
{
	cout << "Hi " << name << "! You are " 
			<< age << " years old.  \n";
}

