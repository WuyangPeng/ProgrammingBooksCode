/*
 * This file contains code from "C++ Primer, Fourth Edition", by Stanley B.
 * Lippman, Jose Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
 * "Copyright (c) 2005 by Objectwrite, Inc., Jose Lajoie, and Barbara E. Moo."
 * 
 * 
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 * 
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address: 
 * 
 * 	Pearson Education, Inc.
 * 	Rights and Contracts Department
 * 	75 Arlington Street, Suite 300
 * 	Boston, MA 02216
 * 	Fax: (617) 848-7047
*/ 

#include <iostream>
using std::cout; using std::endl;
#include "newQueue.h"

int main()
{
    // the class Queue<int> is instantiated
    // new expression requires that Queue<int> be defined
    Queue<int> *p_qi = new Queue<int>;

    int ival;
    for (ival = 0; ival != 10; ++ival)
        // the member function push() is instantiated
        p_qi->push(ival);

    int err_cnt = 0;
    for (ival = 0; ival != 10; ++ival) {
        // the member function front is instantiated
        int qval = p_qi->front();

        if (ival != qval) err_cnt++;
        p_qi->pop();                // instantiates pop
    }

    if (!err_cnt)
        cout << "!! queue executed ok" << endl;
    else 
        cout << "?? " << err_cnt << " Queue errors" << endl;

    delete p_qi;   // deletes elements in the queue

    return 0;
}
