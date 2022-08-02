# include <iostream>		//	for C++ standard I/O
# include <algorithm>		//	for std::sort, std::lower_bound
# include <vector>			//	input vector
# include "Stopwatch03.h"	//	stopwatch class
# include <deque>			//	the data structure under test
# include "kvstruct.h"		//	the element type

bool test_deque(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
	bool rc = true;
	const size_t nelts = random_vector.size();
	std::cout << std::endl << "std::deque " << random_vector.size() << " entries" << std::endl << std::endl;
	std::deque<kvstruct> random_container;

//	deque insert and delete
	{
		std::cout << "multiplier == " << multiplier << std::endl;

		random_container.insert(random_container.end(), random_vector.begin(), random_vector.end());

		{	Stopwatch sw("assign deque to deque + delete x multiplier");
		    Stopwatch::tick_t begin_ticks = 0;
			Stopwatch::tick_t assign_ticks = 0;
			Stopwatch::tick_t assign_x_1000 = 0;
			Stopwatch::tick_t delete_x_1000 = 0;
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container = random_container;
				assign_ticks = sw.Show("");
				assign_x_1000 += assign_ticks - begin_ticks;
				test_container.clear();
				begin_ticks = sw.Show("");
				delete_x_1000 += begin_ticks - assign_ticks;
			}
			std::cout << "    assign " 
				      << Stopwatch::GetMs(assign_x_1000) << "mS" 
					  << " + delete " 
				      << Stopwatch::GetMs(delete_x_1000) << "mS" 
					  << " == " << Stopwatch::GetMs(assign_x_1000 + delete_x_1000) 
					  << "mS" << std::endl;
		}

		{   Stopwatch sw("vector iterator insert(end()) + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container.insert(test_container.end(), random_vector.begin(), random_vector.end());
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator push_back() + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)	
					test_container.push_back(*it);
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector.at() push_back() + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_back(random_vector.at(i));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector[] push_back() + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_back(random_vector[i]);
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator push_front() + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)	
					test_container.push_front(*it);
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector.at() push_front() + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_front(random_vector.at(i));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector[] push_front() + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_front(random_vector[i]);
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator insert at back + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(test_container.end(), *it);
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector.at() insert at end + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.end(), random_vector.at(i));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector[] insert at end + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.end(), random_vector[i]);
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator insert at front + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(test_container.begin(), *it);
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector.at() insert at front + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.begin(), random_vector.at(i));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector[] insert at frone + delete x multiplier");
			std::deque<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.begin(), random_vector[i]);
				test_container.clear();
			}
		}
	}

//	deque traversal
	{
		std::deque<kvstruct> test_container;
		test_container.insert(test_container.end(), random_vector.begin(), random_vector.end());
		long long sum;
		sum = 0;
		{	Stopwatch sw("traverse deque (at) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (unsigned i = 0; i < nelts; ++i)
					sum += test_container.at(i).value;
		}
		rc &= (sum != 0);
		sum = 0;
		{	Stopwatch sw("traverse deque (subscript) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (unsigned i = 0; i < nelts; ++i)
					sum += test_container[i].value;
		}
		rc &= (sum != 0);
		sum = 0;
		{   Stopwatch sw("traverse deque (iterator) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (auto it = test_container.begin(); it != test_container.end(); ++it)
					sum += it->value;
		}
		rc &= (sum != 0);

//		{   Stopwatch sw("traverse deque (iterator) x 1000");
//			auto lastit = sorted_deque.end();
//			auto it     = sorted_deque.end();
//			for (unsigned j = 0; j < 1000; ++j)
//				for (lastit = sorted_deque.begin(), it = ++sorted_deque.begin(); it != sorted_deque.end(); ++it, ++lastit)
//					rc &= (lastit->key < it->key);
//		}
	}

//	deque sort
	{
		std::deque<kvstruct> sorted_container;
		{	Stopwatch sw("std::sort() deque + build + delete x 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container = random_container;
				std::sort(sorted_container.begin(), sorted_container.end());
			}
		}
		{	Stopwatch sw("std::sort() sorted deque x 100");
			for (unsigned j = 0; j < 100; j++) {
				std::sort(sorted_container.begin(), sorted_container.end());
			}
		}
		rc &= (sorted_container.size() == random_vector.size());

	//	std::stable_sort deque

		{	Stopwatch sw("std::stable_sort() deque + build + delete x 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container = random_container;
				std::stable_sort(sorted_container.begin(), sorted_container.end());
			}
		}
		{	Stopwatch sw("std::stable_sort() sorted deque x 100");
			for (unsigned j = 0; j < 100; j++) {
				std::stable_sort(sorted_container.begin(), sorted_container.end());
			}
		}
		rc &= (sorted_container.size() == random_vector.size());
	}

//	lookup
	{
		std::deque<kvstruct> sorted_container;
		sorted_container = random_container;
		std::sort(sorted_container.begin(), sorted_container.end());

		Stopwatch sw("lookup in sorted vector x 100");
		unsigned const testsize = nelts;

		std::deque<kvstruct>::iterator kp;
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
