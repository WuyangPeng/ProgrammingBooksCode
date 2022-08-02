#include <iostream.h>
#include <stdio.h>

#include "mrListGP.h"


void AddLife( mrListGP& list, mrInt life )
{
    for( list.StartIterator(); list.IsIteratorValid(); list.MoveForward() )
        list.GetCurrentItem().m_iLife += life;
}


void printlist( mrListGP& list )
{
    cout << "The list contains:" << endl;
    for( list.StartIterator(); list.IsIteratorValid(); list.MoveForward() )
    {
        cout << "\tLife:\t" << list.GetCurrentItem().m_iLife;
        cout << "\tLevel:\t" << list.GetCurrentItem().m_iLevel << endl;
    }
}


void main()
{
    mrListGP playerList;
    mrBool32 done = mrFalse;
    mrInt choice;
    mrGamePlayer player;
    mrInt life;
    

    while( !done )
    {
        cout << "=================================" << endl;
        cout << " 1 - insert gameplayer" << endl;
        cout << " 2 - remove current gameplayer" << endl;
        cout << " 3 - append gameplayer" << endl;
        cout << " 4 - view current game player" << endl;
        cout << " 5 - move iterator to start" << endl;
        cout << " 6 - move iterator forward" << endl;
        cout << " 7 - is iterator valid?" << endl;
        cout << " 8 - print list" << endl;
        cout << " 9 - add life to every player" << endl;
        cout << "=================================" << endl;
        cout << " Make a choice (0 to quit): ";
        cin >> choice;
        if( choice == 0 )
            break;
        switch( choice )
        {
        case 1:
            cout << "New Players' Life: ";
            cin >> player.m_iLife;
            cout << "New Players' Level: ";
            cin >> player.m_iLevel;
            playerList.InsertItem( player );
            cout << "New Player inserted into list." << endl;
            break;
        case 2:
            if( playerList.IsIteratorValid() )
            {
                playerList.RemoveCurrentItem();
                cout << "current player removed from list." << endl;
            }
            else
            {
                cout << "There is no current player, cannot remove!!" << endl;
            }
            break;
        case 3:
            cout << "New Players' Life: ";
            cin >> player.m_iLife;
            cout << "New Players' Level: ";
            cin >> player.m_iLevel;
            playerList.AppendItem( player );
            cout << "New Player appended to list." << endl;
            break;
        case 4:
            if( playerList.IsIteratorValid() )
            {
                player = playerList.GetCurrentItem();
                cout << "current player is:" << endl;
                cout << "\tLife:\t" << player.m_iLife << endl;
                cout << "\tLevel:\t" << player.m_iLevel << endl;
            }
            else
            {
                cout << "There is no current player, cannot view!!" << endl;
            }
            break;
        case 5:
            playerList.StartIterator();
            cout << "Iterator now points to start of list." << endl;
            break;
        case 6:
            playerList.MoveForward();
            cout << "Iterator moved forward." << endl;
            break;
        case 7:
            if( playerList.IsIteratorValid() )
            {
                cout << "Yes, it is valid." << endl;
            }
            else
            {
                cout << "No, it is not valid." << endl;
            }
            break;
        case 8:
            printlist( playerList );
            break;

        case 9:
            cout << "How much life to add: ";
            cin >> life;
            AddLife( playerList, life );
            cout << "Life Added!" << endl;
            break;
        }
        cout << endl;
        cout << "Press any key to continue..." << endl;
        getchar();
    }
}