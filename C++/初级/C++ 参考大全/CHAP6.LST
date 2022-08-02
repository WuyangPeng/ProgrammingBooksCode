listing 1
f(int i, int k, int j) /* correct */
f(int i, k, float j)   /* incorrect */

listing 2
/* Return 1 if c is part of string s; 0 otherwise. */
int is_in(char *s,  char c)
{
  while(*s)
    if(*s==c) return 1;
    else s++;
  return 0;
}

listing 3
#include <stdio.h>

int sqr(int x);

int main(void)
{
  int t=10;

  printf("%d %d", sqr(t), t);

  return 0;
}

int sqr(int x)
{
  x = x*x;
  return(x);
}

listing 4
void swap(int *x, int *y)
{
  int temp;

  temp = *x;  /* save the value at address x */
  *x = *y;    /* put y into x */
  *y = temp;  /* put x into y */
}

listing 5
void swap(int *x, int *y);

int main(void)
{
  int i, j;

  i = 10;
  j = 20;

  printf("%d %d\n", i, j);

  swap(&i, &j); /* pass the addresses of i and j */

  printf("%d %d\n", i, j);

  return 0;
}

listing 6
#include <stdio.h>
#include <ctype.h>

void print_upper(char *string);

int main(void)
{
  char s[80];

  gets(s);
  print_upper(s); 
  printf("\ns is now uppercase: %s", s);
  return 0;
}

/* Print a string in uppercase. */
void print_upper(char *string)
{
  register int t;

  for(t=0; string[t]; ++t)  {
    string[t] = toupper(string[t]);
    putchar(string[t]);
  }
}

listing 7
#include <stdio.h>
#include <ctype.h>

void print_upper(char *string);

int main(void)
{
  char s[80];

  gets(s);
  print_upper(s);
  printf("\ns is unchanged: %s", s);

  return 0;
}

void print_upper(char *string)
{
  register int t;

  for(t=0; string[t]; ++t)
    putchar(toupper(string[t]));
}

listing 8
/* A simple version of the standard
   gets() library function. */
char *xgets(char *s)
{
  char ch, *p;
  int t;

  p = s;  /* gets() returns a pointer to s */

  for(t=0; t<80; ++t){
    ch = getchar();

    switch(ch) {
      case '\n':
        s[t] = '\0'; /* terminate the string */
        return p;
      case '\b':
        if(t>0) t--;
        break;
      default:
        s[t] = ch;
    }
  }
  s[79] = '\0';
  return p;
}

listing 9
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if(argc!=2) {
    printf("You forgot to type your name.\n");
    exit(1);
  }
  printf("Hello %s", argv[1]);

  return 0;
}

listing 10
run Spot, run

listing 11
Herb,Rick,Fred

listing 12
char *argv[];

listing 13
/* Countdown program. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int disp, count;

  if(argc<2) {
    printf("You must enter the length of the count\n");
    printf("on the command line.  Try again.\n");
    exit(1);
  }

  if(argc==3 && !strcmp(argv[2], "display")) disp = 1;
  else disp = 0;

  for(count=atoi(argv[1]); count; --count)
    if(disp) printf("%d\n", count);

  putchar('\a');  /* this will ring the bell */
  printf("Done");

  return 0;
}

listing 14
#include <stdio.h>

int main(int argc, char *argv[])
{
  int t, i;

  for(t=0; t<argc; ++t) {
    i = 0;

    while(argv[t][i]) {
      putchar(argv[t][i]);
      ++i;
    }
    printf("\n");
  }

  return 0;
}

listing 15
#include <string.h>
#include <stdio.h>

void pr_reverse(char *s);

int main(void)
{
  pr_reverse("I like C++");

  return 0;
}

void pr_reverse(char *s)
{
  register int t;

  for(t=strlen(s)-1; t>=0; t--) putchar(s[t]);
}

listing 16
#include <stdio.h>

int find_substr(char *s1, char *s2);

int main(void)
{
  if(find_substr("C++ is fun", "is") != -1)
    printf("substring is found");

  return 0;
}

/* Return index of first match of s2 in s1. */
int find_substr(char *s1, char *s2)
{
  register int t;
  char *p, *p2;

  for(t=0; s1[t]; t++) {
    p = &s1[t];
    p2 = s2;

    while(*p2 && *p2==*p) {
      p++;
      p2++;
    }
    if(!*p2) return t; /* 1st return */
  }
   return -1; /* 2nd return */
}

listing 17
x = power(y);
if(max(x,y) > 100) printf("greater");
for(ch=getchar(); isdigit(ch); ) ... ;

listing 18
swap(x,y) = 100; /* incorrect statement */

listing 19
#include <stdio.h>

int mul(int a, int b);

int main(void)
{
  int x, y, z;

  x = 10;   y = 20;
  z = mul(x, y);           /* 1 */
  printf("%d", mul(x,y));  /* 2 */
  mul(x, y);               /* 3 */

  return 0;
}

int mul(int a, int b)
{
  return a*b;
}

listing 20
/* Return pointer of first occurrence of c in s. */
char *match(char c, char *s)
{
  while(c!=*s && *s) s++;
  return(s);
}

listing 21
#include <stdio.h>

char *match(char c, char *s);  /* prototype */

int main(void)
{
  char s[80], *p, ch;

  gets(s);
  ch = getchar();
  p = match(ch, s);

  if(*p)  /* there is a match */
    printf("%s ", p);
  else
    printf("No match found.");

  return 0;
}

listing 22
void print_vertical(char *str)
{
  while(*str)
    printf("%c\n", *str++);
}

listing 23
#include <stdio.h>

void print_vertical(char *str);  /* prototype */

int main(int argc, char *argv[])
{
  if(argc > 1) print_vertical(argv[1]);

  return 0;
}

void print_vertical(char *str)
{
  while(*str)
    printf("%c\n", *str++);
}

listing 24
/* recursive */
int factr(int n) {
  int answer;

  if(n==1) return(1);
  answer = factr(n-1)*n; /* recursive call */
  return(answer);
}

/* non-recursive */
int fact(int n) {
  int t, answer;

  answer = 1;

  for(t=1; t<=n; t++)
    answer=answer*(t);

  return(answer);
}

listing 25
/* This program uses a function prototype to
   enforce strong type checking. */

void sqr_it(int *i); /* prototype */

int main(void)
{
  int x;

  x = 10;
  sqr_it(x);  /* type mismatch */

  return 0;
}

void sqr_it(int *i)
{
  *i = *i * *i;
}

listing 26
#include <stdio.h>

/* This definition will also serve
   as a prototype within this program. */
void f(int a, int b)
{
  printf("%d ", a % b);
}

int main(void)
{
  f(10,3);

  return 0;
}

listing 27
int f(); /* C++ prototype for a function with no parameters */

listing 28
float f(void);

listing 29
int func(int a, int b, ...);

listing 30
int func(...); /* illegal */

listing 31
float f(int a, int b, char ch)
{
  /* ... */
}

listing 32
float f(a, b, ch)
int a, b;
char ch;
{
  /* ... */
}

