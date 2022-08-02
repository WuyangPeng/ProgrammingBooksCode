#ifndef LIST_H
#define LIST_H

#include <memory>

template <typename T>
class ListIter;

template <typename T>
struct ListNode {
  	ListNode( ListNode *n, const T &t )
  		: n_( n ), e_( t ) {}
  	ListNode *n_;
  	T e_;
};

template <typename T>
class List : public Container<T> {
  public:
  	List()
  		: hd_( 0 ) {}
    ~List();
    ListIter<T> *genIter() const
    	{ return new ListIter<T>( *this ); }
    List *clone() const;
    void insert( const T &t )
    	{ ListNode<T> *tmp = new ListNode<T>( hd_, t ); hd_ = tmp; }
  private:
	friend class ListIter<T>;
	List( const List & );
	List &operator =( const List & );
  	ListNode<T> *hd_;
};

template <typename T>
class ListIter : public Iter<T> {
  public:
  	ListIter( const List<T> &l )
  		: c_( l.hd_ ), l_( &l ) {}
    virtual ~ListIter() {}
    virtual void reset()
    	{ c_ = l_->hd_; }
    virtual void next()
    	{ c_ = c_->n_; }
    virtual bool done() const
    	{ return !c_; }
    virtual T &get() const
    	{ return c_->e_; }
  private:
  	ListNode<T> *c_;
  	const List<T> *l_;
};

template <typename T>
List<T>::~List() {
	ListNode<T> *p = hd_, *q;
	while( p ) {
		q = p;
		p = p->n_;
		delete q;
	}
}

template <typename T>
List<T> *List<T>::clone() const {
	// not efficient, but interesting...
	std::auto_ptr<List> n1( new List );
	for( ListIter<T> i( *this ); !i.done(); i.next() )
		n1->insert( i.get() );
	List *n2( new List );
	for( ListIter<T> i( *n1 ); !i.done(); i.next() )
		n2->insert( i.get() );
	return n2;
}
    	
#endif
