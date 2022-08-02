/*********************************************************************

  Filename:  shape.cpp
  Section:   12.5   Virtual Functions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//shape hierarchy and virtual area() calculation
#include <iostream.h>

const double PI = 3.14159;

class shape {                      //abstract base class
public:
   virtual double  area() const { return 0; }
   //virtual double area is default behavior
   virtual char* geta_name() = 0;  //pure virtual
protected:
   double  x, y;
};

class rectangle : public shape {
public:
   rectangle(double h, double w):height(h), width(w){}
   double  area() const { return (height * width); }
   char* geta_name() { return (" RECTANGLE "); }
private:
   double  height, width;
};

class circle : public shape {
public:
   circle(double r): radius(r) { }
   double  area() const
      { return (PI * radius * radius); }
   char* geta_name() { return (" CIRCLE "); }
private:
   double   radius;
};

int main()
{
   shape*     ptr_shape;
   rectangle  rec(4.1, 5.2);
   circle     cir(6.1);
   cout << "\nThis program uses hierarchies "
        << "for shapes\n";
   ptr_shape = &rec;
   cout << endl << ptr_shape -> geta_name();
   cout << "  area = " << ptr_shape -> area();
   ptr_shape = &cir;
   cout << endl << ptr_shape -> geta_name();
   cout << "  area = " << ptr_shape -> area();
}

