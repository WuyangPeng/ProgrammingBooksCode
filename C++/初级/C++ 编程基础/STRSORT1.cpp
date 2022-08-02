#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "string5.h"
#include "Vec.h"

int main()
{
    Vec<string> Name(5);
    Vec<string> SortedName(5);
    string LowestName;
    short FirstIndex;
    short i;
    short k;
    string HighestName = "zzzzzzzz";

    cout << "I'm going to ask you to type in five last names." << endl;

    for (i = 0; i < 5; i ++)
      {
      cout << "Please type in name #" << i+1 << ": ";
      cin >> Name[i];
      }

    for (i = 0; i < 5; i ++)
        {
        LowestName = HighestName;
        FirstIndex = 0;
        for (k = 0; k < 5; k ++)
            {
            if (Name[k] < LowestName)
                {
                LowestName = Name[k];
                FirstIndex = k;
                }
            }
        SortedName[i] = LowestName;
        Name[FirstIndex] = HighestName;
        }

    cout << "Here are the names, in alphabetical order: " << endl;
    for (i = 0; i < 5; i ++)
        cout << SortedName[i] << endl;

    return 0;
}
