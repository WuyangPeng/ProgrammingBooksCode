#include <stdio.h>
#include <stdarg.h>

int logdata(const char *fname, const char *fmt, ...)
{ // log formatted data to file fname
int res = -1;
FILE *fp = fopen(fname, "a");
if (fp)
  { // set up argument  list, call vfprintf
  va_list ap;
  va_start(ap, fmt);
  res = vfprintf(fp, fmt, ap);
  fclose(fp);
  va_end(ap);
  }
return res;
}

int main()
  { // demonstrate use of variable-length argument lists
  FILE *fp;
  char buf[128];
  logdata("test.txt", "%d\n", 3);
  logdata("test.txt", "%d %d %d\n", 3, 4, 5);
  fp = fopen("test.txt", "r");
  while (fgets(buf, sizeof(buf), fp))
    printf(buf);
  fclose(fp);
  return 0;
  }