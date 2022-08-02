//This program asks the user to enter the
//amount of the item purchased.
//The function has a static variable, which 
//maintains (remembers) the amount entered.

#include <iostream>
#include <string>

using namespace std;

//function declaration
float HowMuchHaveYouSpent();  

int main()
{
	float total;
	string answer = "yes";

	cout.precision(2);
	cout.setf(ios::fixed);

	while(answer == "yes")
	{
		total = HowMuchHaveYouSpent();

		cout << "You've spent $ " << total << " so far today. ";
		
		cout << "\nKeep shopping?  yes/no  ";
		getline(cin,answer);
	}

	cout << "\nYour shopping trip today cost you $ " << total << endl;
	return 0;
}

float HowMuchHaveYouSpent()
{
	//total is set to zero 1st time in here 
	static float total = static_cast<float>(0.0); 

	float amount; 
	cout << "\nHow much was this recent purchase?  $ " ;
	cin >> amount;
	cin.ignore();

	//keep a running totof of the purchases
	total = total + amount;
	return total;
}
