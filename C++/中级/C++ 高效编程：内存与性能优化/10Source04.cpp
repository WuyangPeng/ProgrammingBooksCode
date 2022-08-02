#include "BookTools.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iomanip.h>

#define MAXSIZE   100000
#define MAXKEYLEN 20

unsigned int keylen = 0;

char *orgArray[MAXSIZE];
char *bigArray[MAXSIZE];

template <class T> inline void radixstr(int byte, unsigned long n, T *source, T *dest)
{
    unsigned long  count[256], i, s =0, c;

    memset(&count[0], 0x0, 256*sizeof(unsigned long));

    for (i = 0; i < n; i++) 
       count[(long)source[i][byte]]++;

    for (i = 0; i < 256; i++)
    {
         c = count[i];
         count[i] = s;
         s += c;
    }

    for (i = 0; i < n; i++) 
         dest[count[(long)source[i][byte]]++] = source[i]; 
}

template <class T> void RadixStrSort (T *data, unsigned long n, int elemsize)
{ 
    T *temp = (T*)malloc (n * sizeof (T));
	int i, j=0;

    if (temp != NULL)
    {
        for (i = elemsize-1; i > 0; i-=2)   
		{
		   radixstr(i, n, data, temp);
    	   radixstr(i-1, n, temp, data);
		}

		if (elemsize & 1)   
		{
            radixstr(0, n, data, temp);
			memcpy(data, temp, n * sizeof(T));
		}

        free (temp);
    }
	else
		printf("Error Alocating Memory!!\n");
}

int compare( const void *arg1, const void *arg2 )
{
	return (strcmp(*(char**)arg1, *(char**)arg2));
}

long cmp1()
{
    qsort((void *)bigArray, (size_t)MAXSIZE, sizeof(char *), compare);
	return(0);
}

long cmp2()
{
	RadixStrSort(bigArray, MAXSIZE, keylen);
	return(0);
}


void SetArray(unsigned long n)
{
	char *tmp;
	unsigned long i, j;

	for(i = 0 ; i < n; i++)
	{
		tmp = (char *)malloc(MAXKEYLEN+1);
		for (j = 0; j < MAXKEYLEN; j++)
			tmp[j] = (char)'A' + (rand() & 31);
		tmp[j] = 0x0;

		orgArray[i] = tmp; 
	}
}

void InitArray(unsigned long n)
{
	for(unsigned long i = 0; i < n ; i++)
	{
		bigArray[i] = orgArray[i];  
		bigArray[i][keylen] = 0x0;
	}
}


void TestResult(char *data[], unsigned long n)
{
	for(unsigned long i =1; i < n; i++)
		if (strcmp(data[i], data[i-1]) < 0)
			cout << "ERROR " << endl;
}



int main (int argc, char *argv[])
{
	SetArray(MAXSIZE);
	cout << "Comparing 'random filled arrays of strings' sort" << endl;
    cout << "Strlen   Qsort  Radix" << endl;
    cout << "======================" << endl;

	for(int i = MAXKEYLEN; i >= 0; i--)
	{
	   keylen = i;
       cout << setw(6) << keylen;	
	
        InitArray(MAXSIZE);
        cout << setw(7) << time_fn(cmp1);	
		TestResult(bigArray, MAXSIZE);

        InitArray(MAXSIZE);
        cout << setw(7) << time_fn(cmp2) << endl;	
		TestResult(bigArray, MAXSIZE);
	}

	int c = getchar();

	return (0);
}        
