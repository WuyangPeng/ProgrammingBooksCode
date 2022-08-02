#include <iostream>

class Node;
class Preorder;
class Postorder;

class NaryTree {
  public:
	int count()
		{ return size; }
  public:
	Node *root;
	int size;
};

typedef short Index;

class Node {
  public:
	Index parent;
	Index sibling;
	Index lchild;
	// other members...
	int value;
	
	friend class Preorder;
	friend class Postorder;
};

class Preorder {
  public:
	Preorder( NaryTree &t )
		: cur( t.root ), end( t.root+t.count()-1 ) {}
	bool next();
	Node *get()
		{ return cur; }
  private:
	Node *cur, *end;
};

inline bool
Preorder::next() {
	return cur == end
		? 0
		: (++cur, 1);
}

class Postorder {
  public:
	Postorder( NaryTree &t )
		: cur( t.root ), pc( START )
		{ next(); }
	bool next();
	Node *get()
		{ return cur; }
  private:
	Node *cur;
	enum {
		START,
		LEAF,
		INNER,
		DONE
	} pc;
	bool parent()
		{ return cur->parent ? (cur+=cur->parent, true) : false; }
	bool sibling()
		{ return cur->sibling ? (cur+=cur->sibling, true) : false; }
	bool lchild()
		{ return cur->lchild ? (cur+=cur->lchild, true) : false; }
};

bool
Postorder::next() {
   switch( pc )
   case START:
   while( true )
      if( !lchild() ) {
         pc = LEAF;
         return true;
   case LEAF:
         while( true )
            if( sibling() )
               break;
            else
               if( parent() ) {
                  pc = INNER;
                  return true;
   case INNER:    ;
               }
               else {
                  pc = DONE;
   case DONE:     return false;
               }
      }
   return true; // will never be executed
}

void iterTest() {
	using namespace std;
	
	cout << "===  iter test  ===" << endl;
	
	Node tree[5] = {
			{ 0,0,1, 101 },
			{-1,3,1, 102 },
			{-1,1,0, 103 },
			{-2,0,0, 104 },
			{-4,0,0, 105 }
		};
	NaryTree n;
	n.root = tree;
	n.size = 5;
	
	cout << "Preorder: ";
	Preorder pre(n);
	do {
		cout << pre.get()->value << ' ';
	} while( pre.next() );
	cout << endl;
	
	cout << "Postorder: ";
	Postorder post(n);
	do {
		cout << post.get()->value << ' ';
	} while( post.next() );
	cout << endl;
}
