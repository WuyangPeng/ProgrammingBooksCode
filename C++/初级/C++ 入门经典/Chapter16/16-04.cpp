//DISPLAY 16.4 Catching Multiple Exceptions
#include <iostream>
#include <string>
using namespace std;

class NegativeNumber
{
public:
    NegativeNumber();
    NegativeNumber(string takeMeToYourCatchBlock);
    string getMessage();
private:
    string message;
};

class DivideByZero
{};

int main()
{
    int jemHadar, klingons;
    double portion;


try
    {
        cout << "Enter number of Jem Hadar warriors:\n";
        cin >> jemHadar;
        if (jemHadar < 0)
             throw NegativeNumber("Jem Hadar");

        cout << "How many Klingon warriors do you have?\n";
        cin >> klingons;
        if (klingons < 0)
            throw NegativeNumber("Klingons");
        if (klingons != 0)
            portion = jemHadar/static_cast<double>(klingons);
        else
            throw DivideByZero();
        cout << "Each Klingon must fight "
             << portion << " Jem Hadar.\n";
    }
    catch(NegativeNumber e)
    {
       cout << "Cannot have a negative number of "
             << e.getMessage() << endl;
    }
    catch(DivideByZero)
    {
       cout << "Send for help.\n";
    }

    cout << "End of program.\n";
    return 0;
}


NegativeNumber::NegativeNumber()
{}

NegativeNumber::NegativeNumber(string takeMeToYourCatchBlock)
    : message(takeMeToYourCatchBlock)
 {}

string NegativeNumber::getMessage()
{
    return message;
}

