#include "BookTools.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <iomanip.h>

#define DATALEN 8192
#define LOOPSIZE 1000

#define SUMDATALEN	8192
#define SUMSTEP		2
unsigned long sumdata[SUMDATALEN];
 
unsigned char data[DATALEN];
unsigned char lookupTable[256];

char decLookup[256][4];
unsigned char upperLookup[256];

long CountBits1()
{
	int i, k;
	long j, count = 0;

	for (j = 0; j < LOOPSIZE; j++)
	{
		for (k = 0 ; k < DATALEN; k++)
			for (i = 1; i <= 256; i <<= 1)
			{
				if (data[k] & i)
					count++;
			}
	}
	return(count);
}

long CountBits2()
{
	int i;
	long j, count = 0;

	for (j = 0; j < LOOPSIZE; j++)
		for (i = 0; i < DATALEN; i++)
		{
			count +=	((data[i] & 128) >> 7)  +
						((data[i] & 64) >> 6)   +
						((data[i] & 32) >> 5)   +
						((data[i] & 16) >> 4)   +
						((data[i] &  8) >> 3)   +
						((data[i] &  4) >> 2)   +
						((data[i] &  2) >> 1)   +
						((data[i] &  1));
		}
		    
	return(count);
}

long CountBits3()
{
	int i, count = 0;
	long j;

	for (j = 0; j < LOOPSIZE; j++)
		for (i = 0; i < DATALEN; i++)
		{
			count+=lookupTable[data[i]]; 
		}
		return(count);
}


long Devisor1()
{
	int i, k;
	long j, count = 0;

	for (j = 0; j < LOOPSIZE; j++)
	{
		for (k = 0 ; k < DATALEN; k++)
			for (i = 1; i <= 256; i <<= 1)
			{
				if ((data[k] % i) == 0)
					count++;
			}
	}
	return(count);
}

long Devisor2()
{
	int i, k;
	long j, count = 0;

	for (j = 0; j < LOOPSIZE; j++)
	{
		for (k = 0; k < DATALEN; k++)
			for (i = 1; i <= 256; i <<= 1)
			{
				if ((data[k] & (i-1)) == 0)
					count++;
			}
	}
		    
	return(count);
}

long Sum1()
{
	int k;
	long j, count = 0;

	for (j = 0; j < 100*LOOPSIZE; j++)
	{
		count = 0;
		for (k = 0 ; k < SUMDATALEN; k++)
			count+= sumdata[k];
	}
	return(count);
}


long Sum2()
{
	long j, count = 0;

	for (j = 0; j < 100*LOOPSIZE; j++)
	{
		count = 0;
		count = SUMDATALEN * sumdata[0] + ((SUMDATALEN * SUMSTEP * (SUMDATALEN-1)) >> 1);

	}
		    
	return(count);
}

inline void Nibble2Ascii(int nibble, char &c)
{
	if (nibble < 10)
		c = (char)(0x30 + nibble);
	else
		c = (0x37 + nibble);
}

inline void HexStr1(char *s, int val)
{
	Nibble2Ascii(val >> 4, s[0]);
	Nibble2Ascii(val %16, s[1]);
	s[2] = 0x0;
}

char  HexString[] = {"0123456789ABCDEF"};
inline void HexStr2(char *s, int val)
{
    s[0] = HexString[val >> 4];
    s[1] = HexString[val & 0xf];
    s[2] = '\0';
}


long NumToHex1()
{
	long i, j;
	char s[3];

	for (i= 0; i < 100*LOOPSIZE; i++)
	{
		for (j = 0 ; j < 256; j++)
			HexStr1(s, j);
	}
	return(s[0]); // needed to avoid unfair compiler optimization when not using 's'
}

long NumToHex2()
{
	long i, j;
	char s[3];

	for (i= 0; i < 100*LOOPSIZE; i++)
	{
		for (j = 0 ; j < 256; j++)
			HexStr2(s, j);
	}
	return(s[0]);  // needed to avoid unfair compiler optimization when not using 's'
}


long NumToDec1()
{
	long i, j;
	char s[4];

	for (i= 0; i < 100*LOOPSIZE; i++)
	{
		for (j = 0 ; j < 256; j++)
			itoa( j, s, 10 );
	}
	return(s[0]);  // needed to avoid unfair compiler optimization when not using 's'
}


long NumToDec2()
{
	long i, j;
	char *s;

	for (i= 0; i < 100*LOOPSIZE; i++)
	{
		for (j = 0 ; j < 256; j++)
			s = decLookup[j];
	}
	return(s[0]);  // needed to avoid unfair compiler optimization when not using 's'
}


long Caps1()
{
	long i, j;
	unsigned char s;

	for (i= 0; i < 100*LOOPSIZE; i++)
	{
		for (j = 0 ; j < 256; j++)
			if (j < 0x61) s = tolower(j);
			else s = toupper(j);
	}
	return(1);  
}


long Caps2()
{
	long i, j;
	unsigned char s;

	for (i= 0; i < 100*LOOPSIZE; i++)
	{
		for (j = 0 ; j < 256; j++)
			s= upperLookup[j];
	}
	return(1);  
}


void main ()
{
	int i, j;

	for (i = 0; i < 256; i++)
		itoa(i ,&(decLookup[i][0]),10);

	for (i = 0; i < DATALEN; i++)
		data[i] = i;

	for (i = 0; i < 256; i++)
	{
			lookupTable[i] =((i & 128) >> 7)+((i & 64) >> 6)+((i & 32) >> 5)+((i & 16) >> 4)+
						    ((i &  8) >> 3)+((i &  4) >> 2)+((i &  2) >> 1)+((i &  1));
			upperLookup[i] = (char) i;
	}

	for (i = 0x41, j = 0x61; i < 0x5b; i++, j++)
	{
		upperLookup[i] = (char) j;
		upperLookup[j] = (char) i;
	}

	int q = 0;
	for (i = 0; i < SUMDATALEN; i++)
	{
		sumdata[i] = q;
		q += SUMSTEP;
	}

	
	// Time BitCounting
	cout << "Timing Bitcount" << endl;
	cout << "   Count 1   Count 2   Count 3" << endl;
	cout << setw(10) << time_fn(CountBits1);	
	cout << setw(10) << time_fn(CountBits2);	
	cout << setw(10) << time_fn(CountBits3);	
	cout << endl << endl;
		
	// Time test for devisors
	cout << "Timing Devisors" << endl;
	cout << "   Devisor 1   Devisor 2" << endl;
	cout << setw(10) << time_fn(Devisor1);	
	cout << setw(10) << time_fn(Devisor2);	
	cout << endl << endl;

	// Time test for sum 
	cout << "Timing Calculating sum" << endl;
	cout << "     Sum 1     Sum 2" << endl;
	cout << setw(10) << time_fn(Sum1);	
	cout << setw(10) << time_fn(Sum2);	
	cout << endl << endl;

	// Time test for hexstr
	cout << "Timing Num to Hex" << endl;
	cout << "  HexStr 1  HexStr 2" << endl;
	cout << setw(10) << time_fn(NumToHex1);	
	cout << setw(10) << time_fn(NumToHex2);	
	cout << endl << endl;

    // Time test for decstr
	cout << "Timing Num to Dec" << endl;
	cout << "  Standard    Lookup" << endl;
	cout << setw(10) << time_fn(NumToDec1);	
	cout << setw(10) << time_fn(NumToDec2);	
	cout << endl << endl;

	// Time test for to upper/ to lower
	cout << "Timing Caps conversion" << endl;
	cout << "  Standard    Lookup" << endl;
	cout << setw(10) << time_fn(Caps1);	
	cout << setw(10) << time_fn(Caps2);	
	cout << endl << endl;

	int c = getchar();
}

