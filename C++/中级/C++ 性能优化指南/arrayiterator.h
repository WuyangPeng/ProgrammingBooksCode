# ifndef ARRAYITERATOR_H
#	define ARRAYITERATOR_H

//  standard-anticipating std::size() for C-style array
namespace std {
	template <typename T, int N> size_t size(T (&a)[N])	{ return N; }
//	template <typename T, int N> T* begin(T (&a)[N])	{ return &a[0]; }
//	template <typename T, int N> T* end(T (&a)[N])		{ return &a[N]; }
}

# endif