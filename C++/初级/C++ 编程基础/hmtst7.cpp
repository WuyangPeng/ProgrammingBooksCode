#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <dos.h>

#include "Vec.h"
#include "xstring.h"

#include "hmit7.h"
#include "hmin7.h"
using namespace std;

int main()
{
    ifstream HomeInfo("home.inv");
    ofstream Printer("lpt1");
    HomeInventory MyInventory;
    HomeItem TempItem;
    xstring Name;
    xstring Description;
    short itemno;
    enum function {DisplayNames=1, AddItem, EditByName,
      EditByPartialName, EditByDescription,
      PrintNames, PrintAll, Exit};
    short option = 0;
    xstring answer;
    xstring temp;

    MyInventory.LoadInventory(HomeInfo);

    for (;;)
      {
      for (;;)
        {
        if (option != DisplayNames)
          clrscr();

        cout << DisplayNames << ". Display names" << endl;

        cout << AddItem << ". Add item" << endl;

        cout << EditByName << ". Edit item by name" << endl;

        cout << EditByPartialName << 
          ". Edit item by partial name" << endl;

        cout << EditByDescription << 
          ". Edit item by description" << endl;

        cout << PrintNames << ". Print item names" << endl;

        cout << PrintAll << ". Print data base" << endl;

        cout << Exit << ". Exit" << endl;

        cout << endl;

        cout << "Please enter a number from " << DisplayNames
          << " to " << Exit << ": ";

        cin >> option;

        if ((option >= DisplayNames) && (option <= Exit))
          break;
        else
          {
          cout << "Sorry, that's an invalid option.";
          _sleep(2);
          clrscr();
          }
        }

        cout << endl;

        switch (option)
          {
          case DisplayNames:
            MyInventory.DisplayNames(cout);
          break;

          case AddItem:
            MyInventory.AddItem();
          break;

          case EditByName:
            cout << "Please type the name of the item to be located: ";
            cin >> Name;
            itemno = MyInventory.LocateItemByName(Name);

            if (itemno > 0)
              {
              cout << endl;
              MyInventory.EditItem(itemno);
              MyInventory.DisplayItem(itemno);
              cout << endl;
              cout << "Please hit ENTER to continue: ";
              getline(cin,temp);
              }
            else
              {
              cout << "Sorry, I can't find that item. ";
              cout << "Please try again." << endl;
              }
          break;

          case EditByPartialName:
            cout << "Please type part of the name ";
            cout << "of the item to be located: ";
            cin >> Name;
            itemno = MyInventory.LocateItemByPartialName(Name);

            if (itemno >= 0)
              {
              cout << endl;
              MyInventory.EditItem(itemno);
              MyInventory.DisplayItem(itemno);
              cout << endl;
              cout << "Please hit ENTER to continue: ";
              getline(cin,temp);
              }
            else
              {
              cout << "Sorry, I can't find that item. ";
              cout << "Please try again." << endl;
              }
          break;

          case EditByDescription:
            cout << "Please type part of the description ";
            cout << "of the item to be located: ";
            cin >> Name;
            itemno = MyInventory.LocateItemByDescription(Name);

            if (itemno > 0)
              {
              cout << endl;
              MyInventory.EditItem(itemno);
              MyInventory.DisplayItem(itemno);
              cout << endl;
              cout << "Please hit ENTER to continue: ";
              getline(cin,temp);
              }
            else
              {
              cout << "Sorry, I can't find that item. ";
              cout << "Please try again." << endl;
              }
          break;

          case PrintNames:
            MyInventory.PrintNames(Printer);
          break;

          case PrintAll:
            MyInventory.PrintAll(Printer);
          break;

          case Exit:
          break;
          }

      if (option == Exit)
        break;

      }

      HomeInfo.close();

      for (;;)
        {
        cout << "Save the changes you have made? (Y/N) ";
        cin >> answer;

        if ((answer == "Y") || (answer == "y"))
          {
          ofstream NewHomeInfo("home.inv");
          MyInventory.StoreInventory(NewHomeInfo);
          cout << "Inventory updated" << endl;
          break;
          }
        else if ((answer == "N") || (answer == "n"))
          {
          cout << "Changes cancelled" << endl;
          break;
          }
        else
          {
          clrscr();
          }
        }

      return 0;
}
