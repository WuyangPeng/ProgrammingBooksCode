// from Optimized C++, (c) Copyright 2015, by Kurt Guntheroth, All Rights Reserved
// fixed block memory manager

# include "block_mgr.h"	// block memory manager
# include <exception>	// defines std::bad_alloc

// something for memory managers to allocate
class TestClass {
	int contents_;
public:
	TestClass(int c) : contents_(c) {}
};

# include <random>			// for randomly allocating and freeing nodes
# include <functional>		// for bind, used by random
# include <iostream>		// std::cout, etc
# include "stopwatch03.h"	// stopwatch class for performance testing

// class with class-specific operator new
class MemMgrTester {
	int contents_;
public:
	MemMgrTester(int c) : contents_(c) {}

	static void* operator new(size_t s){ return mgr_.allocate(s); }
	static void  operator delete(void* p) { mgr_.deallocate(p); }

	static fixed_block_memory_manager<fixed_arena_controller> mgr_;
};

char arena2[4004];
fixed_block_memory_manager<fixed_arena_controller> MemMgrTester::mgr_(arena2);

int test_fixed_block_memory_manager(int test_no, unsigned long multiplier) {
	bool rc = true;
	switch (test_no) {
	default: return -1; // no test with this number
	case 0:  return 3;	// total number of tests
	case 1: {			// unit test
		    char arena[101];
			fixed_block_memory_manager<fixed_arena_controller> block_mgr(arena);
			for (int i = 0; i < 10; ++i)
				block_mgr.allocate(10);
			try {
				block_mgr.allocate(10);
				rc = false;
			}
			catch (std::bad_alloc&) {
				rc &= true;
			}
		}
		{
			char arena[7];
			fixed_block_memory_manager<fixed_arena_controller> block_mgr(arena);
			try {
				//	should allocate a single four-byte node
				block_mgr.allocate(3);
				rc &= true;
			}
			catch (std::bad_alloc&) {
				rc &= false;
			}
			try {
				block_mgr.allocate(3);
				rc &= false;
			}
			catch (std::bad_alloc&) {
				rc &= true;
			}
		}
		{
			char arena[1];
			fixed_block_memory_manager<fixed_arena_controller> block_mgr(arena);
			try {
				//	should fail on first node
				block_mgr.allocate(4);
				rc &= false;
			}
			catch (std::bad_alloc&) {
				rc &= true;
			}
		}
		break;

	case 2: {
			Stopwatch sw("allocate TestClass");
			for (auto j = 10 * multiplier; j > 0; --j) {
				for (auto i = 0; i < 1000; ++i)
					new TestClass(i);
			}
		}
		{
			std::cout << "sizeof(MemMgrTester) = " << sizeof(MemMgrTester) << std::endl;
			Stopwatch sw("allocate MemManTester: local new");
			for (auto j = 10 * multiplier; j > 0; --j) {
				MemMgrTester::mgr_.clear();
				for (auto i = 0; i < 1000; ++i)
					new MemMgrTester(i);
			}
		}
		{
			Stopwatch sw("allocate MemManTester: global new");
			for (auto j = 10 * multiplier; j > 0; --j) {
				for (auto i = 0; i < 1000; ++i)
					::new MemMgrTester(i);
			}
		}
		break;

	case 3: {
			static const unsigned array_size = 1000;
			{
				std::default_random_engine e;
				std::uniform_int_distribution<unsigned> d(0, array_size - 1);
				auto randomizer = std::bind(d, e);

				MemMgrTester::mgr_.clear();

				MemMgrTester* a[array_size];
				for (int i = 0; i < array_size; ++i)
					a[i] = nullptr;

				Stopwatch sw("MemMgrTester: local new/delete");

				for (auto i = 10000 * multiplier; i > 0 && !MemMgrTester::mgr_.empty(); --i) {
					auto idx = randomizer();
					auto p = new MemMgrTester(i);
					if (a[idx] != nullptr) {
						delete a[idx];
					}
					a[idx] = p;
				}

				for (auto i = 0; i < array_size; ++i)
					delete a[i];
			}
			{
				std::default_random_engine e;
				std::uniform_int_distribution<unsigned> d(0, array_size - 1);
				auto randomizer = std::bind(d, e);

				MemMgrTester::mgr_.clear();

				MemMgrTester* a[array_size];
				for (int i = 0; i < array_size; ++i)
					a[i] = nullptr;

				Stopwatch sw("MemMgrTester: global new/delete");

				for (auto i = 10000 * multiplier; i > 0 && !MemMgrTester::mgr_.empty(); --i) {
					auto idx = randomizer();
					auto p = ::new MemMgrTester(i);
					if (a[idx] != nullptr) {
						::delete a[idx];
					}
					a[idx] = p;
				}

				for (auto i = 0; i < array_size; ++i)
					::delete a[i];
			}
		}
		break;
	}
	return rc ? 1 : 0;
}
