// File: prg8_3.cpp
// the program uses a queue to simulate the flow of customers
// in and out of an automated car wash. prompt the user for the
// fixed probability that a car will arrive at any minute of the
// day and the fixed number of minutes it takes for a
// car wash. also input the opening and closing times. the
// simulation steps from opening to closing time in increments
// of 1 minute. each iteration determines if a car arrives and,
// if so pushes the time of arrival in the queue of waiting
// customers. next, determine whether the car wash is busy. if
// it is avaiable, pop the longest waiting customer from the
// queue and update simulation parameters. when the simulation
// loop terminates, output the accumuated parameters, that
// include the total number of cars washed, the maximum waiting
// time for a customer, the average customer waiting time, the
// percentage of the day the car wash operates, and the number
// of customers remaining to serve when the car wash closes

#include <iostream>
#include <queue>

#include "d_time24.h"
#include "d_random.h"

using namespace std;

// returns the time t in minutes
int minutes(const time24& t);

int main()
{
	time24 carArrival;				// stores time of customer's arrival
	queue<time24> waitQueue;		// queue for car arrival objects

	time24 waitTime, maxWaitTime;	// maxWaitTime initially 0:00
	time24 totalWaitTime;			// total time customers wait			 
	time24 totalServiceTime;		// total time equipment is in use
	time24 startTime, endTime;		// times for the simulation
	time24 t, finishWash;			// used in simulation loop

	randomNumber rnd;					// use for random number generation

	double probOfArrival;			// probability customer arrives
	int numberOfWashes = 0;			// number of cars washed in study
	int washTime;						// fixed time for a wash in minutes

	bool washAvailable = true;		// indicates whether wash available

	// real number output is fixed format, with 1 decimal place
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(1);

	// series of inputs to customize the simulation run
	cout << "Enter probability of arrival and wash time: ";
	cin >> probOfArrival >> washTime;
	cout << "Enter time to start and end simulation: ";
	cin >> startTime >> endTime;
	cout << endl;

	// loop views and updates system each minute of the study
	for (t = startTime; t < endTime; t += 1)
	{	// check if customer arrives; if so store arrival time in queue
		if(rnd.frandom() <= probOfArrival)
		{
			carArrival = t; 
			waitQueue.push(carArrival);
		}

		// if car finishes wash, indicate wash is available
		if (washAvailable == false && t == finishWash)
			washAvailable = true;

		// if wash is available, get front car from queue
		if (washAvailable)
			if (!waitQueue.empty())
			{
				// pop next car from queue and update data for summary
				carArrival = waitQueue.front();
				waitQueue.pop();

				// find the waiting time of the next customer
				waitTime = t - carArrival;
				// update the maximum customer waiting time
				if (maxWaitTime  < waitTime)
					maxWaitTime = waitTime;
				// add waiting time for customer to totalWaitTime.
				totalWaitTime += waitTime;
				// add time to wash car to totalServiceTime for the equipment
				totalServiceTime += washTime;
				// determine the time the car will exit from the wash
				finishWash = t + washTime;
				// increment the number of customers served
				numberOfWashes++;
				// set washAvailable to false since equipment back in service
				washAvailable  = false;
			}
	}

	// output the summary data for the simulation include number of cars
	// washed, average customer waiting time and pct of time wash operates
	cout << "Total number of cars washed is " << numberOfWashes << endl;
	cout << "Maximum customer waiting time for a car wash is " 
		  << minutes(maxWaitTime) << " minutes" << endl;
	cout << "Average customer waiting time for a car wash is " 
		  << double(minutes(totalWaitTime))/numberOfWashes << " minutes"
		  << endl;
	cout << "Percentage of time car wash operates is  " 
		  << double(minutes(totalServiceTime))/minutes(endTime-startTime)*100.0
		  << '%' << endl;
	cout << "Number of customers remaining at " << endTime 
		  << " is " << waitQueue.size() << endl;

	return 0;
}

int minutes(const time24& t)
{
	return t.getHour() * 60 + t.getMinute();
}

/*
Run 1:

Enter probability of arrival and wash time: .1 11
Enter time to start and end simulation: 8:00 17:00

Total number of cars washed is 49
Maximum customer waiting time for a car wash is 100 minutes
Average customer waiting time for a car wash is 7.1 minutes
Percentage of time car wash operates is  99.8%
Number of customers remaining at 17:00 is 10

Run 2:

Enter probability of arrival and wash time: .2 3
Enter time to start and end simulation: 8:00 17:00

Total number of cars washed is 123
Maximum customer waiting time for a car wash is 9 minutes
Average customer waiting time for a car wash is 2.2 minutes
Percentage of time car wash operates is  68.3%
Number of customers remaining at 17:00 is 0

Run 3:

Enter probability of arrival and wash time: .25 4
Enter time to start and end simulation: 8:00 17:00

Total number of cars washed is 127
Maximum customer waiting time for a car wash is 29 minutes
Average customer waiting time for a car wash is 7.8 minutes
Percentage of time car wash operates is  94.1%
Number of customers remaining at 17:00 is 1
*/
