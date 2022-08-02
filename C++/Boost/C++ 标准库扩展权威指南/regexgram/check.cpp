// demonstrate use of match_XXX functions to check regular expression syntax
#include "rgxutil.h"

int main()
  { // demonstrate functions match_XXX
  const char expr[] = "a*";
  match_ECMA(expr);
  match_grep(expr);
  match_ere(expr);

  match_ECMA("*");
  match_grep("*");
  match_ere("*");
  return 0;
  }