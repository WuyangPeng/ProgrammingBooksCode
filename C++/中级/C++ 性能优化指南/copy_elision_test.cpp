
# include <vector>
# include <iostream>

struct Noisy {
	Noisy() { std::cout << "constructed\n"; }
	Noisy(const Noisy&) { std::cout << "copied\n"; }
	Noisy& operator=(const Noisy&) { std::cout << "assigned\n"; return *this; }
	~Noisy() { std::cout << "destroyed\n"; }
	Noisy(Noisy&&) { std::cout << "moved\n"; }
};

std::vector<Noisy> f()
{
	std::vector<Noisy> v = std::vector<Noisy>(3); // copy elision from temporary to v
	return v; // NRVO from v to the nameless temporary that is returned
			  // if optimizations are disabled, move constructor is called here
}

Noisy g()
{
	Noisy v;
	return v;
}

void test_noisy()
{
}

void fn_by_val(std::vector<Noisy> arg)
{
	std::cout << "arg.size() = " << arg.size() << '\n';
}

int test_copy_elision(int test_no, unsigned long)
{
	bool rc = true;
	switch (test_no) {
	default: return -1;	//	no test with this number
	case 0:  return 2;	//	number of tests
	case 1:	 return 1;	//  no module test, return success
	case 2: {
			std::cout << "copy elision on return\n";
			Noisy x = g();
			std::cout << "copy elision on assign\n";
			x = g();

			std::cout << "copy elision on return\n";
			   std::vector<Noisy> v = f(); // copy elision from returned temporary to v
			std::cout << "copy elision of unnamed temporary\n";
			   fn_by_val(f());             // and from temporary to the argument of fn_by_val()
			std::cout << "no copy elision on assignment\n";
			v = f();
			std::cout << std::flush;
		}
		break;
	}
	return rc ? 1 : 0;
}