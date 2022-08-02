class Person {
  static const char *myName = "Fred";
  public:
		const char* name() {
    	return myName;
  	}
};

class Money {
  private:
  	double myValue;
  public:
  	Money() {
      myValue = 0.0;
    }
  	Money(double aValue) {
      myValue = aValue;
    }
  	void setValue(const double aValue) {
      myValue = aValue;
    };
};

class BankAccount {
  private:
  	Money *myBalance;
  public:
  	BankAccount() {
      myBalance = new Money();
    }
  	void setBalance(const Money &anAmt) {
      myBalance = new Money(anAmt);
    }
  	Person* getOwner() { 
      return new Person(); 
    }
};

void markWorkflow(const char* aName, int aCmd) {}
const int SET_BALANCE=10;

//START:ex
void processTransaction(BankAccount acct, int) {
  Person *who;
  Money amt;

  amt.setValue(123.45);
  acct.setBalance(amt);
  who = acct.getOwner();
  markWorkflow(who->name(), SET_BALANCE);
}
//END:ex
