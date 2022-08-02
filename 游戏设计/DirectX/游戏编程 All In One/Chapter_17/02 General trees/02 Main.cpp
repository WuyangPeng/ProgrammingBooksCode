#include "mrGenTreeNodeInt.h"
#include <stdio.h>

// example given in section Trees->General Trees->Constructing a General Tree.
// page 16-17 in word2k file.

void main()
{

    mrGenTreeNodeInt root( 1 );
    mrGenTreeNodeInt* temp = 0;
    root.AppendChild( new mrGenTreeNodeInt( 2 ) );
    root.AppendChild( new mrGenTreeNodeInt( 3 ) );
    root.AppendChild( new mrGenTreeNodeInt( 4 ) );
    root.Start();
    temp = root.GetChild();
    temp->AppendChild( new mrGenTreeNodeInt( 5 ) );
    temp->AppendChild( new mrGenTreeNodeInt( 6 ) );
    temp->Start();
    temp->MoveForward();
    temp = temp->GetChild();
    temp->AppendChild( new mrGenTreeNodeInt( 9 ) );
    root.MoveForward();
    root.MoveForward();
    temp = root.GetChild();
    temp->AppendChild( new mrGenTreeNodeInt( 7 ) );
    temp->AppendChild( new mrGenTreeNodeInt( 8 ) );

    cout << "Preorder: " << endl;
    root.PreOrder();
    cout << endl << "Postorder: " << endl;
    root.PostOrder();
    cout << endl;
    cout << "Press any key to continue..." << endl;
    getchar();

};
