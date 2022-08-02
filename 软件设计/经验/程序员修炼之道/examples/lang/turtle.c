/**
  * Parse a simple set of tutrle graphics commands.
  */

#include <stdio.h>
#define ARG    1
#define NO_ARG 0

#define ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))

/* Dummy handler functions */
void doSelectPen(int cmd, int arg)  { printf("P %d\n", arg); }
void doPenUp(int cmd, int arg)      { printf("U\n", arg); }
void doPenDown(int cmd, int arg)    { printf("D\n", arg); }
void doPenDir(int cmd, int arg)     { printf("%c %d\n", cmd, arg); }

/* Because we want to make the language extendable, we'll make the parser 
 * table driven. Each entry in the table contains the command letter, a
 * flag to say whether an argument is required and the name of the
 * routine to call to handle that particular command. 
 */

/*START:table*/
typedef struct {
  char  cmd;              /* the command letter */
  int hasArg;             /* does it take an argument */
  void (*func)(int, int); /* routine to call */
} Command;

static Command cmds[] = {
  { 'P',  ARG,     doSelectPen },
  { 'U',  NO_ARG,  doPenUp },
  { 'D',  NO_ARG,  doPenDown },
  { 'N',  ARG,     doPenDir },
  { 'E',  ARG,     doPenDir },
  { 'S',  ARG,     doPenDir },
  { 'W',  ARG,     doPenDir }
};
/*END:table*/

/* The function that looks up a command performs a linear search of the */
/* table, returning either the matching entry or \CF{NULL}. */

/*START:findcmd*/
Command *findCommand(int cmd) {
  int i;

  for (i = 0; i < ARRAY_SIZE(cmds); i++) {
    if (cmds[i].cmd == cmd)
      return cmds + i;
  }

  fprintf(stderr, "Unknown command '%c'\n", cmd);
  return 0;
}
/*END:findcmd*/

/* Read a numeric argument, returning TRUE if found */
/*START:getarg*/
int getArg(const char *buff, int *result) {
  return sscanf(buff, "%d", result) == 1;
}
/*END:getarg*/


/* The main program is pretty simple: read a line, look up the command, */
/* get the argument if required, then call the handler function. */

int main(int argc, char **argv) {
  char buff[100];

  /*START:main*/
  while (fgets(buff, sizeof(buff), stdin)) {
    
    Command *cmd = findCommand(*buff);
    
    if (cmd) {
      int   arg = 0;
    
      if (cmd->hasArg && !getArg(buff+1, &arg)) {
        fprintf(stderr, "'%c' needs an argument\n", *buff);
        continue;
      } 
    
      cmd->func(*buff, arg);
    }
  }
  /*END:main*/
}
