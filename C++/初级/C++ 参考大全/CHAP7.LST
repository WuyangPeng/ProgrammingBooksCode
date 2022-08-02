listing 1
struct addr
{
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
};

listing 2
struct addr addr_info;

listing 3
addr addr_info;

listing 4
struct addr {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
} addr_info, binfo, cinfo;

listing 5
struct {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  unsigned long int zip;
} addr_info;

listing 6
addr_info.zip = 12345;

listing 7
printf("%lu", addr_info.zip);

listing 8
gets(addr_info.name);

listing 9
register int t;

for(t=0; addr_info.name[t]; ++t)
  putchar(addr_info.name[t]);

listing 10
#include <stdio.h>

int main(void)
{
  struct {
    int a;
    int b;
  } x, y; 

  x.a = 10;

  y = x;  /* assign one structure to another */

  printf("%d", y.a);

  return 0;
}

listing 11
struct addr addr_info[100];

listing 12
printf("%lu", addr_info[2].zip);

listing 13
struct fred
{
  char x;
  int y;
  float z;
  char s[10];
} mike;

listing 14
func(mike.x);    /* passes character value of x */
func2(mike.y);   /* passes integer value of y */
func3(mike.z);   /* passes float value of z */
func4(mike.s);   /* passes address of string s */
func(mike.s[2]); /* passes character value of s[2] */

listing 15
func(&mike.x);    /* passes address of character x */
func2(&mike.y);   /* passes address of integer y */
func3(&mike.z);   /* passes address of float z */
func4(mike.s);    /* passes address of string s */
func(&mike.s[2]); /* passes address of character s[2] */

listing 16
#include <stdio.h>

/* Define a structure type. */
struct struct_type {
  int a, b;
  char ch;
} ;

void f1(struct struct_type parm);

int main(void)
{
  struct struct_type arg;

  arg.a = 1000;

  f1(arg);

  return 0;
}

void f1(struct struct_type parm)
{
  printf("%d", parm.a);
}

listing 17
/* This program is incorrect and will not compile. */
#include <stdio.h>

/* Define a structure type. */
struct struct_type {
  int a, b;
  char ch;
} ;

/* Define a structure similar to struct_type,
   but with a different name. */
struct struct_type2 {
  int a, b;
  char ch;
} ;

void f1(struct struct_type2 parm);

int main(void)
{
  struct struct_type arg;

  arg.a = 1000;

  f1(arg); /* type mismatch */

  return 0;
}

void f1(struct struct_type2 parm)
{
  printf("%d", parm.a);
}

listing 18
struct addr *addr_pointer;

listing 19
struct bal {
  float balance;
  char name[80];
} person;

struct bal *p;  /* declare a structure pointer */

listing 20
p = &person;

listing 21
p->balance

listing 22
/* Display a software timer. */
#include <stdio.h>

#define DELAY 128000

struct my_time {
  int hours;
  int minutes;
  int seconds;
} ;

void display(struct my_time *t);
void update(struct my_time *t);
void delay(void);

int main(void)
{
  struct my_time systime;

  systime.hours = 0;
  systime.minutes = 0;
  systime.seconds = 0;

  for(;;) {
    update(&systime);
    display(&systime);
  }

  return 0;
}

void update(struct my_time *t)
{
  t->seconds++;
  if(t->seconds==60) {
    t->seconds = 0;
    t->minutes++;
  }

  if(t->minutes==60) {
    t->minutes = 0;
    t->hours++;
  }

  if(t->hours==24) t->hours = 0;
  delay();
}

void display(struct my_time *t)
{
  printf("%02d:", t->hours);
  printf("%02d:", t->minutes);
  printf("%02d\n", t->seconds);
}

void delay(void)
{
  long int t;

  /* change this as needed */
  for(t=1; t<DELAY; ++t) ;
}

listing 23
if(t->hours==24) t->hours = 0;

listing 24
struct x {
  int a[10][10]; /* 10 x 10 array of ints */
  float b;
} y;

listing 25
y.a[3][7]

listing 26
struct emp {
  struct addr address; /* nested structure */
  float wage;
} worker;

listing 27
worker.address.zip = 93456;

listing 28
struct status_type {
  unsigned delta_cts: 1;
  unsigned delta_dsr: 1;
  unsigned tr_edge:   1;
  unsigned delta_rec: 1;
  unsigned cts:       1;
  unsigned dsr:       1;
  unsigned ring:      1;
  unsigned rec_line:  1;
} status;

listing 29
status = get_port_status();
if(status.cts) printf("clear to send");
if(status.dsr) printf("data ready");

listing 30
status.ring = 0;

listing 31
struct status_type {
  unsigned :    4;
  unsigned cts: 1;
  unsigned dsr: 1;
} status;

listing 32
struct emp {
  struct addr address;
  float pay;
  unsigned lay_off:    1; /* lay off or active */
  unsigned hourly:     1; /* hourly pay or wage */
  unsigned deductions: 3; /* IRS deductions */
};

listing 33
union u_type {
  int i;
  char ch;
};

listing 34
union u_type cnvt;

listing 35
u_type cnvt;

listing 36
cnvt.i = 10;

listing 37
void func1(union u_type *un)
{
  un->i = 10; /* assign 10 to cnvt using
                 function */
}

listing 38
union pw {
  short int i;
  char ch[2];
};

listing 39
#include <stdio.h>

union pw {
  short int i;
  char ch[2];
};

int putw(short int num, FILE *fp);

int main(void)
{
  FILE *fp;

  fp = fopen("test.tmp", "wb+");

  putw(1000, fp);  /* write the value 1000 as an integer */
  fclose(fp);

  return 0;
}

int putw(short int num, FILE *fp)
{
  union pw word;

  word.i = num;

  putc(word.ch[0], fp); /* write first half */
  return putc(word.ch[1], fp); /* write second half */
}

listing 40
enum coin { penny, nickel, dime, quarter,
            half_dollar, dollar};

listing 41
enum coin money;

listing 42
coin money;

listing 43
money = dime;
if(money==quarter) printf("Money is a quarter.\n");

listing 44
printf("%d %d", penny, dime);

listing 45
enum coin { penny, nickel, dime, quarter=100,
            half_dollar, dollar};

listing 46
/* this will not work */
money = dollar;
printf("%s", money);

listing 47
/* this code is wrong */
strcpy(money, "dime");

listing 48
switch(money) {
  case penny: printf("penny");
    break;
  case nickel: printf("nickel");
    break;
  case dime: printf("dime");
    break;
  case quarter: printf("quarter");
    break;
  case half_dollar: printf("half_dollar");
    break;
  case dollar: printf("dollar");
}

listing 49
char name[][12]={
  "penny",
  "nickel",
  "dime",
  "quarter",
  "half_dollar",
  "dollar"
};
printf("%s", name[money]);

listing 50
char ch;
int i;
double f;

printf("%d", sizeof(ch));
printf("%d", sizeof(i));
printf("%d", sizeof(f));

listing 51
struct s {
  char ch;
  int i;
  double f;
} s_var;

listing 52
union u {
  char ch;
  int i;
  double f;
} u_var;

listing 53
typedef float balance;

listing 54
balance over_due;

listing 55
typedef balance overdraft;

