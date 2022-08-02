//DISPLAY 4.8 Simpler Formal Parameter Names
//Function Declaration
double total_cost(int number, double price);
//Computes the total cost, including 5% sales tax,
//on number items at a cost of price each.

//Function Definition
double total_cost(int number, double price)
{
    const double TAX_RATE = 0.05; //5% sales tax
    double subtotal;

    subtotal = price * number;
    return (subtotal + subtotal*TAX_RATE);
}
