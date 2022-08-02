#include "money.h"

int main() {
	Money<Yen> acct1( 1000000.00 );
	Money<DM> acct2( 123.45 );
	Money<Yen> acct3( acct2 ); // template ctor
	Money<Yen> acct4( acct1 ); // compiler-generated copy ctor!
	acct3 = acct2; // template assignment
	acct4 = acct1; // compiler-generated assignment!
	
	return 0;
}

