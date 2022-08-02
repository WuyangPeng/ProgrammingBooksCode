//Hardware calculation program.
//PVC pipe for your garden.
//Declare variables, use operators, obtain user values

#include <iostream>     //for cout and cin
using namespace std;


int main ()             
{ 
	int nConnectors, nElbows, nPipes;  //variables
	double pipeLength;

	//Now ask the user to input his data.
	cout << "Welcome to the C++ PVC Plumbing Store";

	cout << "\n\nPlease enter the number of ... ";
	cout << "\npipe connectors?  ";
	cin >> nConnectors;
	
	cout << "elbows?  ";
	cin >> nElbows;
	
	cout << "Length of pipe in feet? "
		<< " (can be value such as 8.5)  ";
	cin >> pipeLength;
	
	cout << "How many " << pipeLength << " foot pipes?  ";
	cin >> nPipes; 

	//We want to calculate total length of pipe.
	double totalLength;
	totalLength = pipeLength * nPipes; 

	//Calculate total number of plumbing parts. 
	int totalParts = nConnectors + nElbows + nPipes;

	//Write totals to the screen
	cout << "Summary";
	cout << "\nNumber of Connectors: " << nConnectors;
	cout << "\nNumber of Elbows: " << nElbows;
	cout << "\nNumber of " << pipeLength << " foot pipes: " << nPipes;

	cout << "\nTotal Pipe Length (ft): " << totalLength;

	cout << "\nTotal Plumbing Parts: "  << totalParts << "\n" ;

	return 0;
}
