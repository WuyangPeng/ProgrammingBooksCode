#include <iostream>

// Uncomment only one of the following!
//#define NONVIRTBASE
#define VIRTBASE

class A {
  public:
	A( int x = 9999 )
		: a( x ) {}
    virtual ~A();
    void print() const
    	{ std::cout << "A: " << a; }
  private:
	int a;
};

inline A::~A()
    {}

#ifdef NONVIRTBASE

class B : public A {
  public:
	B( int a, int x )
		: A( a ), b( x ) {}
	B &operator =( const B &rhs ) {
		if( this != &rhs ) {
			b = rhs.b;
		}
		return *this;
	}
	void print() const
		{ std::cout << "B: " << b << " "; A::print(); }
  private:
	int b;
};

class C : public A {
  public:
	C( int a, int x )
		: A( a ), c( x ) {}
	C &operator =( const C &rhs ) {
		if( this != &rhs ) {
			c = rhs.c;
		}
		return *this;
	}
	void print() const
		{ std::cout << "C: " << c << " "; A::print(); }
  private:
	int c;
};

class D : public B, public C {
  public:
	D( int a, int b, int c, int x )
		: B( a, b ), C( a, c ), d( x ) {}
	D &operator =( const D &rhs );
	void print() const
		{ std::cout << "D: " << d << " "; B::print(); std::cout << " "; C::print(); std::cout << std::endl; }
  private:
	int d;
};

D &D::operator =( const D &rhs ) {
    if( this != &rhs ) {
        B::operator =( *this ); // assign B subobject
        C::operator =( *this ); // assign C subobject
        // assign any D-specific members...
        d = rhs.d;
    }
    return *this;
}

#endif

#ifdef VIRTBASE
class B : public virtual A {
  public:
	B( int a, int x )
		: A( a ), b( x ) {}
	B &operator =( const B &rhs ) {
		if( this != &rhs ) {
			b = rhs.b;
		}
		return *this;
	}
	void nonvirtAssign( const B &that )
		{ b = that.b; }
	void print() const
		{ std::cout << "B: " << b << " "; A::print(); }
  private:
	int b;
};

class C : public virtual A {
  public:
	C( int a, int x )
		: A( a ), c( x ) {}
	C &operator =( const C &rhs ) {
		if( this != &rhs ) {
			c = rhs.c;
		}
		return *this;
	}
	void nonvirtAssign( const C &that )
		{ c = that.c; }
	void print() const
		{ std::cout << "C: " << c << " "; A::print(); }
  private:
	int c;
};

class D : public B, public C {
  public:
	D( int a, int b, int c, int x )
		: B( a, b ), C( a, c ), d( x ) {}
	D &operator =( const D &rhs );
	void print() const
		{ std::cout << "D: " << d << " "; B::print(); std::cout << " "; C::print(); std::cout << std::endl; }
  private:
	int d;
};

D &D::operator =( const D &rhs ) {
    if( this != &rhs ) {
        A::operator =( *this ); // assign virtual A
        B::nonvirtAssign( *this ); // assign B, except A part
        C::nonvirtAssign( *this ); // assign C, except A part
        // assign any D-specific members...
        d = rhs.d;
    }
    return *this;
}

#endif

int main() {
	D d( 0, 1, 2, 3 );
	d.print();
	
	D e( d );
	e.print();
	
	d = e;
	d.print();

	return 0;
}
