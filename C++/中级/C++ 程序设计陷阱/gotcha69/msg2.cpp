#include "firewall.h"
#include <iostream>

class Msg2 : public Msg {
  public:
	enum { code = 0x09 };
	Msg2( RawMsgSource & )
		{}
	void op1()
		{ std::cout << "Msg2::op1" << std::endl; }
};

class Msg2Type : public MsgType {
  public:
    Msg2Type()
        { Firewall().addMsgType( this ); }
    int code() const
        { return Msg2::code; }
    Msg *generate( RawMsgSource &src ) const
        { return new Msg2( src ); }
};

static Msg2Type msg2type;
