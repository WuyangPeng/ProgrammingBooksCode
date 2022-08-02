//DISPLAY 5.4 Call-by-Reference Parameters
//Program to demonstrate call-by-reference parameters.
#include <iostream>

void getNumbers(int& input1, int& input2);
//Reads two integers from the keyboard.

void swapValues(int& variable1, int& variable2);
//Interchanges the values of variable1 and variable2.

void showResults(int output1, int output2);
//Shows the values of variable1 and variable2, in that order.

int main( )
{
    int firstNum, secondNum;

    getNumbers(firstNum, secondNum);
    swapValues(firstNum, secondNum);
    showResults(firstNum, secondNum);
    return 0;
}

//Uses iostream:
void getNumbers(int& input1, int& input2)
{
    using namespace std;
    cout << "Enter two integers: ";
    cin >> input1
        >> input2;
}
void swapValues(int& variable1, int& variable2)
{
    int temp;


    temp = variable1;
    variable1 = variable2;
    variable2 = temp;
}

//Uses iostream:
void showResults(int output1, int output2)
{
    using namespace std;
    cout << "In reverse order the numbers are: "
         << output1 << " " << output2 << endl;
}
