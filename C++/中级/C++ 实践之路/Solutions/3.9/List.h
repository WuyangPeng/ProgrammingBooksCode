#if !defined LIST_H
#define LIST_H

class DLink
{
public:
	DLink (int id) 
		:_pPrev (this), _pNext (this), _id (id) {}
	int     Id () const { return _id; }
	DLink const *  Next () const { return _pNext; }
	DLink *  Next () { return _pNext; }
	void SetNext (DLink * next) { _pNext = next; }
	DLink const *  Prev () const { return _pPrev; }
	DLink *  Prev () { return _pPrev; }
	void SetPrev (DLink * prev) { _pPrev = prev; }
	void Unlink ();
private:
	int		 _id;
	DLink *  _pPrev;
	DLink *  _pNext;
};

class List
{
public:
	List (): _pHead (0) {}
	~List ();
	void Put (int id);
	int Get ();
	DLink const * GetHead () const { return _pHead; }
private:
	DLink * _pHead;
};

#endif