#ifndef FIREWALL_H
#define FIREWALL_H

#include <vector>

struct RawMsgSource {
	RawMsgSource( const char *msg )
		: msgcode( msg[0] ), msgBody( msg+1 ) {}
	char msgcode;
	const char *msgBody; // variable-length
};

class Msg {
  public:
	virtual ~Msg() {}
	virtual void op1() = 0;
};

class MsgType {
  public:
    virtual ~MsgType() {}
    virtual int code() const = 0;
    virtual Msg *generate( RawMsgSource & ) const = 0;
};

class Firewall { // Monostate
  public:
    void addMsgType( const MsgType * );
    Msg *genMsg( RawMsgSource & );
    
    typedef std::vector<const MsgType *> C;
    typedef C::const_iterator I;
  private:
    static C *types_;
};

#endif
