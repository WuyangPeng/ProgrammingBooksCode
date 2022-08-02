//This program ask the user to enter the dimensions
//of her rectangular pond. It then calculates
//the volume and required pump size. 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	cout << "\C++'s Pond Pump Calculator Program"
			<< "\nWe'll determine the best C++ pump"
			<< " for your rectangular pond.";

	cout << "\n\nYour pump should be sized so that the entire "
			<< "pond volume \npumps through the filter twice "
			<< "in one hour.\n\n";
	
	vector<int> pumps;	//hold various pump sizes
	
	string answer;

	//First fill the pumps vector with the possible pumps
	//based on their gallons per hour pump rate.

	//C++ pumps come in these gph sizes:
	//350, 600, 950, 1200, 1600, 2500, 3200, 5000 gph
	pumps.push_back(350);    
	pumps.push_back(600);    
	pumps.push_back(950); 
	pumps.push_back(1200);
	pumps.push_back(1600);    
	pumps.push_back(2500);    
	pumps.push_back(3200);    
	pumps.push_back(5000);    

	//we'll assume pond dimensions are in inches
	int pondWidth, pondDepth, pondLength;
	
	do
	{

		cout << "Enter the pond's length, width, and depth: ";
		cin >> pondLength >> pondWidth >> pondDepth;

		cin.ignore();   //strip out enter key since getline is next read

		int cubicInchVol = pondLength * pondWidth * pondDepth;
		float totalGallons = cubicInchVol/231.0;   

		cout << "Your pond is " << totalGallons << " gallons.";

		//determine best sized pump 
		//figure out what pump needs to pump per hour
		int twiceCap = totalGallons * 2.0;

		int numPumps = pumps.size();
		int neededPumpIndex;  
		bool bGoodFit = true;	//set false if pump not adequate

		//First, is it a small pond?
		if(twiceCap < pumps.at(0))
		{
			neededPumpIndex = 0;
			if(twiceCap < pumps.at(0)/3)  //if pump is 3x too big
			{
				bGoodFit = false;
			}
		}
		//Or is it a very large pond?
		else if(twiceCap > pumps.at(numPumps-1) ) 
		{
			neededPumpIndex = numPumps-1;
			bGoodFit = false;
		} 
		else  //our pond needs are somewhere within range of pumps
		{

			for(int i = 0; i < numPumps-1; ++i)
			{
				if( twiceCap > pumps.at(i) && twiceCap < pumps.at(i+1) )
				{
					//found our range
					neededPumpIndex = i+1;

					break;   //can now break out of for loop
				}
			}
		}

		if(bGoodFit == true)
		{
			cout << "\nYour pond needs the " 
				<< pumps.at(neededPumpIndex) << " pump" << endl;
		}
		else
		{
			cout << "\nThe " << pumps.at(neededPumpIndex) 
				<< " pump is the only one that we have for your pond. "
				<< "\nThere may be a better pump for you. " << endl;
		}
			
		cout << "\nFigure another pond pump?  yes/no  ";

		getline(cin, answer);

	}while(answer == "yes");

	return 0;
}