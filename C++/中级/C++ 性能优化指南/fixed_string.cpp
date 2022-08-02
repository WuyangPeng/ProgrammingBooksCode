# include "fixed_string.h"
# include "charbuf.h"
# include "hash.h"
# include <iostream>

// lets you visibly check for extremely obvious collisions, tests hash and basic_fixed_string
void show_hash() {
	hash_seq<basic_fixed_string<>> f;
	std::cout << "hash(\"a\") = " << f(basic_fixed_string<>("a")) << "\n"
	          << "hash(\"A\") = " << f(basic_fixed_string<>("A")) << "\n"
	          << "hash(\"b\") = " << f(basic_fixed_string<>("b")) << "\n"
	          << "hash(\"abc\") = " << f(basic_fixed_string<>("abc")) << "\n"
	          << "hash(\"xyzw\") = " << f(basic_fixed_string<>("xyzw")) << std::endl;
}

// test driver for basic_fixed_string<>

int test_fixed_string(int testno, unsigned long) {
	bool rc = true;
	switch (testno) {
		default:return -1;
		case 0:	return 2;
		case 1: {
			basic_fixed_string<9> s0;
			basic_fixed_string<9> s1("xyzzy");
		//	rc &= (s0 != "xyzzy");
			rc &= (s0 != basic_fixed_string<9>("xyzzy"));
			rc &= (s0 == basic_fixed_string<9>());
		//	rc &= (s0 == "");
			rc &= (s0 == basic_fixed_string<9>(""));
		//	rc &= (s1 == "xyzzy");
			rc &= (s1 == basic_fixed_string<9>("xyzzy"));
			rc &= (s1 != basic_fixed_string<9>());
		}
		break;

		case 2: {
			charbuf<> cb, cb2;
			rc &= (cb == cb);
			rc &= (cb == cb2);
			rc &= (cb == "");
			rc &= !(cb == "x");
			cb = "xyz";
			rc &= (cb == "xyz");
			rc &= !(cb == "abc");
			rc &= !(cb == cb2);
			cb2 = cb;
			rc &= (cb2 == "xyz");
			rc &= !(cb2 == "abc");
			rc &= !(cb2 == "");
			cb = "a";
			cb2 = "b";
			rc &= (cb < cb2);
			rc &= !(cb2 < cb);
			cb2 = "aa";
			rc &= (cb < cb2);
			rc &= !(cb2 < cb);
		}
		break;
	}
	return rc ? 1 : 0;
}