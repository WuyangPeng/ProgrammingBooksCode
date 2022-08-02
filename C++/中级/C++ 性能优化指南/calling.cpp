# include "calling.h"
# include "stopwatch03.h"

static volatile int x;

typedef unsigned long long counter_t;

int test_calling(int test_no, unsigned long) {
	bool rc = true;
	volatile int retval;
	counter_t const nCalls = 1000000ULL * 10ULL;
	std::cout << nCalls << " iterations" << std::endl;
	switch (test_no) {
	default:	return -1;
	case 0:		return 5;
	case 1:		return 1;
	case 2: {
			C c;
			C1 c1(c);
			C2 c2(c1);
			C3 c3(c2);
			C4 c4(c3);
			C5 c5(c4);
			Stopwatch sw("zero arg");
			for (counter_t i = 0; i < nCalls; ++i)
				c.f0();
			sw.Start("c.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				c1.f0();
			sw.Start("c1.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				c2.f0();
			sw.Start("c2.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				c3.f0();
			sw.Start("c3.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				c4.f0();
			sw.Start("c4.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				c5.f0();
			sw.Stop("c5.f0()");
			rc = (c.x_ == 0xfffffffe);
		}
		break;

	case 3: {
			C c;
			C1 c1(c);
			C2 c2(c1);
			C3 c3(c2);
			C4 c4(c3);
			C5 c5(c4);
			Stopwatch sw("zero arg");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c.f0();
			sw.Start("c.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c1.f0();
			sw.Start("c1.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c2.f0();
			sw.Start("c2.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c3.f0();
			sw.Start("c3.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c4.f0();
			sw.Start("c4.f0()");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c5.f0();
			sw.Stop("c5.f0()");
			rc = (c.x_ == 0xfffffffe);
		}
		break;

	case 4:	{//	overhead of a single argument function
			C c;
			C1 c1(c);
			C2 c2(c1);
			C3 c3(c2);
			C4 c4(c3);
			C5 c5(c4);
			Stopwatch sw("single arg");
			for (counter_t i = 0; i < nCalls; ++i)
				c.f1(i);
			sw.Start("c.f1(i)");
			for (counter_t i = 0; i < nCalls; ++i)
				c1.f1(i);
			sw.Start("c1.f1(i)");
			for (counter_t i = 0; i < nCalls; ++i)
				c2.f1(i);
			sw.Start("c2.f1(i)");
			for (counter_t i = 0; i < nCalls; ++i)
				c3.f1(i);
			sw.Start("c3.f1(i)");
			for (counter_t i = 0; i < nCalls; ++i)
				c4.f1(i);
			sw.Start("c4.f1(i)");
			for (counter_t i = 0; i < nCalls; ++i)
				c5.f1(i);
			sw.Stop("c5.f1(i)");
		}
		break;

	case 5:	{//	overhead of a single argument function
			C c;
			C1 c1(c);
			C2 c2(c1);
			C3 c3(c2);
			C4 c4(c3);
			C5 c5(c4);
			Stopwatch sw("single arg");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c.f1(0);
			rc = (c.x_ == 0xfffffffe);
			sw.Start("c.f1(0)");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c1.f1(1);
			rc = (c.x_ == 0xfffffffe);
			sw.Start("c1.f1(1)");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c2.f1(2);
			rc = (c.x_ == 0xfffffffe);
			sw.Start("c2.f1(2)");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c3.f1(3);
			rc = (c.x_ == 0xfffffffe);
			sw.Start("c3.f1(3)");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c4.f1(4);
			rc = (c.x_ == 0xfffffffe);
			sw.Start("c4.f1(4)");
			for (counter_t i = 0; i < nCalls; ++i)
				retval = c5.f1(5);
			rc = (c.x_ == 0xfffffffe);
			sw.Stop("c5.f1(5)");
		}
		break;

	}
	return rc ? 1 : 0;
}

# include "test_driver.h"

int main (int, char**) {
	test_driver(test_calling);
    return 0;
}// end main