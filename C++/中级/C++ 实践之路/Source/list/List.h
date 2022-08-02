#if !defined (LIST_H)
#define LIST_H
// (c) Bartosz Milewski 2000

class Link
{
public:
	Link (Link* pNext, int id) 
		: _pNext (pNext), _id (id) {}
	Link *  Next () const { return _pNext; }
	int     Id () const { return _id; }
private:
	int     _id;
	Link *  _pNext;
};

class List
{
public:
	List (): _pHead (0) {}
	~List ();
	void Add ( int id );
	Link const * GetHead () const { return _pHead; }
private:
	Link* _pHead;
};

#endif
