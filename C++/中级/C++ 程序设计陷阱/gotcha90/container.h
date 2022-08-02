#ifndef CONTAINER_H
#define CONTAINER_H

template <typename T>
class Iter;

template <typename T>
class Container {
  public:
    virtual ~Container() {}
    virtual Iter<T> *genIter() const = 0; // Factory Method
    virtual Container *clone() const = 0; // Prototype
    virtual void insert( const T & ) = 0;
};

template <typename T>
class Iter {
  public:
    virtual ~Iter() {}
    virtual void reset() = 0;
    virtual void next() = 0;
    virtual bool done() const = 0;
    virtual T &get() const = 0;
};

#endif
