# ifndef HASH_H
#	define HASH_H

// hash functions from boost

// combine a hash-in-progress with the next element to be hashed
template <typename T> inline void hash_combine(size_t& seed, T const& v) {
	seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// hash a range given by first/last iterators
template <typename It> inline size_t hash_range(It first, It last) {
	size_t hash = 0;
	for (; first != last; ++first)
		hash_combine(hash, *first);
	return hash;
}

//	hash a sequence container supporting iterators
template <typename SEQ> struct hash_seq {
	std::size_t operator() (SEQ const& x) const {
        return hash_range(x.begin(), x.end());
    }
};

# endif