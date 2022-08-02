//DISPLAY 4.5 Incorrectly Ordered Arguments
//Determines user's grade. Grades are Pass or Fail.
#include <iostream>
using namespace std;

char grade(int receivedPar, int minScorePar);
//Returns 'P' for passing, if receivedPar is
//minScorePar or higher. Otherwise returns 'F' for failing.

int main( )
{
    int score, needToPass;
    char letterGrade;

    cout << "Enter your score"
         << " and the minimum needed to pass:\n";
    cin >> score >> needToPass;

    letterGrade = grade(needToPass, score);

    cout << "You received a score of " << score << endl
         << "Minimum to pass is " << needToPass << endl;

    if (letterGrade == 'P')
        cout << "You Passed. Congratulations!\n";
    else
        cout << "Sorry. You failed.\n";

    cout << letterGrade
         << " will be entered in your record.\n";

    return 0;
}

char grade(int receivedPar, int minScorePar)
{
    if (receivedPar >= minScorePar)
        return 'P';
    else
        return 'F';
}

