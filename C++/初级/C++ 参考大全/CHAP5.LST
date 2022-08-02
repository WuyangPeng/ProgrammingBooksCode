listing 1
m = &count;

listing 2
q = *m;

listing 3
#include <stdio.h>

int main(void)
{
  double x = 100.1, y;
  int  *p;

  /* The next statement causes p (which is an
      integer pointer) to point to a double. */
  p = (int *) &x;

  /* The next statement does not operate as
      expected. */
  y = *p;


  printf("%f", y); /* won't output 100.1 */
  return 0;
}

listing 4
#include <stdio.h>

int main(void)
{
  int x;
  int *p1, *p2;

  p1 = &x;
  p2 = p1;

  printf(" %p", p2); /* print the address of x, not x's value! */

  return 0;
}

listing 5
p1++;

listing 6
p1--;

listing 7
p1 = p1 + 12;

listing 8
if(p<q) printf("p points to lower memory than q\n");

listing 9
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

void push(int i);
int pop(void);

int  *tos, *p1, stack[SIZE];

int main(void)
{
  int value;

  tos = stack; /* tos points to the top of stack */
  p1 = stack; /* initialize p1 */

  do {
    printf("Enter value: ");
    scanf("%d", &value);
    if(value!=0) push(value);
    else printf("value on top is %d\n", pop());
  } while(value!=-1);

  return 0;
}

void push(int i)
{
  p1++;
  if(p1==(tos+SIZE)) {
    printf("Stack Overflow.\n");
    exit(1);
  }
  *p1 = i;
}

int pop(void)
{
  if(p1==tos) {
    printf("Stack Underflow.\n");
    exit(1);
  }
  p1--;
  return *(p1+1);
}

listing 10
return *p1 +1;

listing 11
char str[80], *p1;
p1 = str;

listing 12
str[4]

listing 14
/* Index s as an array. */
void putstr(char *s)
{
  register int t;

  for(t=0; s[t]; ++t) putchar(s[t]);
}

/* Access s as a pointer. */
void putstr(char *s)
{
  while(*s) putchar(*s++);
}

listing 15
int *x[10];

listing 16
x[2] = &var;

listing 17
*x[2]

listing 18
void display_array(int *q[])
{
  int t;

  for(t=0; t<10; t++)
    printf("%d ", *q[t]);
}

listing 19
void syntax_error(int num)
{
  static char *err[] = {
    "Cannot Open File\n",
    "Read Error\n",
    "Write Error\n",
    "Media Failure\n"
  };

  printf("%s", err[num]);
}

listing 20
float **newbalance;

listing 21
#include <stdio.h>

int main(void)
{
  int x, *p, **q;

  x = 10;
  p = &x;
  q = &p;

  printf("%d", **q); /* print the value of x */

  return 0;
}

listing 22
/* look up a name */
int search(char *p[], char *name)
{
  register int t;

  for(t=0; p[t]; ++t)
    if(!strcmp(p[t], name)) return t;

    return -1; /* not found */
}

listing 23
char *p = "hello world";

listing 24
#include <stdio.h>
#include <string.h>

char *p = "hello world";

int main(void)
{
  register int t;

  /* print the string forward and backwards */
  printf(p);
  for(t=strlen(p)-1; t>-1; t--) printf("%c", p[t]);

  return 0;
}

listing 25
const char *p = "hello world";

listing 26
#include <stdio.h>
#include <string.h>

void check(char *a, char *b,
           int (*cmp)(const char *, const char *));

int main(void)
{
  char s1[80], s2[80];
  int (*p)(const char *, const char *);

  p = strcmp;

  gets(s1);
  gets(s2);

  check(s1, s2, p);

  return 0;
}

void check(char *a, char *b,
           int (*cmp)(const char *, const char *))
{
  printf("Testing for equality.\n");
  if(!(*cmp)(a, b)) printf("Equal");
  else printf("Not Equal");
}

listing 27
(*cmp)(a, b)

listing 28
cmp(a, b); 

listing 29
check(s1, s2, strcmp);

listing 30
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void check(char *a, char *b,
           int (*cmp)(const char *, const char *));
int numcmp(const char *a, const char *b);

int main(void)
{
  char s1[80], s2[80];

  gets(s1);
  gets(s2);

  if(isalpha(*s1))
         check(s1, s2, strcmp);
  else
         check(s1, s2, numcmp);

  return 0;
}

void check(char *a, char *b,
           int (*cmp)(const char *, const char *))
{
  printf("Testing for equality.\n");
  if(!(*cmp)(a, b)) printf("Equal");
  else printf("Not Equal");
}

int numcmp(const char *a, const char *b)
{
  if(atoi(a)==atoi(b)) return 0;
  else return 1;
}

listing 31
char *p;
p = malloc(1000); /* get 1000 bytes */

listing 32
p = (char *) malloc(1000);

listing 33
int *p;
p = (int *) malloc(50*sizeof(int));

listing 34
p = (int *) malloc(100);
if(!p) {
  printf("Out of memory.\n");
  exit(1);
}

listing 35
/* This program is wrong. */
int main(void)
{
  int x, *p;

  x = 10;
  *p = x;

  return 0;
}

listing 36
/* This program is wrong. */
#include <stdio.h>

int main(void)
{
  int x, *p;

  x = 10;
  p = x;

  printf("%d", *p);

  return 0;
}

listing 37
p = x;

listing 38
p = &x;

listing 39
char s[80], y[80];
char *p1, *p2;

p1 = s;
p2 = y;
if(p1 < p2) . . .

listing 40
int first[10], second[10];
int *p, t;

p = first;
for(t=0; t<20; ++t)  *p++ = t;

listing 41
/* This program has a bug. */
#include <string.h>
#include <stdio.h>

int main(void)
{
  char *p1;
  char s[80];

  p1 = s;
  do {
    gets(s);  /* read a string */

    /* print the decimal equivalent of each
       character */
    while(*p1) printf(" %d", *p1++);

  } while(strcmp(s, "done"));

  return 0;
}

listing 42
/* This program is now correct. */
#include <string.h>
#include <stdio.h> 

int main(void)
{
  char *p1;
  char s[80];

  do {
    p1 = s;
    gets(s);  /* read a string */

    /* print the decimal equivalent of each
       character */
    while(*p1) printf(" %d", *p1++);

  } while(strcmp(s, "done"));

  return 0;
}

