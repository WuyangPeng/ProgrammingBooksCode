///////////////////////////////////////////////////////////////////////////////
// Crossword Puzzle Helper
//
// From Chapter 15 of:
// "C++: The Core Language" by Gregory Satir and Doug Brown.
// O'Reilly & Associates, Inc. Sebastopol, CA. 1995.
///////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>     // to get exit()
#include <string.h>     // to get strlen() and strcpy()
#include <stdio.h>      // to get old-style input
#include <iostream.h>   // to get new-style output
#include <new.h>        // to get set_new_handler()

// big trouble if any word in the dictionary 
// exceeds this ('\0' terminator included)
#define maxwordsize 256
 
// These are now C++ keywords, take them out if your compiler has them.
// If not, use these definitions.
typedef int bool;
#define true 1
#define false 0
 
// length of hexword generalized 
// You could have a puzzle with a different length, but we haven't seen any.
#define hex 6

// error exit
void oops(char *msg) {
  cerr << msg << "\n";
  exit(1);
}

// called by new if insufficient memory
void dearth_o_mem() {
  oops("out of memory");
}

///////////////////////////////////////////////////////////////////////////////
// String: wrapper class for array of characters
///////////////////////////////////////////////////////////////////////////////
class String {
public:
    String();                       // default constructor
    ~String();                      // destructor
    void operator=(String &s);      // assignment operator
    String(String &s);              // copy constructor

    void set(char *s);              // set from char*
    char *s();                      // return pointer to string
    char c(int n);                  // return nth char
    int length();                   // return length of string

    void print(ostream *os);        // print string to output stream
    bool read(FILE *is);            // read string from old-style input

private:
    char *str;                      // pointer to string
    int lth;                        // length of string
};

// default constructor - initialize object
String::String() {
  str = 0;                          // make nothing for set() to deallocate
  set("");                          // set() copies empty string
}
 
// destructor - free object memory
String::~String() {
  delete[] str;                     // deallocate string
}

// assignment operator - define meaning of operator=() for this class
void String::operator=(String &s) {
  if (this == &s) return;           // don't assign to self
  set(s.str);                       // set() makes a copy
}
 
// copy constructor - initialize object as copy of another object
String::String(String &s) { 
  str = 0;                          // make nothing for set() to deallocate
  set(s.str);                       // set() makes a copy
}

// set value from string
void String::set(char *s) {
  delete[] str;                     // deallocate old string
  lth = strlen(s);                  // set length of new string
  str = new char[lth+1];            // alloc space for string and terminator
  strcpy(str, s);                   // copy string and terminator
}

// return pointer to string
char *String::s() {
  return str;                       // return the pointer
}
 
// return nth character of string
char String::c(int n) {
  // check to make sure n is inside string
  if (n < 0 || n >= lth) oops("string index error");
  return str[n];                    // return the char
}
 
// return length of string
int String::length() {
  return lth;                       // return the length
}
 
// print string to output stream
void String::print(ostream *os) {
  *os << str;                       // op<<() already knows how to print char*
}

// overload << for String
ostream &operator<<(ostream &os, String &s) {
  s.print(&os);                     // call our print member function
  return os;                        // so you can write: cout << a << b
}
 
// read string from old-style input
// This routine uses fscanf() directly into a buffer, which is unsafe.
// If the input file has a word that's too long it will write outside
// the buffer.  The code to do this right, typically using a getc()
// and checking the buffer size with each character, is left as an
// exercise for the reader because it contains nothing new for C++.
bool String::read(FILE *is) {
  char buf[maxwordsize];            // temp buffer
  int n = fscanf(is, "%s", buf);    // read word into buffer
  if (n != 1) return false;         // EOF or other failure
  set(buf);                         // set String to word
  return true;                      // successful return
}

///////////////////////////////////////////////////////////////////////////////
// Rule: class for rules that decide if a word matches some criterion.
// This class defines the interface for the acceptance rule.
// It has no default for accepts() so all the rules that can be instantiated
// are derived from this.
///////////////////////////////////////////////////////////////////////////////
class Rule {
public:
    // test word and return true if it meets the criterion
    virtual bool accepts(String word) = 0;
};
 
///////////////////////////////////////////////////////////////////////////////
// CwRule: class for crossword puzzle rules
///////////////////////////////////////////////////////////////////////////////
class CwRule : public Rule {
public:
    // member function declared in base class
    bool accepts(String word);
    // set the rule
    void set(String cmd);
private:
    // where to store the rule
    String cword;
};

// Test a word to see if it matches a crossword puzzle rule.
// The rule is stored as a String with ?'s where any character
// can match, and the rest of the characters must match exactly.
bool CwRule::accepts(String dword) {
  int i, dlth = dword.length();
  // The word must match the rule length exactly
  if (dlth != cword.length()) return false;
  // loop through each character in the rule
  for (i = 0; i < dlth; i++) {
    // get the character in the rule
    char c = cword.c(i);
    // word doesn't match if characters don't match,
    // unless rule character is a ?
    if (c != '?' && c != dword.c(i)) return false;
  }
  // word matches if all the characters match
  return true;
}
 
// set crossword puzzle rule
void CwRule::set(String cmd) {
  cword = cmd;  // uses assignment operator from String class
}
 
///////////////////////////////////////////////////////////////////////////////
// HwRule: class for hexword puzzle rules
///////////////////////////////////////////////////////////////////////////////
class HwRule : public Rule {
public:
    // member function declared in base class
    bool accepts(String word);
    // set the rule
    void set(String cmd);
private:
    // where to store the rule
    String hword;
};
 
// Test a word to see if it matches a hexword puzzle rule.
// The rule is stored as a String with ?'s where any character
// can match, and the rest of the characters must match exactly.
// Unlike the crossword puzzle word, the hexword puzzle word doesn't
// have to match the size of the rule.  The word must be exactly
// 6 characters long, and the rule must match consecutive characters
// in the dictionary word, going in either direction, possibly
// wrapping around the end or beginning.
bool HwRule::accepts(String dword) {
  int d, h;
 
  // dictionary word length must be 6
  if (dword.length() != hex) return false;
 
  // For every starting point d in the dictionary word,
  // we scan forward and backward from d to see if the rule matches.
  // Instead of d going from 0 to 6 it goes from 6 to 12 so we
  // can add or subtract (to go forward or backward) then take the
  // modulo 6 to get a character position in the dictionary word.
  // If d started at 0 it would go negative and we don't trust
  // modulo of negative numbers.
  for (d = hex; d < 2 * hex; d++) {
    // at each new starting point of the dictionary word,
    // assume the forward and backward searches are successful so far
    bool fwd = true, bwd = true;
    int hlth = hword.length();
    // scan the rule, and fwd and bwd in the dictionary word
    for (h = 0; h < hlth; h++) {
      // get rule character
      char c = hword.c(h);
      // fail fwd at this d if it doesn't match exactly, unless ?
      fwd = fwd && (c == '?' || c == dword.c((d+h)%hex));
      // fail bwd at this d if it doesn't match exactly, unless ?
      bwd = bwd && (c == '?' || c == dword.c((d-h)%hex));
      // optimization - give up on this d if fwd and bwd have already failed
      if (!fwd && !bwd) break;
    }
    // optimization - match if fwd or bwd matched at any d
    if (fwd || bwd) return true;
  }
  // failed if neither fwd nor bwd matched for any d
  return false;
}
 
// set hexword puzzle rule
void HwRule::set(String cmd) {
  hword = cmd; // uses assignment operator from String class
}
 
///////////////////////////////////////////////////////////////////////////////
// Scanner: Class to scan the dictionary searching for words that match
// a given rule.
///////////////////////////////////////////////////////////////////////////////
class Scanner {
public:
    // default constructor
    Scanner();
    // destructor
    ~Scanner();
    // set the dictionary file
    void dict(String name);
    // scan the dictionary for a given rule
    void scan(Rule *the_rule);
private:
    // assignment operator
    void operator=(Scanner &s);
    // copy constructor
    Scanner(Scanner &s);
    // store pointer to dictionary file stream here
    FILE *dictionary;
};

// default constructor - initialize object
Scanner::Scanner() {
    // no dictionary to start with
    dictionary = 0;
}

Scanner::~Scanner() {
    // close dictionary if it's open
    if (dictionary != 0) fclose(dictionary);
}

// set dictionary file
void Scanner::dict(String name) {
  // open the file for old-style reading
  dictionary = fopen(name.s(), "r");
  // error if it won't open for reading
  if (dictionary == 0) oops("can't open dictionary");
}
 
// scan the dictionary with a rule
void Scanner::scan(Rule *the_rule) {
  String word;
 
  // make sure we have a dictionary
  if (dictionary == 0) oops("no dictionary to search");
  // the dictionary needs to be rewound after the first scan
  rewind(dictionary);
  // read a word from the dictionary
  while (word.read(dictionary)) {
    // check if the word matches the rule
    if (the_rule->accepts(word)) {
      // print it if it does
      cout << word << "\n";
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// mainline code
///////////////////////////////////////////////////////////////////////////////

// The input loop.  Pass it an instantiation of a scanner.
void input_loop(Scanner *the_scanner) {
  String cmd;   // command word goes here
  CwRule cr;    // crossword rule goes here
  HwRule hr;    // hexword rule goes here
 
  // read in typed-in commands
  while (cmd.read(stdin)) {
    // word beginning with q means quit (or quite enough)
    if (cmd.c(0) == 'q') break;
    // check for one of our rules
    switch (cmd.c(0)) {
    // c for crossword rule
    case 'c':
        // read next word into a String
        if (!cmd.read(stdin)) return;
        // set the crossword rule with it
        cr.set(cmd);
        // scan the dictionary with the crossword rule
        the_scanner->scan(&cr);
        break;
    // h for hexword rule
    case 'h':
        // read next word into a String
        if (!cmd.read(stdin)) return;
        // set the hexword rule with it
        hr.set(cmd);
        // scan the dictionary with the hexword rule
        the_scanner->scan(&hr);
        break;
    // otherwise it's an error
    default:
        cout << "unrecognized command\n";
        break;
    }
  }
}

// The main function. Parameter argv[1] should be dictionary file name.
int main(int argc, char**argv) {
  // we want new to exit on memory exhaustion
  set_new_handler(dearth_o_mem);
  // keep things in sync while we mix the stdio and iostream libraries
  ios::sync_with_stdio();
  // the scanner we use for scanning the dictionary
  Scanner the_scanner;
  // String for dictionary name
  String dictName;
  argc--; argv++;
  if (argc != 1) oops("must specify a single dictionary");
  // set dictionary name String from command argument
  dictName.set(*argv);
  // give dictionary name to scanner
  the_scanner.dict(dictName);
  // pass scanner to input loop
  input_loop(&the_scanner);
  // exit when input loop is done
  return 0;
}
