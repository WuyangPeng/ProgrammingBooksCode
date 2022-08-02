//DISPLAY 11.7 << as an Operator
cout << "I have " << amount << " in my purse.\n";

means the same as

((cout << "I have ") << amount) << " in my purse.\n";

and is evaluated as follows:

First evaluate (cout << "I have "), which returns cout:
((cout << "I have ") << amount) << " in my purse.\n";



(cout << amount) << " in my purse.\n";


Then evaluate (cout << amount), which returns cout:

(cout << amount) << " in my purse.\n";



cout << " in my purse.\n";


Then evaluate cout << " in my purse.\n", which returns cout:

cout << " in my purse.\n";



cout;
