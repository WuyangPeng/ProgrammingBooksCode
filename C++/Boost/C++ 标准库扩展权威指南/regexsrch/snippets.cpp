#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using std::tr1::regex; using std::tr1::regex_search;
using std::string; using std::ifstream; using std::cout;

static void show_matches(const char *fname)
  { // scan file named by fname, line by line
  ifstream input(fname);
  string str;
  const char *expr = "<CODE>";
  regex rgx(expr, regex::icase);
  while (getline(input, str))
    { // check line for match
    if (regex_search(str, rgx))
      cout << str << '\n';
    }
  }

int main(int argc, char *argv[])
  { // search for lines with code snippets in text file
  if (argc != 2)
    { // wrong number of arguments
    cout << "Usage: snippets <filename>\n";
    return EXIT_FAILURE;
    }
  try
    { // search the file
    show_matches(argv[1]);
    }
  catch(...)
    { // something went wrong
    cout << "Error\n";
    return EXIT_FAILURE;
    }
  return 0;
  }
