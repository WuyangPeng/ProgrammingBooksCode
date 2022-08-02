# include <exception>
# include "old_block_allocator.h"

// quick 'n dirty fixed-block allocator for strings
// unacceptable O(n) search for free blocks

char block_o_memory::mem_[block_o_memory::size][block_o_memory::blocksize];
bool block_o_memory::free_[block_o_memory::size] = { true, true, true, true, true, true, true, true };

void* block_o_memory::allocate(size_t size) {
	if (size <= blocksize) {
		for (unsigned i = 0; i < sizeof(free_)/sizeof(free_[0]); ++i) {
			if (free_[i]) {
				free_[i] = false;
				return mem_[i];
	}	}	}
	throw std::bad_alloc();
}

void block_o_memory::deallocate(void* p) {
	typedef char blocktype[512];
	if (p == 0)
		return;
	if (p < (void*)mem_ || p > (void*)(mem_ + size))
		throw std::bad_alloc();
	unsigned i = static_cast<blocktype*>(p) - mem_;
	free_[i] = true;
	mem_[i][0] = 0;
}

//	count how many blocks are allocated, for debugging
unsigned block_o_memory::count() {
	unsigned ct = 0;
	for (unsigned i = 0; i < size; ++i)
		if (!free_[i])
			ct += 1;
	return ct;
}