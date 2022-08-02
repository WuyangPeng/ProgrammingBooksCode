#include "mrBSTInt.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    mrBSTInt BST;
    mrInt number;
    mrInt temp;
    mrInt choice;
    mrBool32 done = mrFalse;

    while( !done )
    {
        cout << "===================================" << endl;
        cout << " 1 - insert number" << endl;
        cout << " 2 - find number" << endl;
        cout << " 3 - remove number" << endl;
        cout << " 4 - insert lots of random numbers" << endl;
        cout << "===================================" << endl;
        cout << " Make a choice (0 to quit): ";
        cin >> choice;
        if( choice == 0 )
            break;
        switch( choice )
        {
        case 1:
            cout << "what number: ";
            cin >> number;
            BST.Insert( number );
            cout << number << " inserted!" << endl;
            break;
        case 2:
            cout << "what number: ";
            cin >> number;
            if( BST.Search( number ) )
            {
                cout << "The BST contains " << number << endl;
            }
            else
            {
                cout << "The BST DOES NOT contain " << number << endl;
            }
            break;
        case 3:
            cout << "what number: ";
            cin >> number;
            BST.Remove( number );
            break;
        case 4:
            cout << "how many numbers to insert: ";
            cin >> number;
            while( number > 0 )
            {
                temp = rand() % 256;
                cout << "Inserting " << temp << ", ";
                BST.Insert( temp );
                number--;
            }
            break;

        }
        cout << endl;
        cout << "Press any key to continue..." << endl;
        getchar();
    }


}