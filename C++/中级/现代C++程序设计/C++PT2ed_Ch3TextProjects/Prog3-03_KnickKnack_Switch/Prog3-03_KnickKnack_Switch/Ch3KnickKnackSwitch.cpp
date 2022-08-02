// Knick-knack Example program with switch

#include <iostream>
using namespace std;

int main()
{
	int number;  
	cout << "Please enter an integer for knick-knacking  ";
	cin >> number;

	cout << "He played knick-knack ";
	switch(number)  //write out area that will be knick-knacked.
	{
		case 1:
			cout << "with his thumb.  \n";
			break;
		case 2:
			cout << "with my shoe.  \n";
			break;
		case 3:
			cout << "on his knee.  \n";
			break;
		case 4:
			cout << "at the door.  \n";
			break;
		default:
			cout << "\nwhoa! He doesn't play knick-knack there!  \n";
	}
	
	return 0;
}
