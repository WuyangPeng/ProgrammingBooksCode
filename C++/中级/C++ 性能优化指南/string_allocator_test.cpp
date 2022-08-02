# include <limits>
# include <memory>
# include "block_mgr.h"

// C++98-style Allocator that duplicates function of std::Allocator

template <typename T> class NewAllocator {
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
		typedef NewAllocator<U> other;
	};

public:
	NewAllocator() {/*empty*/ }
	~NewAllocator() {/*empty*/ }
	NewAllocator(NewAllocator const&) {/*empty*/ }
	template<typename U> explicit NewAllocator(NewAllocator<U> const&) {/*empty*/ }

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
	bool operator==(NewAllocator const&) {
		return true;
	}
	bool operator!=(NewAllocator const& a) {
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

// C++98-style allocator fixed-block allocator for strings

char string_arena[25000];
fixed_block_memory_manager<fixed_arena_controller> string_memory_manager(string_arena);

template <typename T> class StatelessStringAllocator {
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
		typedef StatelessStringAllocator<U> other;
	};

public:
	StatelessStringAllocator() {/*empty*/ }
	~StatelessStringAllocator() {/*empty*/ }
	StatelessStringAllocator(StatelessStringAllocator const&) {/*empty*/ }
	template<typename U> explicit StatelessStringAllocator(StatelessStringAllocator<U> const&) {/*empty*/ }

	const_pointer address(const_reference r) { return &r; }
	pointer address(reference r) { return &r; }

	void construct(pointer p, const T& t) {
		new(p) T(t);
	}
	void destroy(pointer p) {
		p->~T();
	}
	size_type max_size() const {
		return 512;
	}
	bool operator==(StatelessStringAllocator const&) const {
		return true;
	}
	bool operator!=(StatelessStringAllocator const& a) const {
		return !operator==(a);
	}
	pointer allocate(
		size_type /*count*/,
		typename std::allocator<void>::const_pointer /*hint*/ = nullptr) {
		return reinterpret_cast<pointer>(string_memory_manager.allocate(512));
	}
	void deallocate(pointer p, size_type) {
		string_memory_manager.deallocate(p);
	}
};

# include <string>

typedef std::basic_string<
	char,
	std::char_traits<char>,
	StatelessStringAllocator<char>> fixed_block_string;

// original, naive remove_ctrl()
std::string remove_ctrl(std::string s) {
	std::string result;
	for (size_t i = 0; i<s.length(); ++i) {
		if (s[i] >= 0x20)
			result = result + s[i];
	}
	return result;
}

// original, naive remove_ctrl(), with fixed_block_string substituted for some std::string instances
fixed_block_string remove_ctrl_fixed_block(std::string s) {
	fixed_block_string result;
	for (size_t i = 0; i<s.length(); ++i) {
		if (s[i] >= 0x20)
			result = result + s[i];
	}
	return result;
}

# include <iostream>
# include "stopwatch03.h"

int test_string_allocator(int test_no, unsigned long multiplier)
{
	typedef unsigned counter_t;
	counter_t const iterations = 100 * multiplier;

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
