# include <iostream>		//	for C++ standard I/O
# include <algorithm>		//	for std::sort, std::lower_bound
# include "Stopwatch03.h"	//	stopwatch class
# include <vector>			//	the data structure under test
# include "kvstruct.h"		//	the element type

bool test_vector(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
	bool rc = true;
	const size_t nelts = random_vector.size();
	std::cout << std::endl << "std::vector " << random_vector.size() << " entries" << std::endl << std::endl;

//	vector insert amd delete
	{
		{	Stopwatch sw("assign vector to vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container = random_vector;
				std::vector<kvstruct>().swap(test_container);
			}
		}
		{	Stopwatch sw("assign vector to vector", false);
		    Stopwatch::tick_t ticks;
			Stopwatch::tick_t assign_x_1000 = 0;
			Stopwatch::tick_t delete_x_1000 = 0;
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				sw.Start("");
				test_container = random_vector;
				ticks = sw.Show("");
				assign_x_1000 += ticks;

				std::vector<kvstruct>().swap(test_container);
				delete_x_1000 += sw.Stop("") - ticks;
			}
			std::cout << "    assign vector to vector x 1000: " 
				      << Stopwatch::GetMs(assign_x_1000) << "mS" << std::endl;
			std::cout << "    vector delete x 1000: " 
				      << Stopwatch::GetMs(delete_x_1000) << "mS" << std::endl;
		}

		{   Stopwatch sw("vector iterator insert(begin()) vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				test_container.insert(test_container.begin(), random_vector.begin(), random_vector.end());
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("same, only with reserve");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				test_container.reserve(nelts);
				test_container.insert(test_container.begin(), random_vector.begin(), random_vector.end());
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector iterator insert(end()) vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				test_container.insert(test_container.end(), random_vector.begin(), random_vector.end());
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector iterator push_back() to vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)	
					test_container.push_back(*it);
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("same, only with reserve");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				test_container.reserve(nelts);
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)	
					test_container.push_back(*it);
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector.at() push_back() to vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_back(random_vector.at(i));
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector[] push_back() to vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_back(random_vector[i]);
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector iterator insert at back to vector + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(test_container.end(), *it);
				std::vector<kvstruct>().swap(test_container);
			}
		}
		{   Stopwatch sw("same, but with reserve");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				test_container.reserve(nelts);
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(test_container.end(), *it);
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector.at() insert at end + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.end(), random_vector.at(i));
				std::vector<kvstruct>().swap(test_container);
			}
		}

		{   Stopwatch sw("vector[] insert at end + delete x 1000");
			std::vector<kvstruct> test_container;
			for (unsigned j = 0; j < 1000; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.end(), random_vector[i]);
				std::vector<kvstruct>().swap(test_container);
			}
		}

		std::vector<kvstruct> test_container;
		{   Stopwatch sw("vector iterator insert at front to vector");
			for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
				test_container.insert(test_container.begin(), *it);
		}
		std::vector<kvstruct>().swap(test_container);
		{   Stopwatch sw("same but with reserve");
		    test_container.reserve(nelts);
			for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
				test_container.insert(test_container.begin(), *it);
		}
		std::vector<kvstruct>().swap(test_container);

		{   Stopwatch sw("vector.at() insert at front");
			for (unsigned i = 0; i < nelts; ++i)
				test_container.insert(test_container.begin(), random_vector.at(i));
		}
		std::vector<kvstruct>().swap(test_container);

		{   Stopwatch sw("vector[] insert at front");
			for (unsigned i = 0; i < nelts; ++i)
				test_container.insert(test_container.begin(), random_vector[i]);
		}
	}

//	vector traversal
	{
		long long sum;
		std::vector<kvstruct> test_container = random_vector;

		sum = 0;
		{	Stopwatch sw("traverse vector (at) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (unsigned i = 0; i < nelts; ++i)
					sum += test_container.at(i).value;
		}
		rc &= (sum != 0);
		sum = 0;
		{	Stopwatch sw("traverse vector (subscript), size() x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (unsigned i = 0; i < test_container.size(); ++i)
					sum += test_container[i].value;
		}
		rc &= (sum != 0);
		sum = 0;
		{	Stopwatch sw("traverse vector (subscript) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (unsigned i = 0; i < nelts; ++i)
					sum += test_container[i].value;
		}
		rc &= (sum != 0);
		sum = 0;
		{   Stopwatch sw("traverse vector (iterator) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (auto it = test_container.begin(); it != test_container.end(); ++it)
					sum += it->value;
		}
		rc &= (sum != 0);
	}

//	vector sort
	{
		std::vector<kvstruct> sorted_container;
		sorted_container = random_vector;
		{	Stopwatch sw("std::sort() vector + assign + delete X 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container = random_vector;
				std::sort(sorted_container.begin(), sorted_container.end());
			}
		}
		{	Stopwatch sw("std::sort() sorted vector X 100");
			for (unsigned j = 0; j < 100; j++)
				std::sort(sorted_container.begin(), sorted_container.end());
		}
		rc &= (sorted_container.size() == random_vector.size());

	//	std::stable_sort

		sorted_container = random_vector;
		{	Stopwatch sw("std::stable_sort() vector + assign + delete X 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container = random_vector;
				std::stable_sort(sorted_container.begin(), sorted_container.end());
			}
		}
		{	Stopwatch sw("std::stable_sort() sorted vector X 100");
			for (unsigned j = 0; j < 100; j++)
				std::stable_sort(sorted_container.begin(), sorted_container.end());
		}
		rc &= (sorted_container.size() == random_vector.size());
	}

//	lookup
	{
		std::vector<kvstruct> sorted_container;
		sorted_container = random_vector;
		std::sort(sorted_container.begin(), sorted_container.end());

		Stopwatch sw("lookup in sorted vector x 100");
		unsigned const testsize = nelts;

		std::vector<kvstruct>::iterator kp;
		for (unsigned j = 0; j < 100; ++j) {
			for (auto it = random_vector.begin(); it != random_vector.end(); ++it) {
				kp = std::lower_bound(
							sorted_container.begin(), 
							sorted_container.end(), 
							*it);
				if (kp != sorted_container.end() && *it < *kp)
					kp = sorted_container.end();
			}
			rc &= (kp != sorted_container.end());
		}
	}
	return rc;
}
