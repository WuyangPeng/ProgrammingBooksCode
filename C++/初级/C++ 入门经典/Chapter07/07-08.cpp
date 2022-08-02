//DISPLAY 7.8 Production Graph Program
//Reads data and displays a bar graph showing productivity for each plant.
#include <iostream>
#include <cmath>
const int NUMBER_OF_PLANTS = 4;

void inputData(int a[], int lastPlantNumber);
//Precondition: lastPlantNumber is the declared size of the array a.
//Postcondition: For plant_number = 1 through lastPlantNumber:
//a[plant_number-1] equals the total production for plant number plant_number.

void scale(int a[], int size);
//Precondition: a[0] through a[size-1] each has a nonnegative value.
//Postcondition: a[i] has been changed to the number of 1000s (roundNumed to
//an integer) that were originally in a[i], for all i such that 0 <= i <= size -1.
void graph(const int asteriskCount[], int lastPlantNumber);
//Precondition: asteriskCount[0] through asteriskCount[lastPlantNumber-1]
//have nonnegative values.
//Postcondition: A bar graph has been displayed saying that plant
//number N has produced asteriskCount[N-1] 1000s of units, for each N such that
//1 <= N <= lastPlantNumber

void getTotal(int& sum);
//Reads nonnegative integers from the keyboard and
//places their total in sum.

int roundNum(double number);
//Precondition: number >= 0.
//Returns number rounded to the nearest integer.

void printAsterisks(int n);
//Prints n asterisks to the screen.

int main( )
{
    using namespace std;
    int production[NUMBER_OF_PLANTS];

    cout << "This program displays a graph showing\n"
         << "production for each plant in the company.\n";

    inputData(production, NUMBER_OF_PLANTS);
    scale(production, NUMBER_OF_PLANTS);
    graph(production, NUMBER_OF_PLANTS);
    return 0;
}

//Uses iostream:
void inputData(int a[], int lastPlantNumber)
//The rest of the definition of inputData is given in Display 7.6.

//Uses iostream:
void getTotal(int& sum)
//The rest of the definition of getTotal is given in Display 7.6.

void scale(int a[], int size)
//The rest of the definition of scale is given in Display 7.7.

//Uses cmath:
int roundNum(double number)
//The rest of the definition of roundNum is given in Display 7.7.
//Uses iostream:
void graph(const int asteriskCount[], int lastPlantNumber)
{
    using namespace std;
    cout << "\nUnits produced in thousands of units:\n";
    for (int plant_number = 1;
                plant_number <= lastPlantNumber; plant_number++)
    {
        cout << "Plant #" << plant_number << " ";
        printAsterisks(asteriskCount[plant_number - 1]);
        cout << endl;
    }
}

//Uses iostream:
void printAsterisks(int n)
{
    using namespace std;
    for (int count = 1; count <= n; count++)
        cout << "*";
}

