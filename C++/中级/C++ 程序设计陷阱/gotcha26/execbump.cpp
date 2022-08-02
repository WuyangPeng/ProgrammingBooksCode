#include <iostream>

// Uncomment only one symbol!
//#define MACRO
//#define FUNCTION
#define MONOSTATE

#ifdef MACRO

int kount = 0;

#define execBump( func ) (func(), ++kount)

void aFunc() {
    extern void g();
    int kount = 0;
    while( kount++ < 10 )
        execBump( g ); // increment local count!
}

void g() { std::cout << "Called g, kount = " << kount << std::endl; }

#endif
//=================================================
#ifdef FUNCTION

int kount = 0;

inline void execBump( void (*func)() )
    { func(); ++kount; }
    
void aFunc() {
    extern void g();
    int kount = 0;
    while( kount++ < 10 )
        execBump( g ); // increment local count!
}

void g() { std::cout << "Called g, kount = " << kount << std::endl; }

#endif
//=================================================
#ifdef MONOSTATE
class ExecBump { // Monostate.  See Gotcha #69.
  public:
    void operator ()( void (*func)() )
        { func(); ++count_; }
    int get_count() const
    	{ return count_; }
  private:
    static int count_;
};

int ExecBump::count_ = 0;

void aFunc() {
    extern void g();
    ExecBump exec;
    int kount = 0;
    while( kount++ < 10 )
        exec( g );
}

void g() { std::cout << "Called g, count = " << ExecBump().get_count() << std::endl; }

#endif

int main() {
	aFunc();
	return 0;
}
