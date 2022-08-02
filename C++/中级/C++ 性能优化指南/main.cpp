# include "test_driver.h"
# include <iostream>

int test_remove_ctrl(int test_no, unsigned long multiplier);
int test_file_reader(int test_no, unsigned long multiplier);
int test_allocator(int test_no, unsigned long multiplier);

int (*func[])(int, unsigned long) = {
	test_remove_ctrl, 
	test_file_reader, 
//	test_allocator,
	0
};

int main (int, char**) {
	test_driver(func);
    return 0;
}// end main