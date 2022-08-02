# include <iostream>		//  for std::cout
# include <string>			//	for std::string
# include <algorithm>		//	find, binary_search, equal_range, 
# include "stopwatch03.h"	//  stopwatch class
# include "arrayiterator.h"	//	size() definition

struct kv { // (key,value) pairs
    char const* key;
    unsigned    value;
};

static kv table[] = {
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

//	needed for std::lower_bound
static inline bool operator<(kv const& n1, char const* key) {
	return strcmp(n1.key, key) < 0;
}
static inline bool operator<(char const* key, kv const& n2) {
	return strcmp(key, n2.key) < 0;
}
static inline bool operator<(kv const& n1, kv const& n2) {
	return strcmp(n1.key, n2.key) < 0;
}
//  needed for std::find
static inline bool operator==(kv const& n1, char const* n2) {
	return strcmp(n1.key, n2) == 0;
}
static inline bool operator==(kv const& n1, kv const& n2) {
	return strcmp(n1.key, n2.key) == 0;
}

kv names[] = {// in alphabetical order
    { "alpha",   1 },   { "bravo",   2 },   { "charlie", 3 },   { "delta",  4 },
    { "echo",    5 },   { "foxtrot", 6 },   { "golf",    7 },   { "hotel",  8 },
    { "india",   9 },   { "juliet", 10 },   { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 },  { "oscar",  15 },   { "papa",   16 },
    { "quebec", 16 },   { "romeo",  18 },   { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },   { "whiskey",23 },   { "xray",  24 },
    { "yankee", 25 },   { "zulu",   26 }
};

//	find algorithm, specialized for struct kv
kv* find_unwrapped(kv* first, kv* last, char const* key) {
	while (first != last) {
		if (*first == key)
			return first;
		++first;
    }
    return last;
}

//	find optimization for use when the range is known to be sorted
kv* find_sorted(kv* first, kv* last, char const* key) {
	while (first != last) {
        int rc = strcmp(first->key, key);
		if (rc < 0) {
			++first;
			continue;
		}
		if (rc == 0)
			return first;
		break;
    }
    return last;
}

//  binary search using strcmp() to divide range into 3 parts
kv* find_binary_3way_size(char const* k, kv* table, unsigned size) {
    unsigned mid;
    int      rc;
    while (size > 0) {
        mid = size/2;
        rc = strcmp(k, table[mid].key);
        if (rc < 0)         //  k < table[mid], search left half
        {
            size = mid;
        }
        else if (rc > 0)    //  k > table[mid], search right half
        {
            table = &table[mid+1];
            size -= mid + 1;
        }
        else // (rc == 0)    //  k == table[mid]
        {
            return &table[mid];
        }
    }
    return nullptr;
}

//  binary search using strcmp() to divide range into 3 parts, same API as find()
kv* find_binary_3way(kv* start, kv* end, char const* key) {
	auto stop = end;
	while (start < stop) {
		auto mid = start + (stop-start)/2;
		auto rc = strcmp(mid->key, key);
		if (rc > 0) {// mid->key > key, search left half
			stop = mid;
		}
		else if (rc < 0) {// mid->key < key, search right half
			start = mid + 1;
		}
		else {
			return mid;
		}
	}
	return end;
}

//  binary search using only "less" relation
kv* find_binary_lessthan_size(char const* k, kv* table, unsigned size) {
    int mid;
    while (size > 1) {
        mid = size/2;
        if (strcmp(k, table[mid].key) < 0)
        {// k < table[mid], search left half
            size = mid;
        }
        else
        {// k >= table[mid], search right half
            table = &table[mid];
            size -= mid;
        }
    }
    return strcmp(k, table->key) ? nullptr : table;
}

//  binary search using only "less" relation, same API as find()
kv* find_binary_lessthan(kv* start, kv* end, char const* key) {
	kv* stop = end;
	while (start < stop) {
		auto mid = start + (stop - start) / 2;
		if (*mid < key) {// search right half [mid,stop)
			start = mid + 1;
		}
		else {// search left half [start,mid)
			stop = mid;
		}
	}
	return (start == end || key < *start) ? end : start;
}

unsigned hash(char const* key) {
	if (key[0] < 'a' || key[0] > 'z')
		return 0;
	return (key[0]-'a');
}

kv* find_hash(kv* first, kv* last, char const* key) {
	unsigned i = hash(key);
	return strcmp(first[i].key, key) ? last : first + i;
}

bool test_result(kv const* result, 
				 kv const* end, 
				 kv const* test,
				 unsigned idx,
				 char const* name) {

    bool rc = true;
	if (result == end)
		rc &= test[idx].value == 0;
	else
		rc &= strcmp(test[idx].key, result->key) == 0;
	if (!rc) std::cout << name << " test " << idx << " failed" << std::endl;
	return rc;
}

int test_algorithms(int test_no, unsigned long multiplier) {
    bool rc = true;
    kv* volatile kp;
    switch (test_no) {
    case 1:
        {
			for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = std::find(std::begin(names), std::end(names), test[i].key);

				rc &= test_result(kp, std::end(names), test, i, "std::find()");
			}

			for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = find_unwrapped(std::begin(names), std::end(names), test[i].key);

				rc &= test_result(kp, std::end(names), test, i, "find_unwrapped()");
			}

			for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = find_sorted(std::begin(names), std::end(names), test[i].key);

				rc &= test_result(kp, std::end(names), test, i, "find_sorted()");
            }

            for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = find_binary_3way(std::begin(names), std::end(names), test[i].key);

				rc &= test_result(kp, std::end(names), test, i, "find_binary_3way()");
            }

            for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = find_binary_lessthan(std::begin(names), std::end(names), test[i].key);

				rc &= test_result(kp, std::end(names), test, i, "find_binary_lessthan()");
            }

			for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = find_binary_3way_size(test[i].key, names, std::size(names));

				rc &= test_result(kp, nullptr, test, i, "find_binary_3way_size()");
            }

			for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = find_binary_lessthan_size(test[i].key, names, std::size(names));

				rc &= test_result(kp, nullptr, test, i, "find_binary_lessthan_size()");
            }

			for (unsigned i = 0; i < std::size(test); ++i) {
				auto kp = std::lower_bound(std::begin(names), std::end(names), test[i].key);
				if ((kp < std::end(names)) && (test[i] < kp->key))
					kp = std::end(names);

				rc &= test_result(kp, std::end(names), test, i, "std::lower_bound()");
            }

			for (unsigned i = 0; i < std::size(test); ++i) {
				kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
				auto kp2 = std::upper_bound(std::begin(names), std::end(names), test[i].key);
				if (kp == kp2)
					kp = std::end(names);

				rc &= test_result(kp, std::end(names), test, i, "lower_bound/upper_bound 1");
	        }

			for (unsigned i = 0; i < std::size(test); ++i) {
				kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
				auto kp2 = std::upper_bound(kp, std::end(names), test[i].key);
				if (kp == kp2)
					kp = std::end(names);

				rc &= test_result(kp, std::end(names), test, i, "lower_bound/upper_bound 2");
	        }

            for (unsigned i = 0; i < std::size(test); ++i) {
				auto res = std::equal_range(std::begin(names), std::end(names), test[i].key);
				if (res.first == res.second)
					res.first = std::end(names);

				rc &= test_result(res.first, std::end(names), test, i, "std::equal_range()");
			}

            for (unsigned i = 0; i < std::size(test); ++i) {
				kp = find_hash(std::begin(names), std::end(names), test[i].key);

				rc &= test_result(kp, std::end(names), test, i, "find_hash()");
			}
		}
        break;

	case 2:
		{// linear search using std::find
			Stopwatch sw("std::find()");
             for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = std::find(std::begin(names), std::end(names), test[i].key);
        }
		{// linear search using the find algorithm
			Stopwatch sw("find_unwrapped()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_unwrapped(std::begin(names), std::end(names), test[i].key);
        }
        {// linear search of a sorted table
            Stopwatch sw("find_sorted()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_sorted(std::begin(names), std::end(names), test[i].key);
        }
        break;

	case 3:
		{// std::binary_search
            Stopwatch st("std::binary_search()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					auto res = std::binary_search(std::begin(names), std::end(names), test[i].key);
					kp = &names[res ? 0 : 1];
				}
		}
		{//	std::equal_range for binary search.
            Stopwatch st("std::equal_range()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					auto res = std::equal_range(std::begin(names), std::end(names), test[i].key);
					kp = (res.first == res.second) ? std::end(names) : res.first;
				}
		}
		{//	std::lower_bound / std::upper_bound for binary search.
            Stopwatch st("std::lower_bound / std::upper_bound test 1");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
					auto kp2 = std::upper_bound(std::begin(names), std::end(names), test[i].key);
					kp = (kp == kp2) ? std::end(names) : kp;
				}
		}
		{//	std::lower_bound / std::upper_bound for binary search.
            Stopwatch st("std::lower_bound / std::upper_bound test 2");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					kp       = std::lower_bound(std::begin(names), std::end(names), test[i].key);
					auto kp2 = std::upper_bound(kp,    std::end(names), test[i].key);
					kp = (kp == kp2) ? std::end(names) : kp;
				}
		}
		{//	std::lower_bound for binary search.
            Stopwatch st("std::lower_bound()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i) {
					kp = std::lower_bound(std::begin(names), std::end(names), test[i].key);
					if (kp != std::end(names) && test[i] < kp->key)
						kp = std::end(names);
				}
		}
		{//	custom binary search using <
            Stopwatch st("find_binary_lessthan()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
					kp = find_binary_lessthan(std::begin(names), std::end(names), test[i].key);
		}
		{//	custom binary search using strcmp().
            Stopwatch st("find_binary_3way()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
					kp = find_binary_3way(std::begin(names), std::end(names), test[i].key);
		}
        {
            Stopwatch st("find_binary_lessthan_size()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_binary_lessthan_size(test[i].key, names, std::size(names));
        }
        {
            Stopwatch sw("find_binary_3way_size()");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_binary_3way_size(test[i].key, names, std::size(names));
        }
		break;

	case 4:
		{
            Stopwatch st("find_hash");
            for (unsigned long j = 0; j < multiplier; ++j)
                for (unsigned i = 0; i < std::size(test); ++i)
                    kp = find_hash(std::begin(names), std::end(names), test[i].key);
		}
		break;

    case 0: return 4;
    default:return -1;
    }
    return (rc) ? 1 : 0;
}