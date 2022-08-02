#ifndef __TEXTFILE_H
#define __TEXTFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEBUFSIZE    4096
#define bufsize        32000
#define itemsize       1

#define CR    0x0d
#define LF    0x0a
#define CRLF  0x0d0a
#define LFCR  0x0a0d

class TextFile
{
private:

  FILE *fp;

  unsigned long bufindex;
  unsigned long maxbuf;
  unsigned long filebufsize;
  unsigned char buf[LINEBUFSIZE];

  char filemode;

public:
  unsigned long linecount;
  unsigned char **listptr;

  TextFile(void){fp = NULL;}

  ~TextFile(){close();}
 

  int getline(char *s);
  int putline(char *s, int format = CRLF);

  int open(char *s, char mode = 'r');
  void close();


};

#endif
