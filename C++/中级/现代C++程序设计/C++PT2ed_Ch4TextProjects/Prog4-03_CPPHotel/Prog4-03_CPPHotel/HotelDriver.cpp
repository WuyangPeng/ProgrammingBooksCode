//A program that calculates the cost of a 
//room at the C++ Hotel.

#include <iostream>		//for cout, getline, cin
#include <vector>		
#include <string>
#include <iomanip>		//for setw()

using namespace std;

//Function declarations (prototypes)
void WriteGreeting();
int HowManyPeople();
int HowManyNights();
string WhatTypeRoom();
float CalcCost(int people, int nights, string roomType);
void WriteCostSummary(int people, int nights, 
					  string roomType, float cost);


int main()
{
	int numPeople, numNights;
	float totalCost;
	string roomType;

	//Calling the functions 
	WriteGreeting();

	//Ask for data
	numPeople = HowManyPeople();
	numNights = HowManyNights();
	roomType = WhatTypeRoom();

	//Calculate cost
	totalCost = CalcCost(numPeople, numNights, roomType);

	//Display results
	WriteCostSummary(numPeople, numNights, roomType,totalCost);

	return 0;
}


//obtain the number of guest
int HowManyPeople()
{
	int num;
	cout << "\nHow many people will be staying with us? ";
	cin >> num;
	cin.ignore();	//remove the Enter key

	return num;
}

//obtain the number of nights
int HowManyNights()
{
	int num;
	cout << "How many nights are you staying? ";
	cin >> num;
	cin.ignore();

	return num;
}

//find out what type of room 
string WhatTypeRoom()
{
	vector<string> vRooms;
	
	vRooms.push_back("parking lot view");
	vRooms.push_back("swimming pool view");
	vRooms.push_back("beach view");

	cout << "What type of room? ";
	for(int i = 0; i < vRooms.size(); ++i)
		cout << "\n" << i+1 << setw(20) << vRooms.at(i);

	cout << "\nEnter your choice here ==> ";

	int whichOne;
	cin >> whichOne;
	cin.ignore();

	return vRooms.at(whichOne-1);
}

//calc total room cost based on number of guest and room
float CalcCost(int people, int nights, string roomType)
{
	float totalCost, rate;
	float addPersonCost = static_cast<float>(0.0);

	if(people > 1)
		addPersonCost = static_cast<float>(10.00) * (people-1);

	//room cost:
	//parking lot view  $69.95/night
	//swimming pool view  $79.95/night
	//beach view  $99.95/night

	if(roomType == "parking lot view")
		rate = static_cast<float>(69.95);
	else if(roomType == "swimming pool view")
		rate = static_cast<float>(79.95);
	else if(roomType == "beach view")
		rate = static_cast<float>(99.95);

	totalCost = (rate + addPersonCost) * nights;

	return totalCost;
}

//display a hotel program greeting
void WriteGreeting()
{
	cout << "Welcome to the C++ Hotel Rate Program";
}

//write all info to the screen
void WriteCostSummary(int numPeople, int numNights, 
							string roomType, float cost)
{
	//Set precision to see $xxx.xx format
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "C++ Hotel Rate Information: "
		<< "\nYour cost for a " << roomType << " room for "
		<< numPeople << " people for " << numNights 
		<< " nights is $ " << cost << endl;

}
