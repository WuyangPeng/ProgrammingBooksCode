
#include <stddef.h>

#define NUM_ELEMENTS(x)                             (sizeof(x) / sizeof(0[(x)]))

// unittest.h
typedef struct SomeLongStructName
{
    int i;
} SLSN;
typedef int (*SLSN_processor_t)(SLSN*, int*);
int process(SLSN_processor_t, int*);

// client_code.cpp
int process_forwards(SLSN*, int);
int process_backwards(SLSN*, int);

int main()
{
    int i;

  struct SomeLongStructName s1;
  SLSN_processor_t  pfn[10];

  for(i = 0; i < NUM_ELEMENTS(pfn); ++i)
  {
      pfn[i] = (i & 1) ?  process_forwards : process_backwards;
  }

//  pfn = (. . .) ? process_forwards
//result = (*pfn)(&s1, &p);
//  . . .
}