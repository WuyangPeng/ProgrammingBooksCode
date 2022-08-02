//DISPLAY 16.3 Defining Your Own Exception Class
#include <iostream>
using namespace std;

class NoMilk
{
public:
    NoMilk();
    NoMilk(int howMany);
    int getDonuts();
private:
    int count;
};

int main()
{
    int donuts, milk;
    double dpg;

    try
    {
        cout << "Enter number of donuts:\n";
        cin >> donuts;
        cout << "Enter number of glasses of milk:\n";
        cin >> milk;

        if (milk <= 0)
               throw NoMilk(donuts);

        dpg = donuts/static_cast<double>(milk);
        cout << donuts << " donuts.\n"
             << milk << " glasses of milk.\n"
             << "You have " << dpg
             << " donuts for each glass of milk.\n";
    }
    catch(NoMilk e)
    {
        cout << e.getDonuts() << " donuts, and No Milk!\n"
             << "Go buy some milk.\n";
    }
    cout << "End of program.";
    return 0;
}

NoMilk::NoMilk()
{}

NoMilk::NoMilk(int howMany) : count(howMany)
{}

int NoMilk::getDonuts()
{
    return count;
}



    return 0;
}

