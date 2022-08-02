#include <iostream>
using namespace std;

int main( )
{
    int numberOfPods, peasPerPod, totalPeas;

    cout << "Press return after entering a number.\n";
    cout << "Enter the number of pods:\n";
    cin >> numberOfPods;
    cout << "Enter the number of peas in a pod:\n";
    cin >> peasPerPod;

    totalPeas = numberOfPods * peasPerPod;

    cout << "If you have ";
    cout << numberOfPods;
    cout << " pea pods\n";
    cout << "and ";
    cout << peasPerPod;
    cout << " peas in each pod, then\n";
    cout << "you have ";
    cout << totalPeas;
    cout << " peas in all the pods.\n";

    return 0;
}
