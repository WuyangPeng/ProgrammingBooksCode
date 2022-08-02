/**
  * Standard interface for tests.
  *
  * Provides the routine 'fail' to fail a test
  *
  */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#include "tests.h"

/*
 * Report a failed test and exit
 */

void fail(const char *fmt, ...) {

  va_list ap;
  
  va_start(ap, fmt);

  fprintf(stderr, "TEST FAILED -- ");
  vfprintf(stderr, fmt,  ap);
  fprintf(stderr, "\n");

  exit(1);
}

