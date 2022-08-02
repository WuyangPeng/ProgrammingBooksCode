/*********************************************************************

  Filename:  vect_it.cpp
  Section:   13     Templates
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//templates for vect with associated iterator class
#include  <iostream.h>
#include  <assert.h>      //for assert


template <class T> class  vect_iterator;
template <class T>
class vect {
public:
   //constructors and destructor
   typedef T* iterator;
   explicit vect(int n = 10);//default constructor
   vect(const vect& v);//copy constructor
   vect(const T a[], int n);//from array
   ~vect() { delete [] p; }
   iterator begin(){ return p;}
   iterator end(){ return p + size;}
   T&  operator[](int i) const;
   vect& operator=(const vect& v);
   friend vect
      operator+(const vect& v1,
                const vect& v2);
   friend ostream&
      operator<<(ostream& out,
                 const vect<T>& v);
   friend class vect_iterator<T>;
private:
   T*    p;     //base pointer
   int   size;  //number of elements
};


//default constructor
//default constructor
template <class T>
vect<T>::vect(int n = 10): size(n)
{
   assert(n > 0);
   p = new T[size];
   assert(p != 0);
}


//copy constructor
template<class T>
vect<T>::vect(const vect<T>& v)
{
   size = v.size;
   p = new T[size];
   assert (p != 0);
   for (int i = 0; i < size; ++i)
      p[i] = v.p[i];
}

//Initializing vect from an array
template<class T>
vect<T>::vect(const T a[], int n) : size (n)
{
   assert (n > 0);
   p = new T[size];
   assert (p != 0);
   for (int i = 0; i < size; ++i)
      p[i] = a[i];
}

//overloaded subscript operator
template<class T>
T& vect<T>::operator[](int i) const
{
   assert (i >= 0 && i < size);
   return p[i];
}

//overloaded output operator
template<class T>
ostream& operator<<(ostream& out,
                    const vect<T>& v)
{
   for (int i = 0; i <= (v.size-1); ++i)
      out << v.p[i] << '\t';
   return (out << endl);
}

template<class T>
vect<T>& vect<T>::operator=
          (const vect<T>& v)
{
   assert(v.size == size);
   for (int i = 0; i < size; ++i)
      p[i] = v.p[i];
   return (*this);
}

template<class T> vect<T>
   operator+(const vect<T>& v1, const vect<T>& v2)
{
   int   s = (v1.size < v2.size) ?
             v1.size : v2.size;
   vect  sum(s);
   if (v1.size != v2.size)
      cerr <<
          "adding different size arrays "
           << v1.size << " and " << v2.size
           << endl;
   for (int i = 0; i < s; ++i)
      sum.p[i] = p[i] + v.p[i];
   return sum;
}

template<class T>
void init_vect(vect<T>& v,
          int start, int incr)
{
   for (int i = 0; i <= v.ub(); ++i) {
      v[i] = start;
      start += incr;
   }
}

int main()
{
   vect<double> v(5);
   vect<double>::iterator p ;
   int i = 0;

   for (p = v.begin() ; p != v.end(); ++p)
      *p = 1.5 + i++;

   do {
      --p;
      cout << *p << " , ";
   } while (p != v.begin());
   cout << endl;
}

