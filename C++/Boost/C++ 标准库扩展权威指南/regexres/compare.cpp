#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_match;
using std::tr1::csub_match; using std::tr1::cmatch;
using std::cout;

static char *blocked_sites[] =
{ // block list; any resemblance between the names here
  // and real URLs is probably accidental
"www.idontwantmykidshere.com",
"www.lotsofxxxstuff.com",
"www.nra.org"
};
const int nsites = sizeof(blocked_sites)
  / sizeof(*blocked_sites);

bool allow(const csub_match& match)
  { // return false if match is on the blocked list
  for (int i = 0; i < nsites; ++i)
    if (match.compare(blocked_sites[i]) == 0)
      return false;
  return true;
  }

bool check_url(const char *url)
  { // return false if URL is not a valid HTTP URL or
    // if the hostname is on the blocked list
  regex rgx("http://([^/: ]+)(:(\\d+))?(/.*)?");
  cmatch match;
  return regex_match(url, match, rgx) && allow(match[1]);
  }

void connect(const char *url)
  { // connect to valid, unblocked URL
  if (check_url(url))
    {
    cout << "Okay to connect: " << url << '\n';
    // remainder of connection code left as exercise for the reader
    }
  else
    cout << "Invalid or blocked URL: " << url << '\n';
  }

int main()
  { // connect to a couple of sites
  connect("http://www.xxx.com/risque/index.html");
  connect("http://www.petebecker.com/tr1book");
  connect("http:/invalid, for many reasons");
  return 0;
  }
