#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using std::tr1::regex; using std::tr1::regex_search;
using std::tr1::smatch;
using std::string; using std::ifstream; using std::cout;

static void show_matches(const char *fname)
  { // scan file named by fname, line by line
  ifstream input(fname);
  string str;
  smatch match;
  const char *expr = "<CODE>(.*)</CODE>";
  regex rgx(expr, regex::icase);
  while (getline(input, str))
    { // check line for match
    if (regex_search(str, match, rgx))
      cout << match[1] << '\n';
    }
  }

int main(int argc, char *argv[])
  { // search for code snippets in text file
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