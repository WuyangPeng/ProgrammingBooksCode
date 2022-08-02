#ifndef VIDEO_CLASS
#define VIDEO_CLASS

#include <iostream>
#include <string>

using namespace std;

class video
{
	public:
		// constructor. initialize film title and numCopies
		video(const string& film = "", int copies = 1):
			filmTitle(film), numCopies(copies)
		{}

		// add n to the number of copies. note that if n < 0
		// the function decreases the number of copies
		void updateCopies(int n)
		{
			numCopies += n;
		}
		
		// return the number of copies of the film title
		int getCopies()
		{
			return numCopies;
		}
		
		// two video objects are "equal" if they have the same title
		friend bool operator== (const video& lhs, const video& rhs)
		{
			return lhs.filmTitle == rhs.filmTitle;
		}

		// compare video objects by comparing film titles
		friend bool operator< (const video& lhs, const video& rhs)
		{
			return lhs.filmTitle < rhs.filmTitle;
		}

		// output a video object
		friend ostream& operator<< (ostream& ostr, const video& obj)
		{ 
			ostr << obj.filmTitle << " (" << obj.numCopies << ")" ;
			return ostr;
		}
	private:
		// title of the film
		string filmTitle;
		// number of copies (>= 0)
		int numCopies;
};

#endif	// VIDEO_CLASS
