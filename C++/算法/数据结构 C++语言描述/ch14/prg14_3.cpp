// File: prg14_3.cpp
// program reads and writes account records to and from file
// accounts.dat"; initial write creates 5 records in file with
// account numbers 0 to 4. user is prompted to enter a series of
// account numbers, transactions (deposit 'D'/withdrawal 'W'), and
// amounts. corresponding account is read from file and updated
// based on transaction type. resulting data is then written back
// to the file. program concludes by displaying current account
// information after user enters account number -1

#include <iostream>
#include <fstream>

#include "d_acct.h"

using namespace std;

// output the records in a binary file of account objects
void outputAccounts(fstream& f);

int main()
{
	// binary file of part values
	fstream acctFile;
	account acct;

	int i, n;
	char type;
	double amt;

	// open binary file for input and output. truncate earlier version
	acctFile.open("accounts.dat",ios::in | ios::out |
					   ios::trunc | ios::binary);

	if (!acctFile)
	{
		cerr << "Cannot create 'accounts.dat'" << endl;
		exit(1);
	}

	// write 5 records with account number 0, 1, ..., 4
	for (i=0;i < 5;i++)
	{
		acct = account(i);
		acctFile.write((char *)&acct, sizeof(account));
	}

	// ask user to input account number and 'D' for deposit
	// and 'W' for withdrawal along with the ammount
	// update a record of the file; terminate with accout number -1
	while(true)
	{
		cout << "Enter acct#, type (D or W), and amount: ";
		cin >> n;
		if (n == -1)
			break;
		cin >> type >> amt;

		// seek to record n
		acctFile.seekg(n*sizeof(account), ios::beg);
		// read the record and update the balance
		acctFile.read((char *)&acct, sizeof(account));
		acct.update(type, amt);

		// seek back to the previous record
		acctFile.seekg(-int(sizeof(account)), ios::cur);
		acctFile.write((char *)& acct, sizeof(account));
	}

	// output final state of the account database
	cout << endl << "Final state of the accounts" << endl;
	outputAccounts(acctFile);

	return 0;
}

void outputAccounts(fstream& f)
{
	account acct;

	// go to the end of the file
	f.seekg(0, ios::end);

	// n = number of records in the file
	int n = f.tellg()/sizeof(account), i;

	// go back to the beginning of the file
	f.seekg(0, ios::beg);

	// read and output n records
	for (i=0; i < n; i++)
	{
		f.read((char *)& acct, sizeof(account));
		cout << acct << endl;
	}
}

/*
Run:

Enter acct#, type (D or W), and amount: 3 D 200.00
Enter acct#, type (D or W), and amount: 1 D 500.00
Enter acct#, type (D or W), and amount: 4 W 150.00
Enter acct#, type (D or W), and amount: 2 D 800.00
Enter acct#, type (D or W), and amount: 4 D 225.00
Enter acct#, type (D or W), and amount: 2 W 475.00
Enter acct#, type (D or W), and amount: 1 W 100.00
Enter acct#, type (D or W), and amount: -1

Final state of the accounts
0: 0
1: 400
2: 325
3: 200
4: 75
*/
