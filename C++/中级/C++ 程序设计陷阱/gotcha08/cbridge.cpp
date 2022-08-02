#include "cbridge.h"

class Cimpl {
  public:
    Cimpl( int val ) : a_( val ), b_( a_ ) {}
    ~Cimpl() {}
    int get_a() const { return a_; }
    int get_b() const { return b_; }
  private:
    int a_;
    int b_;
};

C::C( int val )
    : impl_( new Cimpl( val ) ) {}
C::~C()
    { delete impl_; }
    
int C::get_a() const
    { return impl_->get_a(); }
    
int C::get_b() const
    { return impl_->get_b(); }
