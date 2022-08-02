#ifndef RGXUTIL_H
#define RGXUTIL_H

#include <iostream>
#include <iomanip>
#include <regex>

static const char intro[] = "Trying to match `";
static const unsigned intro_chrs = sizeof(intro) - 1;

static const char *error(const std::tr1::regex_error& err)
  { // return description of error
  switch (err.code())
    { // select description
    case std::tr1::regex_constants::error_badbrace:
      return "invalid repeat count";
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
      return "invalid escape sequence";
    case std::tr1::regex_constants::error_paren:
      return "unmatched parenthesis";
    case std::tr1::regex_constants::error_range:
      return "invalid character range specifier";
    case std::tr1::regex_constants::error_space:
      return "out of resources";
    case std::tr1::regex_constants::error_stack:
      return "out of memory";
    case std::tr1::regex_constants::error_backref:
      return "invalid back reference";
    default:
      return "unknown error";;
    }
  }

static void do_match(const char *str, const char *tgt,
  std::tr1::regex_constants::syntax_option_type flags)
  {
  std::tr1::regex rgx;
  std::cout << "Regular expression `" << str << "`: ";
  try 
    { // compile regular expression
    rgx.assign(str, flags);
    std::cout << "okay\n";
    }
  catch(const std::tr1::regex_error& err)
    { // report regular expression error
    std::cout << "invalid\n " << error(err) << '\n';
    return;
    }
  if (tgt)
    { // check for match
    std::tr1::cmatch mr;
    std::cout << intro << tgt << "`, ";
    try
      { // try to match
      if (std::tr1::regex_match(tgt, mr, rgx))
          { // report successful match
          std::cout << "success\n";
          for (int i = 0; i < mr.size(); ++i)
            std::cout << std::setw(intro_chrs - 2) << i << ':'
              << std::setw(mr.position(i) + 1) << ' '
              << mr[i] << '\n';
          }
      else
        std::cout << "no match\n";
      }
    catch(const std::tr1::regex_error& err)
      { // report match error
      std::cout << "match failed\n " << error(err) << '\n';
      }
    }
  }

static void match_ECMA(const char *str, const char *tgt = 0)
  {
  do_match(str, tgt, std::tr1::regex_constants::ECMAScript);
  }

static void match_grep(const char *str, const char *tgt = 0)
  {
  do_match(str, tgt, std::tr1::regex_constants::grep);
  }

static void match_ere(const char *str, const char *tgt = 0)
  {
  do_match(str, tgt, std::tr1::regex_constants::extended);
  }

#endif /* RGXUTIL_H */
