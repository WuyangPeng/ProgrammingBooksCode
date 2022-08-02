#ifndef ARRAY_H
#define ARRAY_H

template <typename T, int n>
class Array {
  public:
    T &operator [](int i)
        { return a_[i]; }
    const T &operator [](int i) const
        { return a_[i]; }
    bool operator ==( const Array &rhs ) const;
    bool operator !=( const Array &rhs ) const
    	{ return !(*this==rhs); }
    Array &operator =( const T & );
    void setAll( const T & );
  private:
    T a_[n];
};

template <class T, int n>
bool Array<T,n>::operator ==( const Array &rhs ) const {
    for( int i = 0; i < n; ++i )
        if( a_[i] != rhs.a_[i] )
            return false;
    return true;
}

template <class T, int n>
Array<T,n> &Array<T,n>::operator =( const T &val ) {
    for( int i = 0; i < n; ++i )
        a_[i] = val;
    return *this;
}

template<class T, int n>
void Array<T,n>::setAll( const T &val )
	{ *this = val; }

#endif
