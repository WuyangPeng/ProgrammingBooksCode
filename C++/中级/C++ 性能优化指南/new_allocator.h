# include <limits>
# include <memory>

// C++98-style allocator that duplicates function of std::allocator

template <typename T> class Allocator {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

public:
	template <typename U> struct rebind {
		typedef Allocator<U> other;
	};

public:
	Allocator() {/*empty*/}
	~Allocator() {/*empty*/}
	Allocator(Allocator const&) {/*empty*/}
	template<typename U> explicit Allocator(Allocator<U> const&) {/*empty*/}

	const_pointer address(const_reference r) { return &r; }
	pointer address(reference r) { return &r; }

	void construct(pointer p, const T& t) {
		new(p) T(t); 
	}
	void destroy(pointer p) {
		p->~T();
	}
	size_type max_size() const {
		return std::numeric_limits<size_type>::max() / sizeof(T);
	}
	bool operator==(Allocator const&) {
		return true;
	}
	bool operator!=(Allocator const& a) {
		return !operator==(a);
	}

	pointer allocate(
		size_type count,
		typename std::allocator<void>::const_pointer = 0) {
		return reinterpret_cast<pointer>(::operator new(count * sizeof(T)));
	}
	void deallocate(pointer p, size_type) {
		::operator delete(p);
	}
};