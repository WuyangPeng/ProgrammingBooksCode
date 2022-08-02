# include <iostream>		//	for C++ standard I/O
# include <random>			//	to create random vectors
# include <functional>      //  for std::bind, used in random engine
# include <algorithm>       //  for sort
# include <vector>			//	we create a vector of 100,000 random kvstructs
# include <set>				//	used to test uniqueness of vector entries
# include "kvstruct.h"		//	key/value table with char[] key, unsigned value
# include "test_driver.h"	//	module test driver

//	build count-element vector containing unique random strings
void build_random_vector(std::vector<kvstruct>& v, unsigned count) {
	std::set<unsigned> unique;
    std::default_random_engine e;
    std::uniform_int_distribution<unsigned> d(count, 10*count);
    auto randomizer = std::bind(d,e);
    v.clear();
    while (v.size() < count) {
		unsigned rv = randomizer();
		if (unique.insert(rv).second == true) {	// new item inserted
			kvstruct keyvalue(rv);
	        v.push_back(keyvalue);
		}
	}
}

//  external declarations: container test drivers
bool test_vector(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_deque(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_list(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_forward_list(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_map(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_unordered_map(std::vector<kvstruct> const& random_vector, unsigned long multiplier);

int test_stl(int test_no, unsigned long multiplier) {
    bool rc = true;
	unsigned long table_size = 100000;
	
    switch(test_no) {
    default:return -1;
    case 0: return 2;
    case 1: {//	basic smoke test to see if things are working
		//	test my stringify implementation
		    char buf[9];
		    rc &= (strcmp(kvstruct::stringify(0, buf), "0") == 0);
            rc &= (strcmp(kvstruct::stringify(0x123, buf),  "123") == 0);
            rc &= (strcmp(kvstruct::stringify(0x1000, buf), "1000") == 0);
            rc &= (strcmp(kvstruct::stringify(0xffffffff, buf), "FFFFFFFF") == 0);

		//	test that build_random_vector items are unique
            std::vector<kvstruct> rnd_vector;
            build_random_vector(rnd_vector, 100);
			std::sort(rnd_vector.begin(), rnd_vector.end());
			for (unsigned i = 1; i < rnd_vector.size(); ++i)
				rc &= (rnd_vector[i-1].key < rnd_vector[i].key);
        }
        break;

    case 2: 
		{
			std::vector<kvstruct> rnd_vector;
			build_random_vector(rnd_vector, table_size);

			rc &= test_vector(rnd_vector, multiplier);
			rc &= test_deque(rnd_vector, multiplier);
			rc &= test_list(rnd_vector, multiplier);
			rc &= test_forward_list(rnd_vector, multiplier);
			rc &= test_map(rnd_vector, multiplier);
			rc &= test_unordered_map(rnd_vector, multiplier);
        }
		break;
    }
    return rc ? 1 : 0;
}

//  external declarations: search test drivers
int test_algorithms(int, unsigned long);
int test_maps(int, unsigned long);
int test_hashes(int, unsigned long);

int (*func[])(int, unsigned long) = {
//    test_stl,
	test_algorithms,
//	test_maps,
//	test_hashes,
	0
};

int main(int argc, char** argv) {
	test_driver(func, argc, argv);
	return 0;
}