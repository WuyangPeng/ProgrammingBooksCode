#include <iostream>
#include "Vec.h"
using namespace std;

int main()
{
    Vec<short> Weight(5);
    Vec<short> SortedWeight(3);
    short HighestWeight;
    short HighestIndex;
    short i;
    short k;

    cout << "I'm going to ask you to type in five weights, in pounds." << endl;

    for (i = 0; i < 5; i ++)
      {
      cout << "Please type in weight #" << i+1 << ": ";
      cin >> Weight[i];
      if (Weight[i] <= 0)
        {
        cout << "I'm sorry, " << Weight[i] << " is not a valid weight.";
        cout << endl;
        }
      }

    for (i = 0; i < 3; i ++)
        {
        HighestWeight = 0;
        HighestIndex = 0;
        for (k = 0; k < 5; k ++)
            {
            if (Weight[k] > HighestWeight)
                {
                HighestWeight = Weight[k];
                HighestIndex = k;
                }
            }
        SortedWeight[i] = HighestWeight;
        Weight[HighestIndex] = 0;
        }

    cout << "The highest weight was: " << SortedWeight[0] << endl;
    cout << "The second highest weight was: " << SortedWeight[1] << endl;
    cout << "The third highest weight was: " << SortedWeight[2] << endl;

    return 0;
}
