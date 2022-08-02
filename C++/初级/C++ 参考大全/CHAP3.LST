listing 1
/* Magic number program #1. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int magic; /* magic number */
  int guess; /* user's guess */

  magic = rand(); /* generate the magic number */

  printf("Guess the magic number: ");
  scanf("%d", &guess); 

  if(guess == magic) printf("** Right **");

  return 0;
}

listing 2
/* Magic number program #2. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int magic; /* magic number */
  int guess; /* user's guess */

  magic = rand(); /* generate the magic number */

  printf("Guess the magic number: ");
  scanf("%d", &guess);

  if(guess == magic) printf("** Right **");
  else printf("Wrong");

  return 0;
}

listing 3
if(i)
{
  if(j) statement 1;
  if(k) statement 2; /* this if */
  else  statement 3; /* is associated with this else */
}
else statement 4; /* associated with if(i) */

listing 4
/* Magic number program #3. */ 
#include <stdio.h>
#include <stdlib.h> 

int main(void) 
{
  int magic; /* magic number */
  int guess; /* user's guess */

  magic = rand(); /* get a random number */

  printf("Guess the magic number: ");
  scanf("%d", &guess); 

  if (guess == magic) {
    printf("** Right **");
    printf(" %d is the magic number\n", magic);
  }
  else {
    printf("Wrong, ");
    if(guess > magic) printf("too high\n");
    else printf("too low\n");
  }

  return 0;
}

listing 5
/* Magic number program #4. */
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
  int magic; /* magic number */
  int guess; /* user's guess */

  magic = rand(); /* generate the magic number */

  printf("Guess the magic number: ");
  scanf("%d", &guess);

  if(guess == magic) {
    printf("** Right ** ");
    printf("%d is the magic number", magic);
  }
  else if(guess > magic)
    printf("Wrong, too high");
  else printf("Wrong, too low");

  return 0;
}

listing 6
x = 10; 
y = x>9 ? 100 : 200;

listing 7
x = 10;
if(x>9) y = 100;
else y = 200;

listing 8
#include <stdio.h>

int main(void)
{
  int isqrd, i;

  printf("Enter a number: ");
  scanf("%d", &i);

  isqrd = i>0 ? i*i : -(i*i);

  printf("%d squared is %d", i, isqrd);

  return 0;
}

listing 9
#include <stdio.h>

int f1(int n);
int f2(void);

int main(void)
{
  int t;

  printf("Enter a number: ");
  scanf("%d", &t);

  /* print proper message */
  t ? f1(t) + f2() : printf("zero entered.\n");

  return 0;
}

int f1(int n)
{
  printf("%d ", n);
  return 0;
}

int f2(void)
{
  printf("entered.\n");
  return 0;
}

listing 10
/* Magic number program #5. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int magic;
  int guess;

  magic = rand(); /* generate the magic number */

  printf("Guess the magic number: ");
  scanf("%d", &guess);

  if(guess == magic) {
    printf("** Right ** ");
    printf("%d is the magic number", magic);
  }
  else
    guess > magic ? printf("High") : printf("Low");

  return 0;
} 

listing 11
/* Divide the first number by the second. */

#include <stdio.h>

int main(void)
{
  int a, b;

  printf("Enter two numbers: ");
  scanf("%d%d", &a, &b);

  if(b) printf("%d\n", a/b);
  else printf("Cannot divide by zero.\n");

  return 0;
}

listing 12
if(b != 0) printf("%d\n", a/b);

listing 13
void menu(void)
{
  char ch;

  printf("1. Check Spelling\n");
  printf("2. Correct Spelling Errors\n");
  printf("3. Display Spelling Errors\n");
  printf("Strike Any Other Key to Skip\n");
  printf("      Enter your choice: ");

  ch = getchar(); /* read the selection from
                     the keyboard */

  switch(ch) {
    case '1':
      check_spelling();
      break;
    case '2':
      correct_errors();
      break;
    case '3':
      display_errors();
      break;
    default :
      printf("No option selected");
  }
} 

listing 14
/* Process a value */
void inp_handler(int i)
{
  int flag; 

  flag = -1; 

  switch(i) {
    case 1:  /* These cases have common */
    case 2:  /* statement sequences. */
    case 3:
      flag = 0;
      break;
    case 4:
      flag = 1;
    case 5:
      error(flag);
      break;
    default:
      process(i);
  }
}

listing 15
flag = 0;
break;

listing 16
switch(x) {
  case 1:
    switch(y) {
      case 0: printf("Divide by zero error.\n");
              break;
      case 1: process(x,y);
    }
    break;
  case 2:
    .
    .
    .

listing 17
#include <stdio.h>

int main(void)
{
  int x; 

  for(x=1; x <= 100; x++) printf("%d ", x);

  return 0;
} 

listing 18
for(x=100; x != 65; x -= 5) {
  z = x*x;
  printf("The square of %d, %f", x, z);
}

listing 19
x = 10;
for(y=10; y!=x; ++y) printf("%d", y);
printf("%d", y);  /* this is the only printf()
                     statement that will execute */

listing 20
for(x=0, y=0; x+y<10; ++x) {
  y = getchar();
  y = y - '0'; /* subtract the ASCII code for 0
                  from y */
    .
    .
    .
}

listing 21
/* Demonstrate multiple loop control variables. */
#include <stdio.h>
#include <string.h>

void converge(char *targ, char *src);

int main(void)
{
  char target[80] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

  converge(target, "This is a test of converge().");
  printf("Final string: %s\n", target);

  return 0;
} 

/* This function copies one string into another. 
   It copies characters to both the ends,
   converging at the middle. */
void converge(char *targ, char *src)
{
  int i, j; 

  printf("%s\n", targ);
  for(i=0, j=strlen(src); i<=j; i++, j--) {
    targ[i] = src[i];
    targ[j] = src[j];
    printf("%s\n", targ);
  }
}

listing 22
void sign_on(void)
{
  char str[20];
  int x;

  for(x=0; x<3 && strcmp(str, "password"); ++x) {
    printf("Enter password please:");
    gets(str);
  }

  if(x==3) return;
  /* else log user in ... */
}

listing 23
#include <stdio.h>

int sqrnum(int num);
int readnum(void);
int prompt(void);

int main(void)
{
  int t;

  for(prompt(); t=readnum(); prompt())
    sqrnum(t);

  return 0;
} 

int prompt(void) 
{
  printf("Enter a number: ");
  return 0;
} 

int readnum(void)
{
  int t;

  scanf("%d", &t);
  return t;
}

int sqrnum(int num)
{
  printf("%d\n", num*num);
  return num*num;
}

listing 24
for(x=0; x!=123; ) scanf("%d", &x);

listing 25
gets(s);  /* read a string into s */
if(*s) x = strlen(s); /* get the string's length */
else x = 10;

for( ; x<10; ) {
  printf("%d", x);
  ++x;
}

listing 26
for( ; ; ) printf("This loop will run forever.\n");

listing 27
ch = '\0'; 

for( ; ; ) {
  ch = getchar(); /* get a character */
  if(ch=='A') break; /* exit the loop */
} 

printf("you typed an A");

listing 28
for( ; *str == ' '; str++) ;

listing 29
for(t=0; t<SOME_VALUE; t++) ;

listing 30
char wait_for_char(void)
{
  char ch; 

  ch = '\0';  /* initialize ch */
  while(ch != 'A') ch = getchar();
  return ch;
}

listing 31
#include <stdio.h>
#include <string.h>

void pad(char *s, int length);

int main(void)
{
  char str[80];

  strcpy(str, "this is a test");
  pad(str, 40);
  printf("%d", strlen(str));

  return 0;
} 

/* Add spaces to the end of a string. */
void pad(char *s, int length)
{
  int l;

  l = strlen(s); /* find out how long it is */

  while(l<length) {
    s[l] = ' '; /* insert a space */
    l++;
  }
  s[l]= '\0'; /* strings need to be
                 terminated in a null */
}

listing 32
void func1(void)
{
  int working;

  working = 1; /* i.e., true */

  while(working) {
    working = process1();
    if(working)
      working = process2();
    if(working)
      working = process3();
  }
}

listing 33
while((ch=getchar()) != 'A') ;

listing 34
do {
  scanf("%d", &num);
} while(num > 100);

listing 35
void menu(void)
{
  char ch;

  printf("1. Check Spelling\n");
  printf("2. Correct Spelling Errors\n");
  printf("3. Display Spelling Errors\n");
  printf("      Enter your choice: ");

  do {
    ch = getchar(); /* read the selection from
                       the keyboard */
    switch(ch) {
      case '1':
        check_spelling();
        break;
      case '2':
        correct_errors();
        break;
      case '3':
        display_errors();
        break;
    }
  } while(ch!='1' && ch!='2' && ch!='3');
}

listing 36
/* i is local to for loop; j is known outside loop. */
int j; 
for(int i = 0; i<10; i++)
  j = i * i;

/* i = 10; // *** Error *** -- i not known here! */


listing 37
if(int x = 20) {
  x = x - y;
  if(x>10) y = 0;
}

listing 38
x = 1;
loop1:
  x++;
  if(x<100) goto loop1;

listing 39
#include <stdio.h>

int main(void)
{
  int t;

  for(t=0; t<100; t++) {
    printf("%d ", t);
    if(t==10) break;
  }

  return 0;
}

listing 40
void look_up(char *name)
{
  do {
    /* look up names ... */
    if(kbhit()) break;
  } while(!found);
  /* process match */
}

listing 41
for(t=0; t<100; ++t) {
  count = 1;
  for(;;) {
    printf("%d ", count);
    count++;
    if(count==10) break;
  }
}

listing 42
#include <stdlib.h>

int main(void)
{
   if(!virtual_graphics()) exit(1);
   play();
   /* ... */
}
/* .... */

listing 43
void menu(void)
{
  char ch;

  printf("1. Check Spelling\n");
  printf("2. Correct Spelling Errors\n");
  printf("3. Display Spelling Errors\n");
  printf("4. Quit\n");
  printf("      Enter your choice: ");

  do {
    ch = getchar(); /* read the selection from
                     the keyboard */
      switch(ch) {
        case '1':
          check_spelling();
          break;
        case '2':
          correct_errors();
          break;
        case '3':
          display_errors();
          break;
        case '4':
          exit(0); /* return to OS */
      }
    } while(ch!='1' && ch!='2' && ch!='3');
  }

listing 44
/* Count spaces */
#include <stdio.h>

int main(void)
{
  char s[80], *str;
  int space;

  printf("Enter a string: ");
  gets(s);
  str = s; 

  for(space=0; *str; str++) {
    if(*str != ' ') continue;
    space++;
  }
  printf("%d spaces\n", space);

  return 0;
}

listing 45
void code(void)
{
  char done, ch;

  done = 0;
  while(!done) {
    ch = getchar();
    if(ch=='$') {
      done = 1;
      continue;
    }
    putchar(ch+1); /* shift the alphabet one
                      position higher */
  }
}

listing 46
func();  /* a function call */
a = b+c; /* an assignment statement */
b+f();   /* a valid, but strange statement */
;        /* an empty statement */

listing 47
#include <stdio.h>

int main(void)
{
  int i;

  {  /* a block statement */
     i = 120;
     printf("%d", i);
  }

  return 0;
}

