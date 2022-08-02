//Use static_cast to compute Spider game stats correctly. 

#include <iostream>		//for cout
#include <iomanip>		//for setw()	
using namespace std;

int main()
{
	int daysInYear = 365;		//assume 2007, non-leapyear
	int gamesPlayed = 1693;		//wow, how many games did you win?
	int gamesWon = 115;		//not very good, are you?  ;-)

	float aveGamesPerDay, winPercent;
	
	//cast the integer number of games played into a float
	aveGamesPerDay= static_cast<float>(gamesPlayed)/daysInYear;

	//cast the games played into a float
	winPercent = static_cast<float>(gamesWon)/gamesPlayed * 100;

	//write results with 2 decimal places of accuracy
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(2);

	cout << "Spider Game Statistics for One Year \n\n" 
			<< setw(6) << gamesPlayed << " Games Played \n" 
			<< setw(6) << gamesWon<<" Games Won \n" 
			<< setw(6) << aveGamesPerDay <<" Ave Games Per Day \n" 
			<< setw(6) << winPercent << " % Win Rate " <<  "\n";

	return 0;
}
