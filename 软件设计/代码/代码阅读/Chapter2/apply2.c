#include "echo.h"

int optopt = 0;
char* optarg = "5";
int optind = 1;

int errx(int index, const char* message, ...)
{
    return 0;
}

int err(int index, const char* message, ...)
{
    return 0;
}

int sigmask(int mask)
{
    return mask;
}

int sigblock(int sig)
{
    return sig;
}

int vfork()
{
    return 0;
}

void sigsetmask(int mask)
{
}

int waitpid(pid_t v0, int* v1, int v2)
{
    return v2;
}

int getopt(int argc, char** argv, char* p)
{
    if (optind < argc)
    {
        optarg = argv[1] + 2;
        ++optind;

        return 't';
    }
    else
    {
        return -1;
    }
}