//DISPLAY 5.3 Use of return in a void  Function
//Function Declaration
void iceCreamDivision(int number, double totalWeight);
//Outputs instructions for dividing totalWeight ounces of
//ice cream among number customers.
//If number is 0, nothing is done.
//Function Definition
//Definition uses iostream:
void iceCreamDivision(int number, double totalWeight)
{
    using namespace std;
    double portion;

    if (number == 0)
        return;
    portion = totalWeight/number;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Each one receives "
         << portion << " ounces of ice cream." << endl;
}
