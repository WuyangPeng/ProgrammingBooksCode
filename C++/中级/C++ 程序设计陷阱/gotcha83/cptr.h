#ifndef CPTR_H
#define CPTR_H

template <class T>
class Cptr {
  public:
    Cptr( T *p ) : p_( p ), c_( new long( 1 ) ) {}
    ~Cptr() { if( !--*c_ ) { delete c_; delete p_; } }
    Cptr( const Cptr &init )
        : p_( init.p_ ), c_( init.c_ ) { ++*c_; }
    Cptr &operator =( const Cptr &rhs ) {
        if( this != &rhs ) {
            if( !--*c_ ) { delete c_; delete p_; }
            p_ = rhs.p_;
            ++*(c_ = rhs.c_);
        }
        return *this;
	}
    T &operator *() const
        { return *p_; }
    T *operator ->() const
        { return p_; }
  private:
    T *p_;
    long *c_;
};

#endif
