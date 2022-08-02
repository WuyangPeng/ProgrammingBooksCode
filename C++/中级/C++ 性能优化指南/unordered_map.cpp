# include <iostream>		//	for C++ standard I/O
# include <vector>			//  unordered_map is loaded from a vector
# include <unordered_map>	//  container whose performance is being measured
# include "charbuf.h"		//  simple container for a char[] string
# include "kvstruct.h"		//  key/value type with char[] keys, unsigned value
# include "Stopwatch03.h"	//	stopwatch class

//  show properties of an std::unordered_map
template<typename T> void hash_stats(T const& table) {
	unsigned zeros = 0;
	unsigned ones  = 0;
	unsigned many  = 0;
	unsigned many_sigma = 0;
	for (unsigned i = 0; i < table.bucket_count(); ++i) {
		unsigned how_many_this_bucket = 0;
		for (auto it = table.begin(i); it != table.end(i); ++it) {
			how_many_this_bucket += 1;
		}
		switch(how_many_this_bucket) {
		case 0:
			zeros += 1;
			break;
		case 1:
			ones  += 1;
			break;
		default:
			many += 1;
			many_sigma += how_many_this_bucket;
			break;
		}
	}
	std::cout << "unordered_map with " << table.size() << " entries" << std::endl
			  << "    " << table.bucket_count() << " buckets"
			  << " load factor " << table.load_factor() 
			  << ", max load factor " << table.max_load_factor() << std::endl;
	if (ones > 0 && many > 0)
		std::cout << "    " << zeros << " empty buckets, "
				  << ones << " buckets with one entry, "
				  << many << " buckets with multiple entries, " << std::endl;
	if (many > 0)
		std::cout << "    average length of multi-entry chain " << ((float) many_sigma) / many << std::endl;
}

// performance tests for std::unordered_map
bool test_unordered_map(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
	bool rc = true;
	const size_t nelts = random_vector.size();
	std::cout << std::endl << "std::unordered_map " << random_vector.size() << " entries" << std::endl
			  << "multiplier == " << multiplier << std::endl << std::endl;

	struct hash_charbuf {
		size_t operator()(charbuf<9> const& cb) const {
			return (size_t) cb;
		}
	};
	typedef std::unordered_map<charbuf<9>, unsigned, hash_charbuf> ContainerT;
	typedef ContainerT::value_type value_type;
	ContainerT random_container;

	for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
		random_container.insert(random_container.end(), value_type(it->key, it->value));
	rc &= (random_container.size() == nelts);

//	unordered_map insert amd delete
	{
		Stopwatch::tick_t begin_ticks = 0;
		Stopwatch::tick_t assign_ticks = 0;
		Stopwatch::tick_t assign_x_1000 = 0;
		Stopwatch::tick_t delete_x_1000 = 0;
		{	Stopwatch sw("assign unordered_map to unordered_map + delete x multiplier");
			ContainerT test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container = random_container;
				assign_ticks = sw.Show("");
				assign_x_1000 += assign_ticks - begin_ticks;
				test_container.clear();
				begin_ticks = sw.Show("");
				delete_x_1000 += begin_ticks - assign_ticks;
			}
		}
		std::cout << "    assign " 
				    << Stopwatch::GetMs(assign_x_1000) << "mS" 
					<< " + delete " 
				    << Stopwatch::GetMs(delete_x_1000) << "mS" 
					<< " == " << Stopwatch::GetMs(assign_x_1000 + delete_x_1000) 
					<< "mS" << std::endl;

		{   
			ContainerT test_container;
			for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
				test_container.insert(value_type(it->key, it->value));
			std::cout << "test container, no optimization. ";
			hash_stats(test_container);
		}
		{   
			ContainerT test_container;
		    test_container.max_load_factor(2.0f);
			for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
				test_container.insert(value_type(it->key, it->value));
			std::cout << "initially set to 100k buckets. ";
			hash_stats(test_container);
		}
		{   
			ContainerT test_container;
			test_container.rehash(random_vector.size());
			for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
				test_container.insert(value_type(it->key, it->value));
			std::cout << "initially set to 100k buckets. ";
			hash_stats(test_container);
		}

		{   Stopwatch sw("vector iterator insert into unordered_map + delete x multiplier");
			ContainerT test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(value_type(it->key, it->value));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector iterator insert into unordered_map w/ pre-allocation + delete x multiplier");
			ContainerT test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container.rehash(random_vector.size()*5);
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(value_type(it->key, it->value));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector iterator insert into unordered_map w/ max 0.8 + delete x multiplier");
			ContainerT test_container;
			test_container.max_load_factor(0.5f);
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container.rehash(random_vector.size()*5);
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(value_type(it->key, it->value));
				test_container.max_load_factor(1.0);
				test_container.rehash(1);
				test_container.clear();
			}
		}
	}

	ContainerT test_container = random_container;
//	unordered_map traversal
	{
		unsigned long long sum;
		sum = 0;
		{   Stopwatch sw("traverse unordered_map (iterator) x multiplier");
			for (unsigned j = 0; j < multiplier; ++j)
				for (auto it = test_container.begin(); it != test_container.end(); ++it)
					sum += it->second;
		}
		rc &= (sum != 0);
	}

//	unordered_map lookup
	{	
		ContainerT test_container;
		for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
			test_container.insert(value_type(it->key, it->value));
		hash_stats(test_container);
		{	Stopwatch sw("unordered_map lookup x 100");
			for (unsigned j = 0; j < 100; ++j)
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it) {
					rc &= (test_container.find(it->key) != test_container.end());
					if (test_container.find(it->key) == test_container.end())
						std::cout << "error on key " << it->key << std::endl;
				}
		}
		test_container.clear();
		test_container.rehash(random_vector.size());
		for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
			test_container.insert(value_type(it->key, it->value));
		hash_stats(test_container);
		{	Stopwatch sw("unordered_map lookup, preallocated table x 100");
			for (unsigned j = 0; j < 100; ++j)
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it) {
					rc &= (test_container.find(it->key) != test_container.end());
					if (test_container.find(it->key) == test_container.end())
						std::cout << "error on key " << it->key << std::endl;
				}
		}
	}

	return rc;
}
