#ifndef MINIPAIR_CLASS
#define MINIPAIR_CLASS

// substitute for the STL miniPair class. used 
// by the miniMap class
template<class T1, class T2>
class miniPair
{
	public:
		T1 first;
		T2 second;
			// public data members

		// default constructor
		miniPair(): first(T1()), second(T2())
		{}

		// constructor that initializes first and second
		miniPair(const T1& v1, const T2& v2):
				first(v1), second(v2)
		{}

		// overload < by comparing the first data members
		friend bool operator< (const miniPair<T1,T2>& lhs, const miniPair<T1,T2>& rhs)
		{
			return lhs.first < rhs.first;
		}

		// overload == by comparing the first data members
		friend bool operator== (const miniPair<T1,T2>& lhs, const miniPair<T1,T2>& rhs)
		{
			return lhs.first == rhs.first;
		}
};

#endif	// MINIPAIR_CLASS
