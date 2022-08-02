//Time Conversion Demonstration

#include <iostream>
using namespace std;

int main()
{
	int choice,hr, min, sec, totalsec;
	char colon;

	cout << "A program that converts between H:M:S and seconds. ";

	do
	{	
		cout << "\n\n1 = Convert H:M:S to seconds" 
				<< "\n2 = Convert seconds to H:M:S"
				<< "\n3 = Exit"
				<< "\nPlease pick your choice ==> ";
		cin >>choice;
	
		switch(choice)
		{
			case 1:		//convert H:M:S to seconds

				cout << "\nEnter H:M:S format, i.e. 3:26:33 ==> ";
				cin >> hr >> colon >> min >> colon >> sec;
				totalsec = hr*3600 + min*60 + sec;
				cout << "Result: " << totalsec;
				break;

			case 2:		//convert seconds to H:M:S

				cout << "\nEnter seconds, i.e. 3440 ==> ";
				cin >> totalsec;
				hr = totalsec/3600;
				totalsec = totalsec - hr*3600;
				min = totalsec/60;
				totalsec = totalsec - min*60;
				sec = totalsec;
				cout << "Result: " << hr << ":" << min << ":" << sec;
				break;

			case 3:		//exiting program

				cout << "You have chosen to exit." << endl;
				break;

			default:
				cout << "\nOh I don't do that choice! Try again! ";
		}
	
	}while(choice != 3);

	return 0;
}

