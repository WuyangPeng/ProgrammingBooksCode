//File: Person.h

#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include "Date.h"
using namespace std;

class Person
{
	private:
			string name;
			Date bday, today;
			int age;	//person's age in years
			
			//number of days to/from birthday
			int daysToFromBday;			

			//birthday yet this year? 
			//based on today's date, 
			bool bHadABirthday;			

			void CalcDaysToFromBday();
			void CalculateAge();
			
	public:	
			Person();						
			void AskForBDayInfo();	//Calls CalcAge() & CalcDays()
			void WriteBDayInfo();
};


#endif
