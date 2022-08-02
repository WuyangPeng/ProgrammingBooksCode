# include <iostream>
# include <cstddef>
# include "test_driver.h"

int test_cache(int test_no, unsigned long) {
	bool rc = true;
	switch(test_no) {
	default: return -1;
	case 0:  return 2;
	case 1:  return 1;
	case 2: {
		struct S1 {
			char c1;
			short s1;
			double d1;
			int i1;
			char c2;
		};
		std::cout << "size of struct S1: " << sizeof(S1) << std::endl
			      << "    offset of c1: " << offsetof(S1, c1) << std::endl
			      << "    offset of s1: " << offsetof(S1, s1) << std::endl
			      << "    offset of d1: " << offsetof(S1, d1) << std::endl
			      << "    offset of i1: " << offsetof(S1, i1) << std::endl
			      << "    offset of c2: " << offsetof(S1, c2) << std::endl;
		struct S1a {
			struct S1 s1;
			char c3;
		};
		std::cout << "size of struct S1a: " << sizeof(S1a) << std::endl
			      << "    offset of c3: " << offsetof(S1a, c3) << std::endl;

		struct S2 {
			char c1;
			char c2;
			short s1;
			int i1;
			double d1;
		};
		std::cout << "size of struct S2: " << sizeof(S2) << std::endl;
		break;
		}
	}
    return rc ? 1 : 0;
}

int main(int argc, char** argv) {
	test_driver(test_cache);
	return 0;
}