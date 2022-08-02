#ifndef PTR_H
#define PTR_H

class T {
  public:
	void f();
};

class Ptr {
  public:
    Ptr( T *init );
    T *operator ->();
    //...
  private:
    T *tp_;
};

class AugPtr {
  public:
    AugPtr( T *init )
    	: p_( init ) {}
    Ptr &operator ->();
    //...
  private:
    Ptr p_;
};

#endif
