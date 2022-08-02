#include <iostream>

// define only one of the following!
//#define PTRPTR
#define REFPTR

#ifdef PTRPTR

// get_token returns a pointer to the next sequence of
// characters bounded by characters in ws.
// The argument pointer is updated to point past the
// returned token.
// A null character is inserted into s after the token.
// Trailing whitespace produces a null token.
char *get_token( char **s, char *ws = " \t\n" ) {
    char *p;
    do
        for( p = ws; *p && **s != *p; p++ );
    while( *p ? *(*s)++ : 0 );
    char *ret = *s;
    do
        for( p = ws; *p && **s != *p; p++ );
    while( *p ? 0 : **s ? (*s)++ : 0 );
    if( **s ) {
    	**s = '\0';
    	++*s;
    }
    return ret;
}

#endif

#ifdef REFPTR

char *get_token( char *&s, char *ws = " \t\n" ) {
    char *p;
    do
        for( p = ws; *p && *s != *p; p++ ); 
    while( *p ? *s++ : 0 );
    char *ret = s;
    do
        for( p = ws; *p && *s != *p; p++ );
    while( *p ? 0 : *s ? s++ : 0 );
    if( *s ) *s++ = '\0';
    return ret;
}

#endif

extern char *getInputBuffer() {
	static char buf[] = "this is an input buffer";
	return buf;
}

int main() {
	char *tokens = getInputBuffer();
	std::cout << "Input buffer: |" << tokens << "|" << std::endl;
	//...
	while( *tokens )
#ifdef PTRPTR
    	std::cout << "token: |" << get_token( &tokens ) << '|' << std::endl;
#endif
#ifdef REFPTR
    	std::cout << "token: |" << get_token( tokens ) << '|' << std::endl;
#endif
    
    return 0;
}
