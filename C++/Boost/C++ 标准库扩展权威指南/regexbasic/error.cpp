#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_error;
using std::cout;

const char *get_error(
  std::tr1::regex_constants::error_type code)
  { // translate error code to text
  switch (code)
    { // select text
    case std::tr1::regex_constants::error_backref:
      return "invalid back reference";
    case std::tr1::regex_constants::error_badbrace:
      return "invalid repetition count";
    case std::tr1::regex_constants::error_badrepeat:
      return "repeat not preceded by expression";
    case std::tr1::regex_constants::error_brace:
      return "unmatched curly brace";
    case std::tr1::regex_constants::error_brack:
      return "unmatched square bracket";
    case std::tr1::regex_constants::error_collate:
      return "invalid collating element name";
    case std::tr1::regex_constants::error_complexity:
      return "match too complex";
    case std::tr1::regex_constants::error_ctype:
      return "invalid character class name";
    case std::tr1::regex_constants::error_escape:
      return "invalid character escape sequence";
    case std::tr1::regex_constants::error_paren:
      return "unmatched parenthesis";
    case std::tr1::regex_constants::error_range:
      return "invalid range specifier";
    case std::tr1::regex_constants::error_space:
      return "insufficient resources";
    case std::tr1::regex_constants::error_stack:
      return "out of memory";
    default:
      return "unknown";;
    }
  }

void test(const char *expr)
  { // construct regex object, catch exception
  cout << '`' << expr << "', ";
  try 
    { // try to construct regex object with invalid regular expression
    regex rgx(expr);
    cout << "okay\n";
    }
  catch(const regex_error& error)
    { // catch regex_error object
    cout << get_error(error.code()) << '\n';
    }
  }

int main()
  { // demonstrate use of error_type
  test("a{3,1}");
  test("[b-a]");
  return 0;
  }