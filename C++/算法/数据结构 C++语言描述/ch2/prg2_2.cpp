// File: prg2_2.cpp
// the program simulates a temporary employees arriving
// at work and leaving when the plant closes at 5:00 PM.
// it prompts for the hour and minute of arrival at work
// and the social security number. it uses the timeCard
// class to determine the employee pay for the day. the
// program uses a random number to simulate that 3 out of
// every 4 employees punch out. in this situation,
// the program must handle a rangeError exception thrown by
// the timeCard class when an employee does not punch out.
// the catch block simulates the supervisor punching out for
// the employee

#include <iostream>

#include "d_tcard.h"		// use timeCard class
#include "d_random.h"	// randomNumber class

using namespace std;

int main()
{
	// posted pay rate
	const double PAYRATE = 12.50;
	// work ends at 5:00 PM
	const time24 CHECKOUT(17,0);
	// employee data input from the keyboard
	string id;
	int inHour, inMinute;
	// simulate 1/4 of employees forgetting to punch out
	randomNumber rnd;

	cout << "Enter hour and minute of arrival at work: ";
	cin >> inHour >> inMinute;
	cout << "Enter social security number: ";
	cin >> id;

	// declare a timeCard object for the employee
	timeCard employee(id, PAYRATE, inHour, inMinute);

	// represents 3 out of 4 employees punching out
	if (rnd.frandom() > .25)
		// punch out
		employee.punchOut(CHECKOUT);

	// include writeSalary() call in a try block. it
	// throws the rangeError exception if the employee
	// has not punched out
	try
	{
		employee.writeSalaryInfo();
	}

	catch (const rangeError& re)
	{
		// output the error string in the rangeError object re
		cerr << re.what() << endl;
		// supervisor punches out the employee. display the salary information
		employee.punchOut(CHECKOUT);
		employee.writeSalaryInfo();
	}

   return 0;
}

/*
Run 1:

Enter hour and minute of arrival at work: 8 00
Enter social security number: 345-27-8156
Worker:      345-27-8156
Start time:  8:00    End time: 17:00
Total time:  9.0 hours
At $12.50 per hour, the days earnings are $112.50

Run 2:

Enter hour and minute of arrival at work: 9 15
Enter social security number: 766-25-6728
timeCard: writeSalaryInfo() called before punching out
Worker:      766-25-6728
Start time:  9:15    End time: 17:00
Total time:  7.75 hours
At $12.50 per hour, the days earnings are $96.88
*/
