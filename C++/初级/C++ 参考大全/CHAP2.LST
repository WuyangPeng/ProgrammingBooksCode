listing 1
int i,j,l;
short int si;
unsigned int ui;
double balance, profit, loss;

listing 2
void func1(void)
{
  int x;

  x = 10;
}

void func2(void)
{
  int x;

  x = -199;
}

listing 3
void f(void)
{
  int t; 

  scanf("%d%*c", &t); 

  if(t==1) {
    char s[80];  /* this is created only upon
                    entry into this block */
    printf("Enter name:");
    gets(s);
    /* do something ... */
  }
}

listing 4
/* This function is in error if compiled as
   a C program, but perfectly acceptable if 
   compiled as a C++ program.
*/
void f(void)
{
  int i;

  i = 10;

  int j;  /* this line will cause an error */

  j = 20;
}

listing 5
#include <stdio.h>

void f(void); 

int main(void)
{
  int i; 

  for(i=0; i<10; i++)  f();

  return 0;
}

void f(void)
{
  int j = 10;

  printf("%d ", j);

  j++;  /* this line has no lasting effect */
}

listing 6
/* Return 1 if c is part of string s; 0 otherwise */
int is_in(char *s, char c)
{
  while(*s)
    if(*s==c) return 1;
    else s++;

  return 0;
}

listing 7
#include <stdio.h>
int count;  /* count is global  */

void func1(void);
void func2(void);

int main(void)
{
  count = 100;
  func1();

  return 0;
}

void func1(void) 
{
  int temp;

  temp = count;
  func2();
  printf("count is %d", count); /* will print 100 */
}

void func2(void)
{
  int count;

  for(count=1; count<10; count++)
    putchar('.');
}

listing 8
const int a=10;

listing 9
#include <stdio.h>

void sp_to_dash(const char *str);

int main(void)
{
  sp_to_dash("this is a test");

  return 0;
}

void sp_to_dash(const char *str)
{
  while(*str) {
    if(*str== ' ') printf("%c", '-');
    else printf("%c", *str);
    str++;
  }
}

listing 10
/* This is wrong. */
void sp_to_dash(const char *str)
{
  while(*str) {
    if(*str==' ' ) *str = '-'; /* can't do this; str is const */
    printf("%c", *str);
    str++;
  }
}

listing 11
const volatile char *port = (const volatile char *) 0x30;

listing 12
#include <stdio.h>

int main(void)
{
  extern int first, last; /* use global vars */

  printf("%d %d", first, last);

  return 0;
}

/* global definition of first and last */
int first = 10, last = 20;


listing 13
int series(void)
{
  static int series_num;

  series_num = series_num+23;
  return series_num;
} 

listing 14
int series(void)
{
  static int series_num = 100;

  series_num = series_num+23;
  return series_num;
}

listing 15
/* This must all be in one file - preferably by itself. */

static int series_num;
void series_start(int seed);
int series(void);

int series(void)
{
  series_num = series_num+23;
  return series_num;
}

/* initialize series_num */
void series_start(int seed)
{
  series_num = seed;
}

listing 16
int int_pwr(register int m,  register int e)
{
  register int temp;

  temp = 1;

  for(; e; e--) temp = temp * m;
  return temp;
}

listing 17
char ch = 'a';
int first = 0;
float balance = 123.23;

listing 18
wchar_t wc;
wc = L'A';

listing 19
int hex = 0x80;   /* 128 in decimal */
int oct = 012;    /* 10 in decimal */

listing 20
#include <stdio.h>

int main(void)
{
  printf("\n\tThis is a test.");

  return 0;
}

listing 21
int x;
char ch;
float  f;

void func(void)
{
  ch = x;    /* line 1 */
  x = f;     /* line 2 */
  f = ch;    /* line 3 */
  f = x;     /* line 4 */
}

listing 22
x = y = z = 0;

listing 23
int x, y;

x = 5;
y = 2;

printf("%d ", x/y);   /* will display 2 */
printf("%d ", x%y);   /* will display 1, the remainder of
                         the integer division */

x = 1;
y = 2;

printf("%d %d", x/y, x%y); /*  will display 0 1 */

listing 24
x = x+1;

listing 25
++x; 

listing 26
x = x-1;

listing 27
x--;

listing 28
x = x+1;

listing 29
++x;

listing 31
x = 10;
y = ++x;

listing 32
x = 10;
y = x++;

listing 33
#include <stdio.h>

int xor(int a, int b);

int main(void)
{
  printf("%d", xor(1, 0));
  printf("%d", xor(1, 1));
  printf("%d", xor(0, 1));
  printf("%d", xor(0, 0));

  return 0;
}

/* Perform a logical XOR operation using the
   two arguments. */
int xor(int a, int b)
{
  return (a || b) && !(a && b);
}

listing 34
int x; 

x = 100;
printf("%d", x>10);

listing 35
char get_char_from_modem(void)
{
  char ch;

  ch = read_modem(); /* get a character from the
                        modem port */
  return(ch & 127);
}

listing 36
/* A bit shift example. */
#include <stdio.h>

int main(void)
{
  unsigned int i;
  int j;

  i = 1;

  /* left shifts */
  for(j=0; j<4; j++) {
    i = i << 1;  /* left shift i by 1, which
                    is same as a multiply by 2 */
    printf("Left shift %d: %d\n", j, i);
  }

  /* right shifts */
  for(j=0; j<4; j++) {
    i = i >> 1;  /* right shift i by 1, which
                    is same as a division by 2 */
    printf("Right shift %d: %d\n", j, i);
  }

  return 0;
}

listing 37
/* A simple cipher function. */
char encode(char ch)
{
  return(~ch); /* complement it */
}

listing 38
x = 10;

y = x>9 ? 100 : 200;

listing 39
x = 10;

if(x>9) y = 100;
else y = 200;

listing 40
m = &count;

listing 41
q = *m; 

listing 42
char *ch;

listing 43
int x, *y, count;

listing 44
#include <stdio.h>

int main(void)
{
  int target, source;
  int *m;

  source = 10;
  m = &source;
  target = *m;

  printf("%d", target);

  return 0;
}

listing 45
double f;

printf("%d ", sizeof f);
printf("%d", sizeof(int));

listing 46
/* Write 6 integers to a disk file. */
void put_rec(int rec[6], FILE *fp)
{
  int len; 

  len = fwrite(rec, sizeof(int)*6, 1, fp);
  if(len != 1) printf("Write Error");
}

listing 47
x = (y=3, y+1);

listing 48
struct employee
{
  char name[80];
  int age;
  float wage;
} emp; 

struct employee *p = &emp; /* address of emp into p */

listing 49
emp.wage = 123.23;

listing 50
p->wage = 123.23;

listing 51
#include <stdio.h>
char s[80];

int main(void)
{
  s[3] = 'X';
  printf("%c", s[3]);

  return 0;
} 

listing 52
x = f1() + f2();

listing 53
(float) x/2

listing 54
#include <stdio.h>

int main(void) /* print i and i/2 with fractions */
{
  int i;

  for(i=1; i<=100; ++i)
    printf("%d / 2 is: %f\n", i, (float) i /2);

  return 0;
}

listing 55
x=10/y~(127/x);

x = 10 / y ~(127/x);

listing 56
x = y/3-34*temp+127;

x = (y/3) - (34*temp) + 127;

listing 57
x = x+10; 

listing 58
x += 10;

listing 59
x = x-100; 

listing 60
x -= 100;

