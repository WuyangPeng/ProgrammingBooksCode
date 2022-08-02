#if __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "BookTools.h"

#ifdef _MSC_VER
#include<ctime>
unsigned long time_fn(long (*fn)(void), int nrSamples)
{
	unsigned long average = 0;
	clock_t tBegin, tEnd;

	for (int i = 0; i < nrSamples; i++)
	{
		tBegin = clock();
		fn();
		tEnd = clock();

		average += tEnd - tBegin;
	}

	return ((unsigned long)average / nrSamples);
}

#else
#include<time.h>
unsigned long time_fn(long (*fn)(void), int nrSamples)
{
	unsigned long average = 0;
	clock_t tBegin, tEnd;

	for (int i = 0; i < nrSamples; i++)
	{
		tBegin = clock();
		fn();
		tEnd = clock();

		average += tEnd - tBegin;
	}

	return ((unsigned long)average / (nrSamples*1000));
}
#endif

void print_time(long msec)
{
    int hour, min, sec;

    hour = (int)(msec / (60*60*1000));
  msec = msec % (60*60*1000);

    min = (int)(msec / (60*1000));
  msec = msec % (60*1000);

    sec = (int)(msec / (1000));
  msec = msec % (1000);

  printf("%02dh %02dm %02ds %03dms\n", hour, min, sec, msec);
}

struct smallstr {char q;};
struct bit {unsigned q: 1;};
union  un  {char a;};

void system_info()
{
	printf("Sizeof char        : %d\n", sizeof(char));
	printf("Sizeof short       : %d\n", sizeof(short));
	printf("Sizeof short int   : %d\n", sizeof(short int));
	printf("Sizeof long        : %d\n", sizeof(long));
	printf("Sizeof int         : %d\n", sizeof(int));
	printf("Sizeof float       : %d\n", sizeof(float));
	printf("Sizeof double      : %d\n", sizeof(double));
	printf("Sizeof long double : %d\n", sizeof(long double));
#ifdef _MSC_VER
	printf("Sizeof int64       : %d\n", sizeof(__int64));
#else
	printf("Sizeof long long   : %d\n", sizeof(long long));
#endif
	printf("Min sizeof struct  : %d\n", sizeof(struct smallstr));
	printf("Min sizeof bitfield: %d\n", sizeof(struct bit));
	printf("Min sizeof union   : %d\n", sizeof(un));
}


void DisplayASCIITable()
{
        int i, j;
        char buf[512];
        char header[] = "0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F  \n-+---------------------------------------------------------------";

          for (i=0; i < 256; i++)
                buf[i] = (unsigned char)i;

        printf("\n |%s\n", header);
        for (i = 0; i < 16; i++)
        {
                printf("%c|", header[i*4]);
                for (j=0; j < 16 ; j++)
                {
                   switch((i*16)+j)
                   { 
                        case 0 : printf("NUL ");
                                 break;                 
                        case 1 : printf("SOH ");
                                 break;                 
                        case 2 : printf("SIX ");
                                 break;                 
                        case 3 : printf("EIX ");
                                 break;                 
                        case 4 : printf("EOI ");
                                 break;                 
                        case 5 : printf("ENQ ");
                                 break;                 
                        case 6 : printf("ACK ");
                                 break;                 
                        case 7 : printf("BEL ");
                                 break;                 
                        case 8 : printf("BS  ");
                                 break;                 
                        case 9 : printf("TAB ");
                                 break;                 
                        case 10: printf("LF  ");
                                 break;                 
                        case 11: printf("VT  ");
                                 break;                 
                        case 12: printf("FF  ");
                                 break;                 
                        case 13: printf("CR  ");
                                 break;                 
                        case 14: printf("SO  ");
                                 break;                 
                        case 15: printf("SI  ");
                                 break;                 
                        case 16: printf("SLE ");
                                 break;                 
                        case 17: printf("XON ");
                                 break;                 
                        case 18: printf("DC2 ");
                                 break;                 
                        case 19: printf("XOF ");
                                 break;                 
                        case 20: printf("DC4 ");
                                 break;                 
                        case 21: printf("NAK ");
                                 break;                 
                        case 22: printf("SYN ");
                                 break;                 
                        case 23: printf("EIB ");
                                 break;                 
                        case 24: printf("CAN ");
                                 break;                 
                        case 25: printf("EM  ");
                                 break;                 
                        case 26: printf("EOF ");
                                 break;                 
                        case 27: printf("ESC ");
                                 break;                 
                        case 28: printf("FS  ");
                                 break;                 
                        case 29: printf("GS  ");
                                 break;                 
                        case 30: printf("RS  ");
                                 break;                 
                        case 31: printf("US  ");
                                 break;                 
                        case 32: printf("SPC ");
                                 break;                 
                        default: printf("%c   ", isprint(buf[(i*16)+j]) ? buf[(i*16)+j] : '.');
                                 break;
                   }
                }
                printf("  (%3d - %3d)\n", (i*16)+j-16, (i*16)+j-1);
                if ( (i==3) || (i==7) || (i==11))
                   printf(" |\n");
        }
}

#if __cplusplus
}
#endif
