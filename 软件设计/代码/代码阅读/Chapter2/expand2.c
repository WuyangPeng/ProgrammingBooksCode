#include <string.h>

char* optarg = "5";
int optind = 1;

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