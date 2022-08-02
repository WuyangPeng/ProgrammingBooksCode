// demonstrate use of match_XXX functions for regular expression searching
#include "rgxutil.h"

int main()
  { // demonstrate functions match_XXX
  match_ECMA("[b-z]", "b");
  match_grep("[b-z]", "b");
  match_ere("[b-z]", "b");

  match_ECMA("[b-z]", "c");
  match_grep("[b-z]", "c");
  match_ere("[b-z]", "c");

  match_ECMA("[b-z]", "a");
  match_grep("[b-z]", "a");
  match_ere("[b-z]", "a");

  match_ECMA("[b-z]", "B");
  match_grep("[b-z]", "B");
  match_ere("[b-z]", "B");
  return 0;
  }