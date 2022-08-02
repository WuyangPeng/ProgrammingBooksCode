//DISPLAY 4.16 Factorial Function
//Function Declaration
int factorial(int n);
//Returns factorial of n.
//The argument n should be nonnegative.

//Function Definition
int factorial(int n)
{
    int product = 1;
    while (n > 0)
    {
        product = n * product;
        n--;
    }

    return product;
}
