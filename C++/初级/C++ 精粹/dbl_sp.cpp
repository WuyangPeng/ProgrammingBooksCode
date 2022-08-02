/*********************************************************************

  Filename:  dbl_sp.cpp
  Section:   16     Input/Output
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//A program to double space a file.
//Usage: executable  f1 f2
//f1 must be present and readable
//f2 must be writable if it exists

#include  <fstream.h>      //includes iostream.h
#include  <stdlib.h>

void double_space(ifstream& f, ofstream& t)
{
   char  c;

   while (f.get(c)) {
      t.put(c);
      if (c == '\n')
         t.put(c);
   }
}

int main(int argc, char** argv)
{
   if (argc != 3) {
      cout << "\nUsage: " << argv[0]
           <<  "  infile  outfile" << endl;
      exit(1);
   }

   ifstream  f_in(argv[1]);
   ofstream  f_out(argv[2]);

   if (!f_in) {
      cerr << "cannot open " << argv[1] << endl;
      exit(1);
   }
   if (!f_out) {
      cerr << "cannot open " << argv[2] << endl;
      exit(1);
   }
   double_space(f_in, f_out);
}

