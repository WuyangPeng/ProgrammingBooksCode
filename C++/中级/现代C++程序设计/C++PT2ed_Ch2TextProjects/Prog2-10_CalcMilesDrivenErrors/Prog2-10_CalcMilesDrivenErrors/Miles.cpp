//This program illustrates what happens if the 
//programmer forgets to initialize his data variables. 

#include <iostream>		//for cout
using namespace std;


int main()
{
	//declare our variables here

	double speed, hrsEachDay;	//rate, daily duration
	int daysOnRoad;				//driving days

	double dailyMiles, totalMiles, totalHoursDriven;

	//calculate miles driven each day hours x speed
	dailyMiles = hrsEachDay * speed;

	//calculate total hours by days x hours
	totalHoursDriven = daysOnRoad * hrsEachDay;

	//total miles is total hours x average rate 
	//(or could have used daily miles x days driven)
	totalMiles = totalHoursDriven * speed;

	cout << "Driving Trip Summary ";
	cout << "\n" << daysOnRoad << " days on road driving " << speed 
			<< " mph for " << hrsEachDay << " hours each day";
	cout << "\n\nDaily miles: " << dailyMiles;
	cout << "\nTotal driving hours: " << totalHoursDriven;
	cout << "\nTotal miles driven: " << totalMiles << "\n";

	return 0;
}
