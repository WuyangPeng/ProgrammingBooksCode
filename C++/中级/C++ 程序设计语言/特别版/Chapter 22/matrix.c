// Program to test slices and a simple N*M matrix class

// pp 670-674 and 683-684

// No guarantees offered. Constructive comments to bs@research.att.com


#include<iostream>
#include<valarray>
#include<algorithm>
#include<numeric>	// for inner_product
using namespace std;

// forward declarations to allow friend declarations:
template<class T> class Slice_iter;
template<class T> bool operator==(const Slice_iter<T>&, const Slice_iter<T>&);
template<class T> bool operator!=(const Slice_iter<T>&, const Slice_iter<T>&);
template<class T> bool operator< (const Slice_iter<T>&, const Slice_iter<T>&);

template<class T> class Slice_iter {
	valarray<T>* v;
	slice s;
	size_t curr;	// index of current element

	T& ref(size_t i) const { return (*v)[s.start()+i*s.stride()]; }
public:
	Slice_iter(valarray<T>* vv, slice ss) :v(vv), s(ss), curr(0) { }

	Slice_iter end() const
	{
		Slice_iter t = *this;
		t.curr = s.size();	// index of last-plus-one element
		return t;
	}

	Slice_iter& operator++() { curr++; return *this; }
	Slice_iter operator++(int) { Slice_iter t = *this; curr++; return t; }

	T& operator[](size_t i) { return ref(i); }		// C style subscript
	T& operator()(size_t i) { return ref(i); }		// Fortran-style subscript
	T& operator*() { return ref(curr); }			// current element

	friend bool operator==<>(const Slice_iter& p, const Slice_iter& q);
	friend bool operator!=<>(const Slice_iter& p, const Slice_iter& q);
	friend bool operator< <>(const Slice_iter& p, const Slice_iter& q);

};


template<class T>
bool operator==(const Slice_iter<T>& p, const Slice_iter<T>& q)
{
	return p.curr==q.curr
		&& p.s.stride()==q.s.stride()
		&& p.s.start()==q.s.start();
}

template<class T>
bool operator!=(const Slice_iter<T>& p, const Slice_iter<T>& q)
{
	return !(p==q);
}

template<class T>
bool operator<(const Slice_iter<T>& p, const Slice_iter<T>& q)
{
	return p.curr<q.curr
		&& p.s.stride()==q.s.stride()
		&& p.s.start()==q.s.start();
}


//-------------------------------------------------------------



// forward declarations to allow friend declarations:
template<class T> class Cslice_iter;
template<class T> bool operator==(const Cslice_iter<T>&, const Cslice_iter<T>&);
template<class T> bool operator!=(const Cslice_iter<T>&, const Cslice_iter<T>&);
template<class T> bool operator< (const Cslice_iter<T>&, const Cslice_iter<T>&);


template<class T> class Cslice_iter 
{
	valarray<T>* v;
	slice s;
	size_t curr; // index of current element
	const T& ref(size_t i) const { return (*v)[s.start()+i*s.stride()]; }
public:
	Cslice_iter(valarray<T>* vv, slice ss): v(vv), s(ss), curr(0){}
	Cslice_iter end() const
	{
		Cslice_iter t = *this;
		t.curr = s.size(); // index of one plus last element
		return t;
	}
	Cslice_iter& operator++() { curr++; return *this; }
	Cslice_iter operator++(int) { Cslice_iter t = *this; curr++; return t; }
	
	const T& operator[](size_t i) const { return ref(i); }
	const T& operator()(size_t i) const { return ref(i); }
	const T& operator*() const { return ref(curr); }

	friend bool operator==<>(const Cslice_iter& p, const Cslice_iter& q);
	friend bool operator!=<>(const Cslice_iter& p, const Cslice_iter& q);
	friend bool operator< <>(const Cslice_iter& p, const Cslice_iter& q);

};

template<class T>
bool operator==(const Cslice_iter<T>& p, const Cslice_iter<T>& q)
{
	return p.curr==q.curr
		&& p.s.stride()==q.s.stride()
		&& p.s.start()==q.s.start();
}

template<class T>
bool operator!=(const Cslice_iter<T>& p, const Cslice_iter<T>& q)
{
	return !(p==q);
}

template<class T>
bool operator<(const Cslice_iter<T>& p, const Cslice_iter<T>& q)
{
	return p.curr<q.curr
		&& p.s.stride()==q.s.stride()
		&& p.s.start()==q.s.start();
}


//-------------------------------------------------------------


class Matrix {
	valarray<double>* v;	// stores elements by column as described in 22.4.5
	size_t d1, d2;	// d1 == number of columns, d2 == number of rows
public:
	Matrix(size_t x, size_t y);		// note: no default constructor
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	~Matrix();
	
	size_t size() const { return d1*d2; }
	size_t dim1() const { return d1; }
	size_t dim2() const { return d2; }

	Slice_iter<double> row(size_t i);
	Cslice_iter<double> row(size_t i) const;

	Slice_iter<double> column(size_t i);
	Cslice_iter<double> column(size_t i) const;

	double& operator()(size_t x, size_t y);					// Fortran-style subscripts
	double operator()(size_t x, size_t y) const;

	Slice_iter<double> operator()(size_t i) { return column(i); }
	Cslice_iter<double> operator()(size_t i) const { return column(i); }

	Slice_iter<double> operator[](size_t i) { return column(i); }	// C-style subscript
	Cslice_iter<double> operator[](size_t i) const { return column(i); }

	Matrix& operator*=(double);

	valarray<double>& array() { return *v; }
};


inline Slice_iter<double> Matrix::row(size_t i)
{
	return Slice_iter<double>(v,slice(i,d1,d2));
}

inline Cslice_iter<double> Matrix::row(size_t i) const
{
	return Cslice_iter<double>(v,slice(i,d1,d2));
}

inline Slice_iter<double> Matrix::column(size_t i)
{
	return Slice_iter<double>(v,slice(i*d2,d2,1));
}

inline Cslice_iter<double> Matrix::column(size_t i) const
{
	return Cslice_iter<double>(v,slice(i*d2,d2,1));
}

Matrix::Matrix(size_t x, size_t y)
{
	// check that x and y are sensible
	d1 = x;
	d2 = y;
	v = new valarray<double>(x*y);
}

Matrix::~Matrix()
{
	delete v;
}

double& Matrix::operator()(size_t x, size_t y)
{
	return column(x)[y];
}



//-------------------------------------------------------------




double mul(const Cslice_iter<double>& v1, const valarray<double>& v2)
{
	double res = 0;
	for (size_t i = 0; i<v2.size(); i++) res+= v1[i]*v2[i];
	return res;
}


valarray<double> operator*(const Matrix& m, const valarray<double>& v)
{
	if (m.dim1()!=v.size()) cerr << "wrong number of elements in m*v\n";

	valarray<double> res(m.dim2());
	for (size_t i = 0; i<m.dim2(); i++) res[i] = mul(m.row(i),v);
	return res;
}


// alternative definition of m*v

//valarray<double> operator*(const Matrix& m, valarray<double>& v)
valarray<double> mul_mv(const Matrix& m, valarray<double>& v)
{
	if (m.dim1()!=v.size()) cerr << "wrong number of elements in m*v\n";

	valarray<double> res(m.dim2());

	for (size_t i = 0; i<m.dim2(); i++) {
		const Cslice_iter<double>& ri = m.row(i);
		res[i] = inner_product(ri,ri.end(),&v[0],double(0));
	}
	return res;
}



valarray<double> operator*(valarray<double>& v, const Matrix& m)
{
	if (v.size()!=m.dim2()) cerr << "wrong number of elements in v*m\n";

	valarray<double> res(m.dim1());

	for (size_t i = 0; i<m.dim1(); i++) {
		const Cslice_iter<double>& ci = m.column(i);
		res[i] = inner_product(ci,ci.end(),&v[0],double(0));
	}
	return res;
}

Matrix& Matrix::operator*=(double d)
{
	(*v) *= d;
	return *this;
}

ostream& operator<<(ostream& os, Matrix& m)
{
	for(int y=0; y<m.dim2(); y++)
	{
		for(int x=0; x<m.dim1(); x++)
			os<<m[x][y]<<"\t";
		os << "\n";
	}
	return os;
}


//-------------------------------------------------------------


void f (int x_max, int y_max)	// test layout and basic access
{
	cout << "\nf(" << x_max <<"," << y_max << "):\n";
	
	Matrix a(x_max, y_max);

	for(int x=0; x<x_max; x++)		// initialize
		for(int y=0; y<y_max; y++)
			a[x][y]=x+y*10;

	cout<<"C-style access used to initialize:\n" << a;

	for(int x=0; x<x_max; x++)
		for(int y=0; y<y_max; y++)
			a(x,y)=x+y*10;

	cout <<"Fortran-style access used to initialize:\n" << a;
	
	cout << "addresses: \n";

	for(int x=0; x<x_max; x++)
		for(int y=0; y<y_max; y++)
			cout<<"("<< x<<","<<y<<") at "<<&a[x][y]-&a[0][0]<<"\n";
	cout <<"columns :\n";

	for(int x=0; x<x_max; x++) {
		cout << "column " << x << ":\n";
		for (Slice_iter<double> c = a.column(x); c!=c.end(); ++c)
			cout << "\t" << *c <<"\n";
	}

	cout <<"rows :\n";

	for(int y=0; y<y_max; y++) {
		cout << "row " << y << ":";
		for(Slice_iter<double> r = a.row(y); r!=r.end(); ++r)
			cout << "\t" << *r ;
		cout <<"\n";
	}


}

ostream& operator<<(ostream& os, const valarray<double>& v)
{
	for (int i = 0; i<v.size(); ++i) os << '\t' << v[i];
	return os;
}

void g(int x_max,int y_max)	// check multiplication
{
	cout << "\ng(" << x_max <<"," << y_max << "):\n";

	Matrix a(x_max,y_max);

	for(int x=0; x<x_max; x++)		// initialize
		for(int y=0; y<y_max; y++)
			a[x][y]=x+y*10;

	valarray<double> r(2,x_max);
	cout << "a*v: " << a*r << endl;
	cout << "m*v: " << mul_mv(a,r) << endl;

	valarray<double> c(2,y_max);
	cout << "v*a: " << c*a << endl;
	
}

int main()
{
	f(3,4);
	f(4,3);

	g(3,4);
	g(4,3);
}
