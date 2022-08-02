//DISPLAY 5.10 Driver Program
//Driver program for the function getInput.
#include <iostream>

void getInput(double& cost, int& turnover);
//Precondition: User is ready to enter values correctly.
//Postcondition: The value of cost has been set to the
//wholesale cost of one item. The value of turnover has been
//set to the expected number of days until the item is sold.

int main( )
{
    using namespace std;
    double wholesaleCost;
    int shelfTime;
    char ans;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    do
    {
        getInput(wholesaleCost, shelfTime);

        cout << "Wholesale cost is now $"
             << wholesaleCost << endl;
        cout << "Days until sold is now "
             << shelfTime << endl;

        cout << "Test again?"
             << " (Type y for yes or n for no): ";
        cin >> ans;
        cout << endl;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
//Uses iostream:
void getInput(double& cost, int& turnover)
{
    using namespace std;
    cout << "Enter the wholesale cost of item: $";
    cin >> cost;
    cout << "Enter the expected number of days until sold: ";
    cin >> turnover;
}
