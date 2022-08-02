#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include "mrDatatypes.h"
#include "bubblesort.h"
#include "quicksort.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>



void main()
{
    mrInt* array = 0;
    mrBool32 done = mrFalse;
    mrInt choice;
    mrInt size = 0;
    int i;

    while( size <= 0 )
    {
        cout << "Enter the size of the data array you wish to sort: ";
        cin >> size;
    }

    array = new mrInt[size];
    
    while( !done )
    {
        cout << "====================================" << endl;
        cout << " 1 - fill array with random numbers" << endl;
        cout << " 2 - bubblesort array" << endl;
        cout << " 3 - quicksort array" << endl;
        cout << " 4 - view array" << endl;
        cout << "=================================" << endl;
        cout << " Make a choice (0 to quit): ";
        cin >> choice;
        if( choice == 0 )
            break;
        switch( choice )
        {
        case 1:
            cout << "Filling array..." << endl;
            for( i = 0; i < size; i++ )
                array[i] = rand();
            break;
        case 2:
            cout << "Bubble-sorting array..." << endl;
            BubbleSortInt( array, size );
            break;
        case 3:
            cout << "Quick-sorting array..." << endl;
            QuickSortInt( array, 0, size );
            break;
        case 4:
            cout << "The array contains: " << endl;
            for( i = 0; i < size; i++ )
            {
                cout << array[i] << ", ";
            }
        }
        cout << endl;
        cout << "Press any key to continue..." << endl;
        getchar();
    }
}