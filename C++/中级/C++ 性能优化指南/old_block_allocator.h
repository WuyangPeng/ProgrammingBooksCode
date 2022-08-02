# include <limits>
# include <memory>

// quick 'n dirty fixed-block allocator for strings
// unacceptable O(n) search for free blocks

class block_o_memory {
public:
	static const unsigned size = 8;
	static const size_t   blocksize = 512;
	static void* allocate(size_t size);
	static void  deallocate(void* p);
	static unsigned count();
private:
	static char mem_[size][blocksize];
	static bool free_[size];
};

template <typename T> class std_allocator_defs {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	pointer address(reference r) { return &r; }
	const_pointer address(const_reference r) { return &r; }
};

template <typename T, size_t n> class block_allocator : public std_allocator_defs<T> {

public:
	template <typename U> struct rebind {
		typedef block_allocator<U, n> other;
	};

public:
	block_allocator() {/*empty*/}
	~block_allocator() {/*empty*/}
	block_allocator(block_allocator const&) {/*empty*/}
	template<typename U> explicit block_allocator(block_allocator<U,n> const&) {/*empty*/}

	void construct(pointer p, const T& t) {
		new(p) T(t); 
	}
	void destroy(pointer p) {
		p->~T();
	}
	size_type max_size() const {
		return block_o_memory::blocksize;
	}
	bool operator==(block_allocator const&) const {
		return true;
	}
	bool operator!=(block_allocator const& a) const {
		return !operator==(a);
	}

	pointer allocate(
		size_type count,
		typename std::allocator<void>::const_pointer = 0) {
		return reinterpret_cast<pointer>(block_o_memory::allocate(count * sizeof(T)));
	}
	void deallocate(pointer p, size_type) {
		block_o_memory::deallocate(p);
	}
};