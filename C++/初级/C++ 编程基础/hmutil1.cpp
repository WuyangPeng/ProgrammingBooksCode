// hmutil1.cc

#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio>
#include <string>

#include "Vec.h"
#include "xstring.h"

#include "windos\keys.h"
#include "windos\windos.h"
#include "hmutil1.h"
using namespace std;

bool HomeUtility::CheckNumericInput(istream& is)
{
  int NextChar = is.peek();
  if (NextChar == '\n' || NextChar == ' ')
   IgnoreTillCR(is);
  else
    {
    xstring garbage;
    is.clear();
    is >> garbage;
    xstring Message = "Illegal data in numeric value: ";
    Message = Message + garbage;
    HandleError(Message);
    return false;
    }
    
  return true;
}

bool HomeUtility::ReadDoubleFromLine(istream& is, double& Result)
{
  double temp;
  xstring garbage;

  is >> Result;
 
  return CheckNumericInput(is);
}

bool HomeUtility::ReadLongFromLine(istream& is, long& Result)
{
  long temp;
  xstring garbage;

  is >> Result;
  
  return CheckNumericInput(is);
}


void HomeUtility::IgnoreTillCR(istream& is)
{
   is.ignore(numeric_limits<streamsize>::max(),'\n');
}

void HomeUtility::HandleError(const xstring& Message)
{
  cout << endl;
  cout << Message << endl;
  cin.clear();
  IgnoreTillCR();
  cout << "Please hit ENTER to continue." << endl;
  cin.get();
}

bool HomeUtility::ReadDateFromLine(istream& is, long& Date)
{
  bool result = ReadLongFromLine(is, Date);

  if (result == false)
    return false;

  if ((Date < 18000101) && (Date != 0))
    {
    xstring Message = "Date must be either 0 (if unknown)";
    Message = Message + " or a number in the form YYYYMMDD";
    Message = Message + "\n";
    Message = Message + "which is on or after 18000101";
    Message = Message + " (January 1st, 1800)";
    HandleError(Message);
    result = false;
    }

  return result;
}

short HomeUtility::GetNumberOrEnter(bool AllowArrows)
{
  int key;
  char keychar;
  short FoundItemNumber;

  cout.flush();

  for (;;)
    {
    key = windos::getkey();
    keychar = key;

    if (key == K_Return)
      return e_Return;

    if (AllowArrows)
      {
      if (key == K_Up)
        return e_Up;
      if (key == K_Down)
        return e_Down;
      }

    if ((key < '0') || (key > '9'))
      continue;

    cout << keychar;
    cout.flush();

    FoundItemNumber = key - '0';

    for (;;)
      {
      key = windos::getkey();
      keychar = key;

      if (key == K_BackSpace)
        {
        cout << keychar;
        cout.flush();
        cout << ' ';
        cout << keychar;
        cout.flush();
        FoundItemNumber /= 10;
        continue;
        }

      if (key == K_Return)
        {
        cout << keychar;
        cout.flush();
        return FoundItemNumber;
        }

      if ((key < '0') || (key > '9'))
        continue;

      cout << keychar;
      cout.flush();

      FoundItemNumber = FoundItemNumber * 10 + (key - '0');
      }
  }
}

void HomeUtility::ClearRestOfScreen(short StartingRow)
{
  short i;
  
  short HighestRowNumber = windos::ScreenRows();

  for (i = StartingRow; i <= HighestRowNumber; i ++)
    {
    gotoxy(1,i);
    clreol();
    }

  gotoxy(1,StartingRow);
}

short HomeUtility::SelectItem(const Vec<short>& Number,
  const Vec<xstring>& Name)
{
short FoundItemNumber;
int Row;
int Column;
int RowCount = windos::ScreenRows();
short ItemCount = Name.size();

windos::ScreenGetCursor(Row,Column);
Row ++;

// Max number of rows in scroll area is 1/2 available rows on screen

int RowsAvail = RowCount / 2;

if (RowsAvail > ItemCount)
  RowsAvail = ItemCount;

if (RowsAvail == 0)
  {
  HandleError("No items found.");
  return 0;
  }

short offset = 0;
for (;;)
  {
  ClearRestOfScreen(Row);

  for (short i = offset; i < offset + RowsAvail ; i++)
    cout << setw(5) << Number[i] + 1 << ".  " << Name[i] << endl;

  cout << endl;

  cout << "Type item number to select or ENTER to end." << endl;

  if (ItemCount > RowsAvail)
    cout << "Hit down arrow or up arrow to scroll." << endl;

  cout << endl;

  FoundItemNumber = GetNumberOrEnter(true);
  if (FoundItemNumber == e_Return)
    return 0;

  if (FoundItemNumber == e_Up)
    {
    if (ItemCount > RowsAvail)
      {
      offset --;
      if (offset < 0)
        offset = 0;
      }
    continue;
    }

  if (FoundItemNumber == e_Down)
    {
    if (ItemCount > RowsAvail)
      {
      offset ++;
      if (offset >= (int)(Name.size()-RowsAvail))
        offset = Name.size()-RowsAvail;
      }
    continue;
    }

  for (short i = 0; i < ItemCount; i ++)
    {
    if (FoundItemNumber == Number[i]+1)
      return FoundItemNumber;
    }

  IgnoreTillCR();
  cout << FoundItemNumber <<
    " is an invalid entry. Hit ENTER to continue." << endl;
  IgnoreTillCR();
  return 0;
  }
}    

