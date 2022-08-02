/**
  * Testbed for enumerated.pl
  *
  * Check that the output of enumerated.pl agrees with test.inc
  *
  */

#include <string.h>

#include "../c/tests.h"
#include "etest.h"

#define TRY(T) if (strcmp(ETEST_name[T], #T)) fail(#T "'s name is wrong")


int main() {
  TRY(STATEA);
  TRY(STATEB);
  TRY(STATEC);
  TRY(STATED);

  return 0;
}

