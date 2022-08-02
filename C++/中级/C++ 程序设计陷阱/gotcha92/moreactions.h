#ifndef MOREACTIONS_H
#define MOREACTIONS_H

#include "button.h"
#include "cptr.h"
#include <list>
#include <iostream>

class Macro : public Action {
  public:
    void add( const Action *a )
        { a_.push_back( a->clone() ); }
    void operator ()() {
        for( I i(a_.begin()); i != a_.end(); ++i )
            (**i)();
    }
    Macro *clone() const {
        Macro *m = new Macro;
        for( CI i(a_.begin()); i != a_.end(); ++i )
            m->add((*i).operator->());
        return m;
    }
  private:
    typedef std::list< Cptr<Action> > C;
    typedef C::iterator I;
    typedef C::const_iterator CI;
    C a_;
};

struct Talk : public Action {
	void operator ()()
		{ std::cout << "Hello!!!" << std::endl; }
	Talk *clone() const
		{ return new Talk; }
};

struct Beep : public Action {
	void operator ()()
		{ std::cout << "\a" << std::flush; }
	Beep *clone() const
		{ return new Beep; }
};

#endif
