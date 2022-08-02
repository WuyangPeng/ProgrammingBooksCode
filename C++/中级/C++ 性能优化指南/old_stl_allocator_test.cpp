# include "simple_allocator.h"
# include "old_block_allocator.h"
# include "stopwatch03.h"
# include <string>
# include <iostream>

typedef std::basic_string<
	char, 
	std::char_traits<char>,
	Allocator<char>> SimpleStringT;

typedef std::basic_string<
	char, 
	std::char_traits<char>,
	block_allocator<char, 10>> fixed_block_string;

// original, naive remove_ctrl()
std::string remove_ctrl(std::string s) {
    std::string result;
    for (size_t i=0; i<s.length(); ++i) {
        if (s[i] >= 0x20)
            result = result + s[i];
    }
    return result;
}
#ifdef never
// original, naive remove_ctrl(), substituting SimpleStringT for std::string
SimpleStringT remove_ctrl_simple(std::string s) {
    SimpleStringT result;
    for (size_t i=0; i<s.length(); ++i) {
        if (s[i] >= 0x20)
            result = result + s[i];
    }
    return result;
}
#endif
// original, naive remove_ctrl(), with fixed_block_string substituted for some std::string instances
fixed_block_string remove_ctrl_fixed_block(std::string s) {
    fixed_block_string result;
    for (size_t i=0; i<s.length(); ++i) {
        if (s[i] >= 0x20)
            result = result + s[i];
    }
    return result;
}

int test_fixed_block_allocator(int test_no, unsigned long multiplier)
{
	typedef unsigned counter_t;
	counter_t const iterations = 100*multiplier;

    std::string s("\07Now is the time\07 for all good men\r\n to come to the aid of their country. \07");
    std::string test("Now is the time for all good men to come to the aid of their country. ");
    s = s + s + s;
    test = test + test + test;

	std::string stdresult;
	fixed_block_string fbresult;

    bool rc = true;

    switch (test_no) {
    default: return -1;
    case 0:  return 2;
    case 1:
		{
			void* p = block_o_memory::allocate(100);
			void* q = block_o_memory::allocate(200);
			void* r = block_o_memory::allocate(333);
			block_o_memory::deallocate(r);
			block_o_memory::deallocate(p);
			block_o_memory::deallocate(q);
			rc &= (block_o_memory::count() <= 1); // 0 for release, 1 for debug
		}
        std::cout << s.length() << " character argument to remove_ctrl()" << std::endl;
        std::cout << iterations << " iterations" << std::endl;
		{
			std::string verifier;

			verifier = remove_ctrl(s);
			rc &= (verifier.compare(test) == 0);

		//	SimpleStringT result1 = remove_ctrl_simple(s);
		//	verifier = result1.data();
		//	rc &= (verifier.compare(test) == 0);

			fixed_block_string result2 = remove_ctrl_fixed_block(s);
			verifier = result2.data();
	        rc &= (verifier.compare(test) == 0);
		}
        break;

    case 2: 
		{
            Stopwatch sw("remove_ctrl()");
            for (counter_t i = 0; i < iterations; ++i)
                stdresult = remove_ctrl(s);
        }
		{
            Stopwatch sw("remove_ctrl_fixed_block()");
            for (counter_t i = 0; i < iterations; ++i)
                fbresult = remove_ctrl_fixed_block(s);
        }
        break;
	}
    return rc ? 1 : 0;
}
