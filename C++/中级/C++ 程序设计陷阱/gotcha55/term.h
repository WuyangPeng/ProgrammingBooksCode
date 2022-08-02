#ifndef TERM_H
#define TERM_H

extern const char *terminalType;
//other things to initialize...

class InitMgr { // Schwarz counter
  public:
    InitMgr()
        { if( !count_++ ) init(); }
    ~InitMgr()
        { if( !--count_ ) cleanup(); }
    void init();
    void cleanup();
  private:
    static long count_; // one per process
};
namespace { InitMgr initMgr; } // one per file inclusion

#endif
