/*********************************************************************

  Filename:  student.cpp
  Section:   12     Inheritance
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <string.h>

enum year { fresh, soph, junior, senior, grad };
enum support { ta, ra, fellowship, other };

//base class student
class student {
public:
   student(char* nm, int id, double g, year x);
   friend ostream& operator<<(ostream& out, const
                              student& stu);
protected:
   int     student_id;
   double  gpa;
   year    y;
   char    name[30];
};

//derived class grad_student
class grad_student : public student {
public:
   grad_student (char* nm, int id, double g,
                year x, support t, char* d, char* th);
   friend ostream& operator <<(ostream& out,
                           const grad_student& gstu);
protected:
   support  s;
   char     dept[10];
   char     thesis[80];
};

student::student(char* nm, int id, double g, year x) :
                 student_id(id), gpa(g), y(x)
{
   strcpy(name, nm);
}

grad_student::grad_student (
   char* nm, int id, double g, year x, support t,
   char* d, char* th) : student(nm, id, g, x), s(t)
{
   strcpy(dept, d);
   strcpy(thesis, th);
}

//overloaded output operator
ostream& operator <<(ostream& out, const student& stu)
{
   cout << endl << stu.name << ", "
        << stu.student_id << ", "
        << stu.y << ", " << stu.gpa;
   return (out << endl);
}

ostream& operator <<(ostream& out,
                     const grad_student& gstu)
{
   out << (student)gstu;     //base class info printed
   out << gstu.dept << ", " << gstu.s << endl
       << gstu.thesis;
   return (out << endl);
}

int main()
{
   student       s("Mae Pohl", 100, 3.425, fresh);
   grad_student  gs("Morris Pohl", 200, 3.2564, grad,
                 ta, "Pharmacy", "Retail Pharmacies");

   cout << s;
   cout << gs;
}


