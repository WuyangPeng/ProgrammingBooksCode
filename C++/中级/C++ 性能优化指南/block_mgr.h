// from Optimized C++, (c) Copyright 2015, by Kurt Guntheroth, All Rights Reserved
// fixed array memory manager to use with class-specific new
///////////////////////// fixed_block_memory_manager ////////////

template <class Arena> struct fixed_block_memory_manager {
	template <int N> 
		fixed_block_memory_manager(char(&a)[N]);
	fixed_block_memory_manager(fixed_block_memory_manager&) = delete;
   ~fixed_block_memory_manager() = default;
	void operator=(fixed_block_memory_manager&) = delete;

	void*  allocate(size_t);
	size_t block_size() const;
	size_t capacity() const;
	void   clear();
	void   deallocate(void*);
	bool   empty() const;

private:
	struct free_block {
		free_block* next;
	};
	free_block*	free_ptr_;
	size_t		block_size_;
	Arena		arena_;
};

///////////////////// fixed_arena_controller ////////////////////

struct fixed_arena_controller {
	template <int N> 
	    fixed_arena_controller(char(&a)[N]);
	fixed_arena_controller(fixed_arena_controller&) = delete;
   ~fixed_arena_controller() = default;
	void operator=(fixed_arena_controller&) = delete;
	
	void*  allocate(size_t);
	size_t block_size() const;
	size_t capacity() const;
	void   clear();
	bool   empty() const;

private:
	void*  arena_;
	size_t arena_size_;
	size_t block_size_;

};

# include "block_mgr.inl"
