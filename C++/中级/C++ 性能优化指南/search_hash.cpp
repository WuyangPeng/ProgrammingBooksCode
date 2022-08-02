# include <iostream>		//  for std::cout
# include <string>			//	for std::string
# include <unordered_map>	//	for std::unordered_map
# include "charbuf.h"		//	for charbuf
# include "stopwatch03.h"	//  stopwatch class

struct kv { // (key,value) pairs
    char const* key;
    unsigned    value;
};

static kv names[] = {
	{ "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",   24 },
    { "yankee", 25 },   { "zulu",   26 }
};
static kv test[] = {
	{ "adam",     0 },	{ "boy",     0 },	{ "charles", 0 },	{ "david",   0 },
	{ "ebenezer", 0 },	{ "ferris",  0 },	{ "george",  0 },	{ "henry",   0 },
	{ "ida",      0 },	{ "john",	 0 },	{ "karl",    0 },	{ "laurence",0 },
	{ "mary",	  0 },	{ "nora",    0 },	{ "ocean",   0 },	{ "panda",   0 },
	{ "quakka",   0 },	{ "robert",  0 },	{ "sam",     0 },	{ "tangle",  0 },
	{ "unice",    0 },	{ "vassily", 0 },	{ "waldo",   0 },	{ "xavier",  0 },
	{ "yabba",    0 },	{ "zebra",   0 },	{ "zymergy", 0 }
	,
	{ "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",   24 },
    { "yankee", 25 },   { "zulu",   26 }
};

//	free function for hashing a struct charbuf
inline size_t hash_charbuf(charbuf<> const& cb) {
	return (size_t)cb;
}

//	free function for hashing a char* string
inline size_t hash_charstar(char const* p) {
	size_t hash = 0;
	for (; *p; ++p)
		hash_combine(hash, *p);
	return hash;
}

// function object for hashing a char* string
struct hash_c_string {
	std::size_t operator() (char const* p) const {
		size_t hash = 0;
		for (; *p; ++p)
			hash_combine(hash, *p);
		return hash;
	}
};

// function object compares two char* strings for equality
struct comp_c_string {
	bool operator()(char const* p1, char const* p2) const {
		return strcmp(p1,p2) == 0;
	}
};

int test_hashes(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    case 1:
        {
		}
        break;

	case 2:
		{// hash<string>
			std::unordered_map<std::string, unsigned> table;
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;

            Stopwatch st("unordered_map<string>");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		{// hash<charbuf> operator size_t
			std::unordered_map<charbuf<>, unsigned> table;
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;

            Stopwatch st("unordered_map<charbuf> operator size_t");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		{// hash<charbuf, hash> function object
			struct hash_charbuf {
				size_t operator()(charbuf<> const& cb) const {
					return (size_t) cb;
				}
			};
			std::unordered_map<charbuf<>, unsigned, hash_charbuf> table;
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;

            Stopwatch st("unordered_map<charbuf, hash> function object");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		{// hash<charbuf, hash> lambda
			auto hashme = [](charbuf<> const& cb) { return (size_t)cb; };
			std::unordered_map<charbuf<>, unsigned, decltype(hashme)> table(50, hashme);
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;

            Stopwatch st("unordered_map<charbuf, hash> lambda");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		{// hash<charbuf, hash> free function
			std::unordered_map<charbuf<>, unsigned, size_t (*)(charbuf<> const&)> table(50, hash_charbuf);
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;

            Stopwatch st("unordered_map<charbuf, hash> free function");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}

		{//	hash<char const*, hash> function object
			std::unordered_map<char const*, unsigned, hash_c_string, comp_c_string> table;
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;
			
            Stopwatch st("unordered_map<char*, hash> function object");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		{//	hash<char const*, hash> lambda
			auto hashlambda = [](char const* p) -> size_t {
				size_t hash = 0;
				for (; *p; ++p)
					hash_combine(hash, *p);
				return hash;
			};
			std::unordered_map<char const*, unsigned, decltype(hashlambda), comp_c_string> table(100, hashlambda);
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;
			
            Stopwatch st("unordered_map<char*, hash> lambda");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		{//	hash<char const*, hash> free function
			std::unordered_map<char const*, unsigned, size_t (*)(char const*), comp_c_string> table(100, hash_charstar);
			for (auto it = names; it != std::end(names); ++it)
				table[it->key] = it->value;
			
            Stopwatch st("unordered_map<char*, hash> free function");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    auto it = table.find(test[i].key);
		}
		break;

    case 0: return 2;
    default:return -1;
    }
    return (rc) ? 1 : 0;
}
