#ifndef MSGDECORATOR_H
#define MSGDECORATOR_H

#include "msg.h"

class MsgDecorator : public Msg {
  public:
	MsgDecorator( Msg *m )
		: decorated_( m ) {}
    void send() = 0;
  private:
    Msg *decorated_;
};

inline void MsgDecorator::send() {
    decorated_->send(); // forward call
}

class BeepDecorator : public MsgDecorator {
  public:
	BeepDecorator( Msg *m )
		: MsgDecorator( m ) {}
	void send();
};

#endif
