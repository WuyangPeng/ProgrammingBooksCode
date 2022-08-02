#ifndef E_H
#define E_H

/*

// Grammar for constructing the hierarchy:
E -> E + E
E -> E * E
E -> int
E -> id
E -> id = E

*/

#include <string>
#include <map>

class E {
public:
	E();
	virtual ~E();
	virtual int eval() const = 0;
private:
	E( const E & );
	E &operator =( const E & );
};

class Plus : public E {
public:
	Plus( E *l, E *r );
	~Plus();
	int eval() const;
private:
	E *l_, *r_;
};

class Times : public E {
public:
	Times( E *l, E *r );
	~Times();
	int eval() const;
private:
	E *l_, *r_;
};

class Int : public E {
public:
	Int( int value );
	int eval() const;
private:
	int v_;
};

class Var : public E {
public:
	Var( const std::string &id );
	int eval() const;
	int set( int newValue );
private:
	std::string id_;
	static std::map<std::string,int> stab_;
};

class Assign : public E {
public:
	Assign( Var *var, E *expr );
	~Assign();
	int eval() const;
private:
	Var *var_;
	E *e_;
};

class Uminus : public E {
public:
	Uminus( E *e );
	~Uminus();
	int eval() const;
private:
	E *e_;
};

#endif
