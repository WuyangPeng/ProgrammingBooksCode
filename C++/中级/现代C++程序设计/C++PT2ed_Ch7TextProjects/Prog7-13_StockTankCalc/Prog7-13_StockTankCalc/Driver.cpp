//StockTankDriver.cpp
#include <iostream>
#include <string>
#include "StockTankCalc.h"

using namespace std;

int Menu();

int main()
{
	cout <<"The Stock Tank Calculator Program";

	int choice, chooseShape;
	int ht, diam, len, width;
	int per;

	double gallons;

	STCalc Tank;

	do
	{
		choice = Menu();

		switch (choice)
		{
		case 1:		//chocse shape of tank
			cout <<"Select stock tank shape\n";
			cout <<"(1) Circular (2) Rectangular "
					<<"(3) Oval  ";
			cin >>chooseShape;
			
			if(chooseShape == 1)
			{
				Tank.setShape("Circular");
				cout <<"\nEnter diameter height:  ";
				cin >> diam >> ht;
				Tank.setCircTankDims(diam, ht);	
				
			}
			else if(chooseShape == 2)
			{
				Tank.setShape("Rectangular");
				cout <<"\nEnter width height length:  ";
				cin >> width >> ht >> len;
				Tank.setRectTankDims(width, ht, len);
			}
			else if(chooseShape == 3)
			{
				Tank.setShape("Oval");
				cout <<"\nEnter width height length:  ";
				cin >>width >> ht >> len;
			    Tank.setOvalTankDims(ht, width, len);
			}
			else
			{
				cout <<"\nWhoops! Not a choice. \n";

			}
			break;

		case 2:		//show tank data
			Tank.WriteTankData();
			break;
		
		case 3:		//percentage of tank
			cout << "\nEnter a percentage:  ";
			cin >> per;
			gallons = Tank.getPercent(per);
			cout << "When the tank is " << per
				<< "% full, it will hold "
				<< gallons << " gallons.";
		}

	}while(choice != 4);

	return 0;
}

int Menu()
{
	int choice;
		
	cout <<"\n\nStock Tank Calculator Menu\n";
	cout << "(1) Set Tank Shape  (3) Get % of capacity\n"
		 << "(2) See Tank Info   (4) Exit\n\n";

	cin >>choice;
	cin.ignore();
	return choice;
}