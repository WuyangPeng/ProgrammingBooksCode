// File: prg2_3.cpp
// prompt the user for the time a movie starts and the
// length of the  movie. use the time24 + operator to determine
// when the movie ends. a bus always arrives in front of
// the theater at 22:45. use the time24 - operator to compute
// the waiting time at the bus stop. output the time the movie
// ends and the waiting time

#include <iostream>

#include "d_time24.h"

using namespace std;

int main()
{
	time24  startMovie, movieLength, endMovie,
           busArrival(22,45), waitingTime;

	// prompt and input times for movie to start and its length
	cout << "Enter the time the movie starts and its length: ";
	cin >> startMovie >> movieLength;

	// compute the time the movie ends and the waiting time for the bus
	endMovie = startMovie + movieLength;
	waitingTime = busArrival - endMovie;

	cout << "Movie ends at " << endMovie << endl;
	cout << "Waiting time for the bus is " << waitingTime << endl;

	return 0;
}

/*
Run:

Enter the time the movie starts and its length: 20:15  1:50
Movie ends at 22:05
Waiting time for the bus is  0:40
*/
