// File: prg1_1.cpp
// the program uses time24 objects to compute the cost of
// parking a car in a public garage at the rate is $6.00 per hour.
// after the user inputs the times at which a customer enters and
// exits the garage, the program outputs a receipt that includes
// the enter and exit times, the length of time the car is parked
// and the total charges

#include <iostream>

#include "d_time24.h"

using namespace std;

int main()
{
	// cost of parking per hour
	const double PERHOUR_PARKING = 6.00;

	// objects designate when a car enters and leaves the garage
	// and the total amount of parking time
	time24 enterGarage, exitGarage, parkingTime;

	// length of billing time in hours
	double billingHours;

	cout << "Enter the times the car enters and exists the garage: ";
	enterGarage.readTime();
	exitGarage.readTime();

	// evaluate the total parking time
	parkingTime =  enterGarage.duration(exitGarage);

	// evaluate the parking time in minutes
	billingHours = parkingTime.getHour() + parkingTime.getMinute()/60.0;

	// output parking receipt including time of arrival, time
	// of departure, total parking time, and cost of parking
	cout << "Car enters at: ";
	enterGarage.writeTime();
	cout << endl;

	cout << "Car exits at: ";
	exitGarage.writeTime();
	cout << endl;

	cout << "Parking time: ";
	parkingTime.writeTime();
	cout << endl;

	cout << "Cost is $" << billingHours * PERHOUR_PARKING  << endl;

	return 0;
}

/*
Run:

Enter the times the car enters and exists the garage: 8:30 11:00
Car enters at:  8:30
Car exits at: 11:00
Parking time:  2:30
Cost is $15
*/
