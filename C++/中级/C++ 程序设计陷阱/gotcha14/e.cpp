#include "e.h"

E::E()
	{}

E::~E()
	{}

Plus::Plus( E *l, E *r )
	: l_(l), r_(r) {}

Plus::~Plus()
	{ delete r_; delete l_; }
	
// incorrect implementation below!
//int Plus::eval() const
//    { return l_->eval() + r_->eval(); }

// correct implementation
int
Plus::eval() const {
	int tmp = l_->eval();
	return tmp + r_->eval();
}

Times::Times( E *l, E *r )
	: l_(l), r_(r) {}

Times::~Times()
	{ delete r_; delete l_; }

int
Times::eval() const {
	int tmp = l_->eval();
	return tmp * r_->eval();
}

Int::Int( int value )
		: v_( value ) {}

int
Int::eval() const
	{ return v_; }

Var::Var( const std::string &id )
: id_( id ) {}

int
Var::eval() const
	{ return stab_[id_]; }

int
Var::set( int newValue )
	{ return stab_[id_] = newValue; }

std::map<std::string,int> Var::stab_;

Assign::Assign( Var *var, E *expr )
	: var_( var ), e_( expr ) {}

Assign::~Assign()
	{ delete e_; delete var_; }

int
Assign::eval() const
	{ return var_->set( e_->eval() ); }

Uminus::Uminus( E *e )
	: e_( e ) {}

Uminus::~Uminus()
	{ delete e_; }

int
Uminus::eval() const
	{ return -e_->eval(); }
