#pragma once

#include <signal.h>

#define __COPYRIGHT(value)
#define __RCSID(value)

extern char* optarg;
extern int optind;
extern int optopt;

int getopt(int argc, char** argv, char* p);

#define _PATH_BSHELL 0
#define SIGCHLD 0
#define SIGQUIT 0

typedef int pid_t;

typedef _crt_signal_t sig_t;

union wait
{
    int w_status;
};