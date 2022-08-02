#include <iostream>
#include <fstream>
#include <string>

#include "Vec.h"
#include "xstring.h"

#include "windos\keys.h"
#include "windos\windos.h"
#include "hmit8.h"
#include "hmin8.h"
#include "hmutil1.h"
using namespace std;

enum MenuItem {AddItem=1, SelectItemFromNameList,
  EditByPartialName, EditByDescription, EditByCategory,
  DeleteItemFromNameList, PrintNames, PrintAll, Exit
};

char GetMenuChoice(HomeInventory& Inventory)
{
  short MenuRow;
  short option;

  for (;;)
    {
    windos::clrscr();

    cout << Inventory.GetCount() << " items in database." << endl;

    cout << endl;

    cout << AddItem << ". Add item" << endl;

    cout << SelectItemFromNameList <<
      ". Select item name from list" << endl;

    cout << EditByPartialName <<
      ". Edit item by partial name" << endl;

    cout << EditByDescription <<
      ". Edit item by description" << endl;

    cout << EditByCategory <<
      ". Edit item by category" << endl;

    cout << DeleteItemFromNameList <<
      ". Delete item" << endl;

    cout << PrintNames <<
      ". Print item names" << endl;

    cout << PrintAll << ". Print data base" << endl;

    cout << Exit << ". Exit" << endl;

    cout << endl;

    cout << "Please enter a number from " <<
      AddItem << " to " << Exit << ": ";

    cin >> option;

    if ((option >= AddItem) && (option <= Exit))
      break;
    else
      HomeUtility::HandleError("Sorry, that's an invalid option.");
    }

  windos::clrscr();

  return option;
}

void ExecuteMenuChoice(char option, HomeInventory& Inventory)
{
  short itemno;
  ofstream Printer("lpt1");
  string Name;
  string Description;
  string Category;

  switch (option)
    {
    case AddItem:
      {
      cout << "Adding item" << endl << endl;
      Inventory.AddItem();
      ofstream SaveHomeInfo("home.$$$");
      Inventory.StoreInventory(SaveHomeInfo);
      }
    break;

    case SelectItemFromNameList:
      cout << "Selecting item from whole inventory";
      cout << endl << endl;
      HomeUtility::IgnoreTillCR();
      itemno = Inventory.SelectItemFromNameList();
      if (itemno != -1)
        {
        Inventory.EditItem(itemno);
        ofstream SaveHomeInfo("home.$$$");
        Inventory.StoreInventory(SaveHomeInfo);
        }
    break;

    case EditByPartialName:
      cout << "Selecting item by partial name";
      cout << endl << endl;
      cout << "Please enter part of the name of the item\n";
      cout << "(or ENTER for all items): ";
      HomeUtility::IgnoreTillCR();
      getline(cin,Name);
      cout << endl;
      itemno = Inventory.SelectItemByPartialName(Name);
      if (itemno != -1)
        {
        Inventory.EditItem(itemno);
        ofstream SaveHomeInfo("home.$$$");
        Inventory.StoreInventory(SaveHomeInfo);
        }
    break;

    case EditByDescription:
      cout << "Selecting item by partial description";
      cout << endl << endl;
      cout << "Please enter part of the description of the item\n";
      cout << "(or ENTER for all items): ";
      HomeUtility::IgnoreTillCR();
      getline(cin,Description);
      cout << endl;

      itemno = 
        Inventory.SelectItemFromDescriptionList(Description);

      if (itemno != -1)
        {
        Inventory.EditItem(itemno);
        ofstream SaveHomeInfo("home.$$$");
        Inventory.StoreInventory(SaveHomeInfo);
        }
    break;

    case EditByCategory:
      cout << "Selecting item by partial category";
      cout << endl << endl;
      cout << "Please enter part or all of the category name\n";
      cout << "(or ENTER for all categories): ";
      HomeUtility::IgnoreTillCR();
      getline(cin,Category);
      cout << endl;

      itemno = 
        Inventory.SelectItemFromCategoryList(Category);

      if (itemno != -1)
        {
        Inventory.EditItem(itemno);
        ofstream SaveHomeInfo("home.$$$");
        Inventory.StoreInventory(SaveHomeInfo);
        }
    break;

    case DeleteItemFromNameList:
      cout << "Deleting item" << endl << endl;
      itemno = Inventory.SelectItemFromNameList();
      if (itemno != -1)
        {
        string Query;
        cout << "Are you sure you want to delete item ";
        cout << itemno + 1 << " (Y/N)? ";
        cin >> Query;
        if (toupper(Query[0]) == 'Y')
          {
          Inventory.DeleteItem(itemno);
          ofstream SaveHomeInfo("home.$$$");
          Inventory.StoreInventory(SaveHomeInfo);
          }
        }
    break;

    case PrintNames:
      Inventory.PrintNames(Printer);
    break;

    case PrintAll:
      Inventory.PrintAll(Printer);
    break;
    }
}


int main()
{
  ifstream HomeInfo("home.inv");
  HomeInventory MyInventory;
  char option;
  string answer;

  MyInventory.LoadInventory(HomeInfo);

  for (;;)
    {
    option = GetMenuChoice(MyInventory);

    if (option == Exit)
      break;
    else
      ExecuteMenuChoice(option,MyInventory);
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
        windos::clrscr();
      }

    return 0;
}
