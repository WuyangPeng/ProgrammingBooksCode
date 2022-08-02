#include "firewall.h"
#include <iostream>

Msg *Firewall::genMsg( RawMsgSource &src ) {
    int code = src.msgcode;
    for( I i( types_->begin() ); i != types_->end(); ++i )
        if( code == (*i)->code() )
            return (*i)->generate( src );
    return 0;
}

void Firewall::addMsgType( const MsgType *mt ) {
	// Perform lazy initialization of container to
	// avoid runtime static initialization ordering
	// problems.
	// In this case, destruction of the container is
	// not a problem.
    if( !types_ )
    	types_ = new C;
    types_->push_back(mt);
}


Firewall::C *Firewall::types_ = 0;
