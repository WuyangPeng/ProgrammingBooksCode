#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

#include "ccc_empl.cpp"

const int NEWLINE_LENGTH = 2; /* or 1 on Unix */
const int RECORD_SIZE = 30 + 10 + NEWLINE_LENGTH;

/** 
   Converts a string to a floating-point value, e.g. 
   "3.14" -> 3.14.
   @param s a string representing a floating-point value
   @return the equivalent floating-point value
*/   
double string_to_double(string s)
{  
   istringstream instr(s);
   double x;
   instr >> x;
   return x;
}

/** 
   Raises an employee salary.
   @param e employee receiving raise
   @param percent the percentage of the raise
*/
void raise_salary(Employee& e, double percent)
{  
   double new_salary = e.get_salary() * (1 + percent / 100);
   e.set_salary(new_salary);
}

/**
   Reads an employee record from a file.
   @param e filled with the employee
   @param in the stream to read from
*/
void read_employee(Employee& e, istream& in)
{  
   string line;
   getline(in, line);
   if (in.fail()) return;
   string name = line.substr(0, 30);
   double salary = string_to_double(line.substr(30, 10));
   e = Employee(name, salary);
}

/**
   Writes an employee record to a stream
   @param e the employee record to write
   @param out the stream to write to
*/
void write_employee(Employee e, ostream& out)
{  
   out << e.get_name()
      << setw(10 + (30 - e.get_name().length()))
      << fixed << setprecision(2)
      << e.get_salary()
      << "\n";
}

int main()
{  
   cout << "Please enter the data file name: ";
   string filename;
   cin >> filename;
   fstream fs;
   fs.open(filename.c_str());
   fs.seekg(0, ios::end); /* go to end of file */
   int nrecord = fs.tellg() / RECORD_SIZE;

   cout << "Please enter the record to update: (0 - "
      << nrecord - 1 << ") ";
   int pos;
   cin >> pos;

   const double SALARY_CHANGE = 5.0;

   Employee e;
   fs.seekg(pos * RECORD_SIZE, ios::beg);
   read_employee(e, fs);
   raise_salary(e, SALARY_CHANGE);
   fs.seekp(pos * RECORD_SIZE, ios::beg);
   write_employee(e, fs);

   fs.close();
   return 0;
}
