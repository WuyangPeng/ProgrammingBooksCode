# ifndef KVSTRUCT_H
#	define KVSTRUCT_H

// simple, non-template key/value class with char[] keys, unsigned values

struct kvstruct {
    char key[9];
    unsigned value; //  could be anything at all
    kvstruct(unsigned k) : value(k) 
	{ 
		char buf[9];
		strcpy_s(key, stringify(k, buf));
	}

	static char const* stringify(unsigned i, char* buf) {
		buf[8] = 0;
		char* bufp = &buf[8];
		do {
			*--bufp = "0123456789ABCDEF"[i & 0xf];
			i >>= 4;
		} while (i != 0);
		return bufp;
	}

    bool operator<(kvstruct const& that)  const { return strcmp(this->key, that.key) < 0; }
	bool operator==(kvstruct const& that) const { return strcmp(this->key, that.key) == 0; }
};
// static inline bool operator<(kvstruct const& left, kvstruct const& right) { return strcmp(left.key, right.key) < 0; }

# endif