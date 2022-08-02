// from Optimized C++, (c) Copyright 2015, by Kurt Guntheroth, All Rights Reserved
// simple fixed-size block free memory manager

class mem_manager {
	struct freenode {
		size_t    size;
		freenode* next;
	};

	static freenode* freeptr;
	static size_t    chunk_size;

	static const size_t default_chunk_size = 8192;
	static const size_t minimum_allocation = 16;

	//	round to a multiple of multiple
	int round_up(int num_to_round, int multiple) 
	{
		return ((num_to_round + multiple - 1) / multiple) * multiple;
	}

public:
	mem_manager(size_t chunk_size = default_chunk_size) {
	    freeptr = (nullptr);
	    chunk_size = (chunk_size);
	}
	
	void* allocate(size_t size);
	void  deallocate(void*);
};
