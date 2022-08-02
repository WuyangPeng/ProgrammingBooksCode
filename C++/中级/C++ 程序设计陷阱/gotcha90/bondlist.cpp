#include <iostream>
#include <vector>
#include <algorithm>
#include "bondlist.h"

double bondPortfolioPV( BondList &bonds ) {
	double sumpv = 0.0;
	for( int i = 0; i < bonds.size(); ++i ) {
		Bond *b = bonds[i];
		sumpv += b->pv();
	}
	return sumpv;
}
class UnderpaidMinion : public Object {
  public:
    virtual double pay()
        { std::cout << "UnderpaidMinion::pay!" << std::endl; return 0.0; }
};
void sneaky( ObjectList &list )
    { list.insert( new UnderpaidMinion ); }
    
BondList bondList;
BondList &getBondList() {
	return bondList;
}

void victimize() {
    BondList &blist = getBondList();
    sneaky( blist );
    bondPortfolioPV( blist ); //done!
}

