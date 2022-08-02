//File: Person.cpp

#include "Person.h"
#include <string>
#include <iostream>
using namespace std;

Person::Person()
{
	name = "";
	age = 0;
	daysToFromBday = 0;
	bHadABirthday = false;
}

void Person::CalcDaysToFromBday()
{	
	//We need the day of year for the 
	//bday and today. Problem is if the
	//person was born in a leapyear,
	//our diff would be one day off.
	//For example:
	//Mar 1, 2000 = 61th day
	//Mar 1, 1999 = 60th day

	//To solve, we'll make our own date using
	//today's month & day, and bday's year.
	//We use the Date's overloaded constructor.
	//We pass in a "" string, since it won't be used.
	Date check(today.GetMonth(), today.GetDay(),
				bday.GetYear(), ""); 

	//Now take the difference from bday and today
	int diff;
	diff = bday.GetDayOfYear() - check.GetDayOfYear();
	
	//if the diff is 0 or negative
	//then the person already had a Bday
	if(diff <= 0) 
	{
		daysToFromBday = -1*diff;
		bHadABirthday = true;
	}	
	else
	{
		daysToFromBday = diff;
		bHadABirthday = false;
	}
}

void Person::CalculateAge()
{	
	age = today.GetYear() - bday.GetYear();

	//This calc depends on knowing if person has
	//had a birthday. Need to be sure we have 
	//called CalcDays. Since these are both 
	//private functions, we are OK since we
	//know from whence we came. 

	//if the person did not yet had a Bday
	if(bHadABirthday == false ) age--;
	
}

void Person::AskForBDayInfo()
{
	//ask for the name
	cout<<"What is your name? ";
	getline(cin,name);

	//ask for the birthday
	int d,m,y;
	char slash;
	cout <<"" << name 
		 << ", when is your birthday (M/D/Y)? ";
	cin >> m >> slash >> d >> slash >> y;

	//remove newline from input queue
	cin.ignore();

	//set data into birthday object
	string des = name + "'s Birthday";
	bday.SetDate(m,d,y,des); 
	
	//Must call CalcDays function before the
	//CalcAge function! See notes in CalcAge.
	CalcDaysToFromBday();
	CalculateAge();
}


void Person::WriteBDayInfo()
{
	cout << "\n" << bday.GetFormattedDate() <<
		" makes him/her " << age << " years old.";

	//first check if it is his/her birthday
	if(daysToFromBday == 0)
	{
		cout<<"\nHappy birthday!!!" << endl;
		return;
	}
	
	//not a birthday, so write results
	if(bHadABirthday == true)
	{
		cout << "\n" << name << " had his/her birthday "
			<< daysToFromBday<<" days ago.\n\n";
	}
	else
	{
		cout << "\n" << name 
			<< " will have his/her birthday in "
			<< daysToFromBday << " days.\n\n" ;
	}
}