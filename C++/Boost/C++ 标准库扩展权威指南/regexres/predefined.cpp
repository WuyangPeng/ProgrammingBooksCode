#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::wregex;
using std::tr1::regex_match;
using std::tr1::cmatch; using std::tr1::smatch;
using std::tr1::wcmatch; using std::tr1::wsmatch;
using std::tr1::csub_match; using std::tr1::ssub_match;
using std::tr1::wcsub_match; using std::tr1::wssub_match;
using std::string; using std::wstring;
using std::cout;

static void show(...)
  { // called with unknown type
  cout << "Called with unknown argument type\n";
  }

static void show(csub_match match)
  { // called with csub_match argument
  cout << "Called show(csub_match)\n";
  }

static void show(wcsub_match match)
  { // called with wcsub_match argument
  cout << "Called show(wcsub_match)\n";
  }

static void show(ssub_match match)
  { // called with ssub_match argument
  cout << "Called show(ssub_match)\n";
  }

static void show(wssub_match match)
  { // called with wssub_match argument
  cout << "Called show(wssub_match)\n";
  }

int main()
  { // show sub_match types for various match_results types
  regex rgx("abc");
  cmatch match0;
  if (regex_match("abc", match0, rgx))
    show(match0[0]);
  smatch match1;
  if (regex_match(string("abc"), match1, rgx))
    show(match1[0]);
  wregex wrgx(L"abc");
  wcmatch match2;
  if (regex_match(L"abc", match2, wrgx))
    show(match2[0]);
  wsmatch match3;
  if (regex_match(wstring(L"abc"), match3, wrgx))
    show(match3[0]);
  return 0;
  }