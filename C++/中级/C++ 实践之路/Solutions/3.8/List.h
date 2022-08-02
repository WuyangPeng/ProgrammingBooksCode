#if !defined LIST_H
#define LIST_H

class Link
{
public:
	Link (Link* pNext, int id) 
		: _pNext (pNext), _id (id) {}
	Link const *  Next () const { return _pNext; }
	Link *  Next () { return _pNext; }
	void SetNext (Link * next) { _pNext = next; }
	int     Id () const { return _id; }
private:
	int     _id;
	Link *  _pNext;
};

class List
{
	friend class UnlinkSeq;
public:
	List (): _pHead (0) {}
	~List ();
	void Add (int id);
	Link const * GetHead () const { return _pHead; }
private:
	Link * _pHead;
};

class ListSeq
{
public:
	ListSeq (List const & list)
		: _link (list.GetHead ())
	{}
	bool AtEnd () const { return _link == 0; }
	void Advance () { _link = _link->Next (); }
	int Id () const { return _link->Id (); }
private:
	Link const * _link;
};

class UnlinkSeq
{
public:
	UnlinkSeq (List & list)
		: _list (list),
		  _cur (list._pHead),
		  _prev (0)
	{}
	bool AtEnd () const { return _cur == 0; }
	void Advance ()
	{
		_prev = _cur;
		_cur = _cur->Next ();
	}
	int Id () const { return _cur->Id (); }
	void Unlink ();
private:
	List & _list;
	Link * _cur;
	Link * _prev;
};


#endif