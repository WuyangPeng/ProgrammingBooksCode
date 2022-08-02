#ifndef MSG_H
#define MSG_H

class Msg {
  public:
    virtual void send();
    // . . . 
};
class XMsg : public Msg {
  public:
    void send();
    // . . . 
};

#endif
