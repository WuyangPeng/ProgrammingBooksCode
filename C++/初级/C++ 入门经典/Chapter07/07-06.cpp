//DISPLAY 7.6 Test of Function inputData
//Tests the function inputData.
#include <iostream>
const int NUMBER_OF_PLANTS = 4;

void inputData(int a[], int lastPlantNumber);
//Precondition: lastPlantNumber is the declared size of the array a.
//Postcondition: For plant_number = 1 through lastPlantNumber:
//a[plant_number-1] equals the total production for plant number plant_number.

void getTotal(int& sum);
//Reads nonnegative integers from the keyboard and
//places their total in sum.

int main( )
{
    using namespace std;
    int production[NUMBER_OF_PLANTS];
    char ans;

    do
    {
        inputData(production, NUMBER_OF_PLANTS);
        cout << endl
             << "Total production for each"
             << " of plants 1 through 4:\n";
        for (int number = 1; number <= NUMBER_OF_PLANTS; number++)
        cout << production[number - 1] << " ";

        cout << endl
             << "Test Again?(Type y or n and Return): ";
        cin >> ans;
    }while ( (ans != 'N') && (ans != 'n') );

    cout << endl;

    return 0;
}
//Uses iostream:
void inputData(int a[], int lastPlantNumber)
{
    using namespace std;
    for (int plant_number = 1;
                   plant_number <= lastPlantNumber; plant_number++)
    {
        cout << endl
             << "Enter production data for plant number "
             << plant_number << endl;
        getTotal(a[plant_number - 1]);
    }
}


//Uses iostream:
void getTotal(int& sum)
{
    using namespace std;
    cout << "Enter number of units produced by each department.\n"
         << "Append a negative number to the end of the list.\n";

    sum = 0;
    int next;
    cin >> next;
    while (next >= 0)
    {
        sum = sum + next;
        cin >> next;
    }

    cout << "Total = " << sum << endl;
}

