#ifndef MYASSERT_H
#define MYASSERT_H

#include <iostream>

// undefine standard assert so we can show our own version
// don't do this in production code!
#undef assert

#ifndef NDEBUG

#define assert(e) ((e) \
    ? ((void)0) \
    :__assert_failed(#e,__FILE__,__LINE__) )
    
void __assert_failed(const char *m, const char *file, int line ) {
	std::cerr << "Assertion failed: " << m << " file: " << file
	<< " line: " << line << std::endl;
	// pedagogic code: comment out abort to allow multiple assertions
	// std::abort();
}

#else

#define assert(e) ((void)0)

#endif

#endif
