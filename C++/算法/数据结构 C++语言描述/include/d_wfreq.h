#ifndef WORDFREQ_CLASS
#define WORDFREQ_CLASS

#include <iostream>
#include <string>

// maintains a word and its frequency of occurrence
class wordFreq
{
	public:
		// initialize word and set freq to 1
		wordFreq(const string& str): word(str), freq(1)
		{}

		// add 1 to the frequency
		void increment()
		{ freq++; }

		// equality operator compares the word for the objects
		friend bool operator== (const wordFreq& lhs, const wordFreq& rhs)
		{ return lhs.word == rhs.word; }

		// less than operator compares the word for the objects
		friend bool operator< (const wordFreq& lhs, const wordFreq& rhs)
		{ return lhs.word < rhs.word; }

		// output an object in the format:  word (freq)
		friend ostream& operator<< (ostream& ostr, const wordFreq& w)
		{
			ostr << w.word << " (" << w.freq << ')';
			return ostr;
		}

	private:
		string word;
		// number of times word found
		int freq;
};

#endif	// WORDFREQ_CLASS
