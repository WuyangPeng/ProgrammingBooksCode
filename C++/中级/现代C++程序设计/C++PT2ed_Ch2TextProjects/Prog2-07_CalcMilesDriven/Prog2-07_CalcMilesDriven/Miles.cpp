//This program calculates the number of miles and hours
//traveled based on average speed and days driven.

#include <iostream>		//for cout
using namespace std;


int main()
{
	//declare our variables here
	//we can assign the values when declared

	double speed = 68.0;	//average rate mph
	int daysOnRoad = 4;		//driving days
	double hrsEachDay = 7.5;	 //hours driven per day

	double dailyMiles, totalMiles, totalHoursDriven;

	//calculate miles driven each day hours x speed
	dailyMiles = hrsEachDay * speed;

	//calculate total hours by days x hours
	totalHoursDriven = daysOnRoad * hrsEachDay;

	//total miles is total hours x average rate 
	//(or could have used daily miles x days driven)
	totalMiles = totalHoursDriven * speed;

	cout << "Driving Trip Summary";
	cout << "\n" << daysOnRoad << " days on road driving " << speed 
			<< " mph for " << hrsEachDay << " hours each day";
	cout << "\n\nDaily miles: " << dailyMiles;
	cout << "\nTotal driving hours: " << totalHoursDriven;
	cout << "\nTotal miles driven: " << totalMiles << "\n";

	return 0;
}
