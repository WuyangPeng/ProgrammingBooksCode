#if !defined (LIST_H)
#define LIST_H
// (c) Bartosz Milewski 2000
#include <new>

class LinkAllocator;

class List
{
public:
	List ();
	~List ();
	void Add (int value);
public:
	class Link
	{
	public:
		Link (Link* pNext, int value = -1) 
			: _pNext (pNext), _value (value) {}
		Link *  Next () const { return _pNext; }
		void	SetNext (Link * next) { _pNext = next; }
		int     GetValue () const { return _value; }
		// allocator
		void * operator new (std::size_t size);
		void operator delete (void * mem);
		static void Purge ();
	private:
		static LinkAllocator _linkAlloc;

		int		_value;
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

class LinkAllocator
{
	enum { BlockLinks = 4 }; // small value for testing
	class Block
	{
	public:
		Block (Block * next): _next (next) {}
		Block * Next () { return _next; }
	private:
		Block * _next;
	};
public:
	LinkAllocator () : _p (0), _blocks (0) {}
	~LinkAllocator () { Purge (); }
	void Purge ();
	void * NewLink ();
	void Recycle (void * link);
private:
	List::Link  * _p;
	Block * _blocks;
};

#endif
