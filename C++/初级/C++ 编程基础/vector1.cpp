#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<short> Weight(5);
    vector<short> SortedWeight(3);
    short HighestWeight;
    short HighestIndex = -10000;
    short i;
    short k;

    cout << "I?m going to ask you to type in five weights, in pounds." << endl;

    for (i = 0; i < 5; i ++)
      {
      cout << "Please type in weight #" << i+1 << ": ";
      cin >> Weight[i];
      }

    for (i = 0; i < 3; i ++)
        {
        HighestWeight = 0;
        for (k = 0; k < 5; k ++)
            {
            if (Weight[k] > HighestWeight)
                {
                HighestWeight = Weight[k];
                HighestIndex = k;
                }
            }
cout << "HighestIndex: " << HighestIndex << endl;
        SortedWeight[i] = HighestWeight;
        Weight[HighestIndex] = 0;
        }

    cout << "The highest weight was: " << SortedWeight[0] << endl;
    cout << "The second highest weight was: " << SortedWeight[1] << endl;
    cout << "The third highest weight was: " << SortedWeight[2] << endl;

    return 0;
}
