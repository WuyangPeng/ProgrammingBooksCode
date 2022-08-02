listing 1
#include <iostream>
#include <cwctype>
using namespace std;

int main()
{
  wctype_t x;

  x = wctype("space");

  if(iswctype(L' ', x))
    cout << "Is a space.\n";

  return 0;
}


listing 2
#include <iostream>
#include <cwctype>
using namespace std;

int main()
{
  wctrans_t x;

  x = wctrans("tolower");

  wchar_t ch = towctrans(L'W', x);
  cout << (char) ch;

  return 0;
}

