# include <iostream>		//	for C++ standard I/O
# include <algorithm>		//	for std::sort, std::lower_bound
# include <vector>			//	input vector
# include "Stopwatch03.h"	//	stopwatch class
# include <forward_list>	//	the data structure under test
# include "kvstruct.h"		//	the element type
//# include <list>

bool test_forward_list(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
	bool rc = true;
	const size_t nelts = random_vector.size();
	std::cout << std::endl << "std::forward_list " << random_vector.size() << " entries" << std::endl
			  << "multiplier == " << multiplier << std::endl << std::endl;
	std::forward_list<kvstruct> random_container;

//	list insert and delete
	{
		random_container.insert_after(random_container.before_begin(), random_vector.begin(), random_vector.end());

		{	Stopwatch sw("assign forward_list to forward_list + delete x multiplier");
		    Stopwatch::tick_t begin_ticks = 0;
			Stopwatch::tick_t assign_ticks = 0;
			Stopwatch::tick_t assign_x_1000 = 0;
			Stopwatch::tick_t delete_x_1000 = 0;
			std::forward_list<kvstruct> test_container;
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

		{   Stopwatch sw("vector iterator insert_after(before_begin()) + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				test_container.insert_after(test_container.before_begin(), random_vector.begin(), random_vector.end());
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator push_front() + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)	
					test_container.push_front(*it);
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector.at() push_front() + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_front(random_vector.at(i));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector[] push_front() + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_front(random_vector[i]);
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator insert at front + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert_after(test_container.before_begin(), *it);
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector iterator insert at last position + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				auto place = test_container.before_begin();
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					place = test_container.insert_after(place, *it);
				test_container.clear();
			}
		}

		{   Stopwatch sw("vector.at() insert at front + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert_after(test_container.before_begin(), random_vector.at(i));
				test_container.clear();
			}
		}
		{   Stopwatch sw("vector[] insert at front + delete x multiplier");
			std::forward_list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert_after(test_container.before_begin(), random_vector[i]);
				test_container.clear();
			}
		}
	}

//	traversal
	{
		std::forward_list<kvstruct> test_container;
		unsigned long long sum;
		sum = 0;
		test_container = random_container;
		{   Stopwatch sw("traverse list (iterator) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (auto it = test_container.begin(); it != test_container.end(); ++it)
					sum += it->value;
		}
		rc &= (sum != 0);
	}

//	sort
//	list sort
	{
		std::forward_list<kvstruct> sorted_container;
		{	Stopwatch sw("std::list::sort() list + build + delete x 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container = random_container;
				sorted_container.sort();
			}
		}
		{	Stopwatch sw("std::list::sort() sorted list x 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container.sort();
			}
		}
//		rc &= (sorted_container.size() == random_vector.size());
	}

	return rc;
}
