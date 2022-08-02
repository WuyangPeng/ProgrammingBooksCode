# include "test_driver.h"

int test_class_new(int, unsigned long);
int test_list_allocator(int, unsigned long);
int test_string_allocator(int, unsigned long);
int test_fixed_block_memory_manager(int, unsigned long);
int test_copy_elision(int, unsigned long);
int test_insert_ctrl(int, unsigned long);

testfunc flist[] = {
//	test_class_new,
//	test_insert_ctrl,
//	test_copy_elision,
//	test_fixed_block_memory_manager,
	test_list_allocator,
	test_string_allocator,
	0
};

int main(int argc, char** argv)
{
	test_driver(flist, argc, argv);
	return 0;
}
