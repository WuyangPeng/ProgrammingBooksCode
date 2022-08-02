// from Optimized C++, (c) Copyright 2015, by Kurt Guntheroth, All Rights Reserved
// fixed-size block memory manager
#ifdef never
# include "mem_mgr_fixed.h"

void* mem_manager::allocate(size_t size_requested) {
	size_t size_to_allocate;
	size_t* tmp;

//	the minimum size possible to allocate is 8+1 bytes, to hold the size of the allocation
	size_to_allocate = round_up(size_requested+sizeof(size_t), sizeof(size_t));
//	the minimum that will actually be allocated is 16 bytes
	size_to_allocate = std::max(size_to_allocate, minimum_allocation);
//	test argument for overflow, then validity
	if (size_requested > size_to_allocate || size_requested == 0)
		return nullptr;

//	walk the free list to find a node
	for (freenode** fptr = &freeptr; *fptr != nullptr; fptr = &(*fptr)->next) {
		if ((*fptr)->size < size_to_allocate) {
		//	node too small
			continue;
		}
		if ((*fptr)->size < 2*size_to_allocate) {
		//	node fits
			tmp = reinterpret_cast<size_t*>(*fptr) + 1;
			(*fptr) = (*fptr)->next;
			return tmp;
		}
		else {
		//  split big node
		}
	}

//	no free node or no fit
	if (freeptr == nullptr) {
		tmp = reinterpret_cast<size_t*>(malloc(std::max(chunk_size, size_to_allocate)));
		return tmp;
	}
}

void mem_manager::deallocate(void* p) {
	if (p == nullptr)
		return;
	size_t* memp = reinterpret_cast<size_t*>(p) - 1;
	freenode* nodep = reinterpret_cast<freenode*>(memp);
}
#endif