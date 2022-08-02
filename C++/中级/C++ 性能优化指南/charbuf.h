# ifndef CHARBUF_H
#	define CHARBUF_H

// simple container for a char[] text string
template <unsigned N=10, typename T=char> struct charbuf {
	charbuf();
	charbuf(charbuf const& cb);
	charbuf(T const* p);
	charbuf& operator=(charbuf const& rhs);
	charbuf& operator=(T const* rhs);

	T* data();
	T const* data() const;

	operator size_t() const;

	bool operator==(charbuf const& that) const;
	bool operator<(charbuf const& that) const;

	size_t capacity() const;

	size_t hash1() const;
	size_t hash2() const;

private:
	T data_[N];
};

# include "hash.h"			// hash functions from boost to extend std::hash
# include "arrayiterator.h"	// std::begin(), std::end(), std::size()

template <unsigned N, typename T>
	inline charbuf<N,T>::charbuf() { 
		for (auto it = std::begin(data_); it < std::end(data_);++it)
			*it = 0;
	}

template <unsigned N, typename T>
	inline charbuf<N,T>::charbuf(charbuf const& that) { 
		T const* p = that.data();
		for (auto it = std::begin(data_); it != std::end(data_); ++it) {
			*it = *p;
			if (*p) 
				++p;
		}
	}

template <unsigned N, typename T>
	inline charbuf<N,T>::charbuf(T const* p) {
		if (p == nullptr) 
			p = "";
		for (auto it = std::begin(data_); it != std::end(data_); ++it) {
			*it = *p;
			if (*p) 
				++p;
		}
	}

	
template <unsigned N, typename T>
	inline charbuf<N,T>& charbuf<N,T>::operator=(charbuf const& that) {
		if (this != &that) {
			T const* p = that.data();
			for (auto it = std::begin(data_); it != std::end(data_); ++it) {
				*it = *p;
				if (*p) 
					++p;
			}
		}
		return *this;
	}
		
template <unsigned N, typename T>
	inline charbuf<N,T>& charbuf<N,T>::operator=(T const* p) {
		if (p != data_) {
			if (p == nullptr) 
				p = "";
			for (auto it = std::begin(data_); it != std::end(data_); ++it) {
				*it = *p;
				if (*p) 
					++p;
			}
		}
		return *this;
	}

template <unsigned N, typename T>
	inline T* charbuf<N,T>::data() {
		return data_;
	}

template <unsigned N, typename T>
	inline T const* charbuf<N,T>::data() const {
		return data_;
	}

template <unsigned N, typename T>
	inline size_t charbuf<N,T>::hash1() const {
		return hash_range(std::begin(data_), std::end(data_));
	}

template <unsigned N, typename T>
	inline size_t charbuf<N,T>::hash2() const {//djb2 algorithm
		size_t hash = 5381;
		for (T const* it=std::begin(data_); it != std::end(data_); ++it) {
			hash = (hash << 6) + hash + (*it); /* hash * 33 + c */
		}
		return hash;
	}

	template <unsigned N, typename T>
	inline charbuf<N,T>::operator size_t () const {
		return hash1();
	}

template <unsigned N, typename T>
	inline bool charbuf<N,T>::operator==(charbuf const& that) const {
		return strcmp(this->data_, that.data_) == 0;
	}

template <unsigned N, typename T>
	inline bool charbuf<N,T>::operator<(charbuf const& that) const {
		return strcmp(this->data_, that.data_) < 0;
	}

template <unsigned N, typename T>
	inline size_t charbuf<N,T>::capacity() const {
		return N;
	}

# endif