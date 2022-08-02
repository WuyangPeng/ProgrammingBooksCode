// File: prg8_1.cpp
// the program outputs the interview schedule for a personnel director.
// the executive secretary constructs a queue of appointment times
// by reading the times from the keyboard. by cycling through the
// queue, the secretary outputs the time at which each appointment
// begins and the available time until the next scheduled
// appointment. the last interview ends at 5:00 PM
 
#include <iostream>
#include <iomanip>
#include <queue>

#include "d_time24.h"

using namespace std;

int main()
{
	time24 interviewTime;
	// queue to hold appointment time for job applicants
	queue<time24> apptQ;

	cout << "First interview of the day: ";
	cin >> interviewTime;

	// construct the queue until input is 5:00 PM or later
	while (interviewTime < time24(17,0))
	{
		//  push the interview time on the queue
		apptQ.push(interviewTime);

		// prompt for the next interview time
		cout << "Next interview: ";
		cin >> interviewTime;
	}

	// output the day's appointment schedlule
	cout << endl << "Appointment    Available Interview Time" << endl;

	// pop the next applicant appointment time and determine available
	// time for interview by checking time for applicant at the front
	// of the queue
	while (!apptQ.empty())
	{
		interviewTime = apptQ.front();
		apptQ.pop();

		// output available time. if the queue is empty,
		// the interview ends at 5:00 PM
		cout << "  " << interviewTime << setw(17) << "  "; 
		if (apptQ.empty())
			cout << (time24(17,0) - interviewTime) << endl;
		else
			cout << (apptQ.front()-interviewTime) << endl;
	}

	return 0;
}

/*
Run:

First interview of the day: 9:00
Next interview: 10:15
Next interview: 11:15
Next interview: 13:00
Next interview: 13:45
Next interview: 14:30
Next interview: 15:30
Next interview: 16:30
Next interview: 17:00

Appointment    Available Interview Time
   9:00                  1:15
  10:15                  1:00
  11:15                  1:45
  13:00                  0:45
  13:45                  0:45
  14:30                  1:00
  15:30                  1:00
  16:30                  0:30
*/
