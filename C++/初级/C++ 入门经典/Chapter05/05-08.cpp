//DISPLAY 5.8 Function Calling Another Function
//Program to demonstrate a function calling another function.
#include <iostream>

void getInput(int& input1, int& input2);
//Reads two integers from the keyboard.

void swapValues(int& variable1, int& variable2);
//Interchanges the values of variable1 and variable2.

void order(int& n1, int& n2);
//Orders the numbers in the variables n1 and n2
//so that after the function call n1 <= n2.

void giveResults(int output1, int output2);
//Outputs the values in output1 and output2.
//Assumes that output1 <= output2


int main( )
{
    int firstNum, secondNum;

    getInput(firstNum, secondNum);
    order(firstNum, secondNum);
    giveResults(firstNum, secondNum);
    return 0;
}


//Uses iostream:
void getInput(int& input1, int& input2)
{
    using namespace std;
    cout << "Enter two integers: ";
    cin >> input1 >> input2;
}

void swapValues(int& variable1, int& variable2)
{
    int temp;

    temp = variable1;
    variable1 = variable2;
    variable2 = temp;
}

void order(int& n1, int& n2)
{
    if (n1 > n2)
        swapValues(n1, n2);
}

//Uses iostream:
void giveResults(int output1, int output2)
{
    using namespace std;
    cout << "In increasing order the numbers are: "
         << output1 << " " << output2 << endl;
}

