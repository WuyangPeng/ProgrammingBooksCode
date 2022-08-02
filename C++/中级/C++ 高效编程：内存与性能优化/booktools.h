
#ifndef __BOOKTOOLS_H
#define __BOOKTOOLS_H
#if __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <ctype.h>

unsigned long time_fn(long (*fn)(void), int nrSamples = 1);
//void time_on();
//unsigned long time_off();
void print_time(long msec);

void system_info();
//void alignment_info();
void DisplayASCIITable();

#if __cplusplus
}
#endif

#endif
