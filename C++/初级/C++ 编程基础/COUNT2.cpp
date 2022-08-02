#include <iostream>
using namespace std;

short counter()
{
    short count;
 
    count ++;
 
    cout << count << " ";

    return 0;
}
 
int main()
{
    short i;
 
    for (i = 0; i < 10; i ++)
        counter();

    return 0;
}