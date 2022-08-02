/*********************************************************************

  Filename:  word_cnt.cpp
  Section:   16     Streams
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//The word_cnt program for counting words.
//Usage: executable < file
#include  <iostream.h>
#include  <ctype.h>
int  found_next_word();

int main()
{
   int  word_cnt = 0;

   while (found_next_word())
      ++word_cnt;
   cout << "word count is " << word_cnt << endl;
}

int found_next_word()
{
   char  c;
   int   word_sz = 0;

   cin >> c;
   while ( !cin.eof() && !isspace(c)) {
      ++word_sz;
      cin.get(c);
   }
   return word_sz;
}

