/**
  * Interface for our testbed.
  *
  * When we run tests on code, we want a consistent reporting of the results.
  * The tests.c file gives us he routine 'fail' which is used to
  * report a failed test.
  *
  **/

#ifndef _TESTS_H
#define _TESTS_H

void fail(const char *fmt, ...);

#endif
