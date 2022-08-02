//This program determines the depth of water in inches
//for an elliptical bathtub, given the desired gallons.
//Area of an ellipse is PI*A*B where A/B are the major/minor axes.

#include <iostream>
using namespace std;

//prototypes
void AskEllipTubDim(float &rMajorAxis, float &rMinorAxis);
float AskTotalGallons();
float CalculateInches(float MajorAxis, float MinorAxis, 
					  float gallons);

int main()
{
	cout << "Welcome to the C++ Elliptical Tub Water "
		<< "Use Program.";
	cout << "\nWe'll determine how many inches you"
		<< " can fill your tub "
		<< "\ngiven the desired max-gallon use.";

	float majorAxis, minorAxis, gallons, inches;

	AskEllipTubDim(majorAxis, minorAxis);
	gallons = AskTotalGallons();
	inches = CalculateInches(majorAxis, minorAxis, gallons);

	cout << "\nFill your tub " << inches << " inches to use " 
			<< gallons << " gallons of water. " << endl;

	return 0;
}

void AskEllipTubDim(float &rMajorAxis, float &rMinorAxis)
{
	float length, width;
	
	cout << "\nEnter elliptical tub dimensions:"
			<< "\nTub length? (in inches)  ";
	cin >> length;
	
	cout << "Tub width? (in inches)  ";
	cin >> width;
	cin.ignore();

	rMajorAxis = length/2.0;
	rMinorAxis = width/2.0;
}

float AskTotalGallons()
{
	float gallons;

	cout << "Gallon-usage limit for this"
		<< " bathing experience?  ";
	cin >> gallons;
	cin.ignore();

	return gallons;
}

float CalculateInches(float MajorAxis, float MinorAxis, 
					  float gallons)
{
	float PI = static_cast<float>(3.14159265);

	//First calculate the area of the elliptical tub
	float area = PI * MajorAxis * MinorAxis;

	//Next determine how many gallons 1 inch contains
	//231 cubic inches = 1 gallon of water
	float gallonsPerInch = area/231.0;

	float inches = gallons/gallonsPerInch;

	return inches;
}

