#if !defined (LIST_H)
#define LIST_H
// (c) Bartosz Milewski 2000
#include <new>
#include <cassert>

class List
{
	class Link;
	
	class Free
	{
	public:
		Free () : _p (0) {}
		~Free ();
		void Purge ();
		void * NewLink ();
		void Recycle (void * link);
	private:
		Link * _p;
	};
public:
	List ();
	~List ();
	void Add (int value);
private:
	class Link
	{
		friend class Free;
	public:
		Link (Link * pNext, int value)
			: _pNext (pNext), _value (value) {}
		Link *  Next () const { return _pNext; }
		int     GetValue () const { return _value; }
		// allocator
		void * operator new (std::size_t size)
		{
			assert (size == sizeof (Link));
			return _freeList.NewLink ();
		}
		void operator delete (void * mem)
		{
			if (mem)
				_freeList.Recycle (mem);
		}
		static void Purge () { _freeList.Purge (); }
	private:
		static    Free _freeList;
	
		int     _value;
		Link *  _pNext;
	};
public:
	class Seq
	{
	public:
		bool AtEnd () const { return _pLink == 0; }
		void Advance () { _pLink = _pLink->Next (); }
		int GetValue () const { return _pLink->GetValue (); }

	protected:
		Seq (List const & list)
			: _pLink (list.GetHead ()) {}
	private:
		Link const * _pLink; // current link
	};

	friend class Seq;
private:
	Link const * GetHead () const { return _pHead; }
	
	Link * _pHead;
};

#endif
