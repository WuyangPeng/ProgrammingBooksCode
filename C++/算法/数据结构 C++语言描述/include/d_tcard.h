#ifndef TIMECARD_CLASS
#define TIMECARD_CLASS

#include <iostream>

#include "d_time24.h"
#include "d_except.h"
#include "d_util.h"

using namespace std;

class timeCard
{
	public:
		timeCard(const string& ssno, double rate, int punchInHour,
					int punchInMinute);

		void punchOut(const time24& t);
			// assign t to punchOutTime and set hasPunched to true

		void writeSalaryInfo();
			// output a log that includes the beginning and ending times for
			// the day's work, the amount of time worked, the pay rate
			// and the earnings.
			// precondition:  throw a rangeError exception if worker has not
			//						punched out (hasPunched == false)

	private:
		string workerID;
		time24 punchInTime, punchOutTime;	// supplier-class objects
		double payrate;
		bool hasPunched;
};

// use initialization list to initialize data members
timeCard::timeCard(const string& ssno, double rate, int punchInHour,
						 int punchInMinute):
		workerID(ssno), payrate(rate), hasPunched(false),
		punchInTime(punchInHour, punchInMinute)
{}

void timeCard::punchOut(const time24& t)
{
	punchOutTime = t;
	hasPunched = true;
}

void timeCard::writeSalaryInfo()
{
	// throw an exception if the worker did not punch out
	if (hasPunched == false)
		throw rangeError("timeCard: writeSalaryInfo() called before "
							  "punching out");

	// total time worked
	time24 timeWorked = punchInTime.duration(punchOutTime);
	// hours and fraction of an hour worked
	double hoursWorked = timeWorked.getHour() +
								timeWorked.getMinute()/60.0;

	// format the output
	cout << "Worker:      " << workerID << endl;
	cout << "Start time: ";
	punchInTime.writeTime();
	cout << "  End time: ";
	punchOutTime.writeTime();
	cout << endl;
	cout << "Total time:  " << setreal(1,2) << hoursWorked
		  << " hours" << endl;
	cout << "At $" << setreal(1,2) << payrate
		  << " per hour, the days earnings are $"
		  << setreal(1,2) << payrate*hoursWorked << endl;
}

#endif	// TIMECARD_CLASS
