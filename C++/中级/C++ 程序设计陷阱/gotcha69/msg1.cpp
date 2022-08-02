#include "firewall.h"
#include <iostream>

class Msg1 : public Msg {
  public:
	enum { code = 0x05 };
	Msg1( RawMsgSource & )
		{}
	void op1()
		{ std::cout << "Msg1::op1" << std::endl; }
};

class Msg1Type : public MsgType {
  public:
    Msg1Type()
        { Firewall().addMsgType( this ); }
    int code() const
        { return Msg1::code; }
    Msg *generate( RawMsgSource &src ) const
        { return new Msg1( src ); }
};

static Msg1Type msg1type;
