#include <iostream>
#include <memory>
#include "e.h"
#include "eparse.h"

using namespace std;

int
main() {
	Parser *parser = 0;
	try {
		parser = new ExprParser( new ExprLex );
		while( true ) {
			cout << "Enter an expression:  " << flush;
			auto_ptr<E> root( parser->parse() );
			if( !root.get() )
				break;
			cout << "Result: " << root->eval() << endl;
		}
	}
	catch( const exception &e ) {
		cout << "***" << e.what() << "***" << endl;
	}
	catch( ... ) {
		cout << "caught some exception" << endl;
	}
	delete parser;

	return 0;
}
