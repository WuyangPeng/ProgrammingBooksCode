// File: prg2_4.cpp
// in a loop, the user enters the starting time for three
// appointments and the length of each appointment in minutes.
// using the time24 output and + operators, the program displays
// the starting and ending time for each appointment. during the
// loop, the program uses the time24 += operator to accumulate
// the total time required for the appointments

#include <iostream>

#include "d_time24.h"

using namespace std;

int main()
{
	time24 apptTime, totalApptTime;
	int apptLength;

	int i; 

	for (i = 1; i <= 3; i++)
	{
		// input appointment time and length of appointment
		cout << "Enter start of appointment and length in minutes: ";
		cin >> apptTime >> apptLength;

		// output starting and stopping time for appointment
		cout << "    Appointment " << i << ": Start: " << apptTime 
			  << "  Stop: " << (apptTime + apptLength) << endl;
		totalApptTime += apptLength;
	}

	// output total time spent with appointments
	cout << "Total appointment time: " << totalApptTime << endl;
	return 0;
}

/*
Run:

Enter start of appointment and length in minutes: 9:00 90
    Appointment 1: Start:  9:00  Stop: 10:30
Enter start of appointment and length in minutes: 11:30 120
    Appointment 2: Start: 11:30  Stop: 13:30
Enter start of appointment and length in minutes: 14:00 30
    Appointment 3: Start: 14:00  Stop: 14:30
Total appointment time:  4:00
*/
