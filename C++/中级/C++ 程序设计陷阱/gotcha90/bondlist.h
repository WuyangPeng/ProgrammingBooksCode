#ifndef BONDLIST_H
#define BONDLIST_H

class Object
    { public: virtual ~Object(){} };
class Instrument : public Object
    { public: virtual double pv() const = 0; };
class Bond : public Instrument
    { public: double pv() const; };
class ObjectList {
  public:
  	ObjectList() : c(0) {}
    void insert( Object *o ) { a[c++] = o; }
    Object *get();
    size_t size() const { return c; }
    Object *operator [](int i) { return a[i]; }
    //...
    private:
    int c;
    Object *a[100];
};
class BondList : public ObjectList { // bad idea!!!
  public:
    void insert( Bond *b )
        { ObjectList::insert( b ); }
    Bond *get()
        { return static_cast<Bond *>(ObjectList::get()); }
    Bond *operator []( int a ) { return (Bond *)ObjectList::operator [](a); }
    //...
};

#endif
