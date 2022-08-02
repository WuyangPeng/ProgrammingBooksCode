//DISPLAY 4.15 Using Namespaces
//Computes the area of a circle and the volume of a sphere.
//Uses the same radius for both calculations.
#include <iostream>
#include <cmath>

const double PI = 3.14159;

double area(double radius);
//Returns the area of a circle with the specified radius.

double volume(double radius);
//Returns the volume of a sphere with the specified radius.

int main( )
{
    using namespace std;

    double radiusOfBoth, areaOfCircle, volumeOfSphere;

    cout << "Enter a radius to use for both a circle\n"
            << "and a sphere (in inches): ";
    cin >> radiusOfBoth;

    areaOfCircle = area(radiusOfBoth);
    volumeOfSphere = volume(radiusOfBoth);

    cout << "Radius = " << radiusOfBoth << " inches\n"
            << "Area of circle = " << areaOfCircle
            << " square inches\n"
            << "Volume of sphere = " << volumeOfSphere
            << " cubic inches\n";

    return 0;
}


double area(double radius)
{
    using namespace std;

    return (PI * pow(radius, 2));
}

double volume(double radius)
{
    using namespace std;

    return ((4.0/3.0) * PI * pow(radius, 3));
}

