//DISPLAY 17.6 Implementation of GenericList
//This is the implementation file: genericlist.cpp
//This is the implementation of the class template named GenericList.
//The interface for the class template GenericList is in the
//header file genericlist.h.
#ifndef GENERICLIST_CPP
#define GENERICLIST_CPP
#include <iostream>
#include <cstdlib>
#include "genericlist.h" //This is not needed when used as we are using this file,
                 //but the #ifndef in genericlist.h makes it safe.
using namespace std;

namespace listsavitch
{
    //Uses cstdlib:
    template<class ItemType>
    GenericList<ItemType>::GenericList(int max) : maxLength(max),
                                                  currentLength(0)
    {
          item = new ItemType[max];
    }

    template<class ItemType>
    GenericList<ItemType>::~GenericList( )
    {
        delete [] item;
    }

    template<class ItemType>
    int GenericList<ItemType>::length( ) const
    {
        return (currentLength);
    }

    //Uses iostream and cstdlib:
    template<class ItemType>
    void GenericList<ItemType>::add(ItemType newItem)
    {
        if ( full( ) )
        {
            cout << "Error: adding to a full list.\n";
            exit(1);
        }
        else
        {
            item[currentLength] = newItem;
            currentLength = currentLength + 1;
        }
    }

    template<class ItemType>
    bool GenericList<ItemType>::full( ) const
    {
        return (currentLength == maxLength);
    }

    template<class ItemType>
    void GenericList<ItemType>::erase( )
    {
        currentLength = 0;
    }
}//listsavitch
#endif // GENERICLIST_CPP Notice that we have enclosed all the template
       // definitions in #ifndef... #endif.