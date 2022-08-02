#ifndef ACCOUNT_CLASS
#define ACCOUNT_CLASS

#include <iostream>

using namespace std;

// maintain bank account information
class account
{
	public:		
		account (int n = 0, double bal = 0.0): acctNo(n), balance (bal)
		{}		
		
		// update balance with deposit (D) or withdrawal (W)
		void update (char type, double amt)	
		{	
			if (type == 'D')
				balance += amt;
			else
				balance -= amt;
		}
		
		// output account
		friend ostream& operator<< (ostream& ostr, const account& acct)
		{			
			ostr << acct.acctNo << ": " << acct.balance;
			return ostr;		
		}
		
	private:		
		int acctNo;
		double balance;
};

#endif	// ACCOUNT_CLASS
