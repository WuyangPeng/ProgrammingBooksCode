#include "BookTools.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iomanip.h>


#define MAXSIZE   100000
#define MAXKEYLEN 14

unsigned long sortNum;
unsigned long sortKey;

class record
{  
   char *name;
public:
   record(){}  
   void setname(const char *p)
   {  
	  name = new char[strlen(p)+1];
      strcpy(name, p);
   }
   friend int operator==(const record &r, const record &s)
   {  
	   return(strcmp(r.name, s.name));
   }
   friend int operator<(const record &r, const record &s)
   {  
	   return(strcmp(r.name, s.name) < 0);
   }
   friend int operator<=(const record &r, const record &s)
   {  
	   return(strcmp(r.name, s.name) <= 0);
   }
   friend int operator>(const record &r, const record &s)
   {  
	   return(s < r);
   }
   friend int operator>=(const record &r, const record &s)
   {  
	   return(s <= r);
   }

   char &operator[](int index)        
   {  
	   return name[index];
   }
   char operator[] (int index) const  
   {  
	   return name[index];
   }

   friend ostream &operator<<(ostream &s, const record &r)
   {  
	   return s << r.name << endl;
   }
};
 
record orgArray[MAXSIZE];
record bigArray[MAXSIZE];

template <class T> inline void FQuickSort(T *data, long n)
{
    T pivot, tempElem;
    long left, right, tempIndex;

   while(n > 1)
   {
	right = n-1;
	left = 1;

	tempIndex = right / 2; 
    pivot = data[tempIndex];
    data[tempIndex] = data[0];

    while (1) 
    {
        while (pivot > data[left] && left < right) 
			left++;
        while (pivot <= data[right] && right >= left) 
			right--;
        if (left >= right) 
			break;
        tempElem = data[left];
        data[left] = data[right];
        data[right] = tempElem;
        right--; left++;
    }
    data[0] = data[right];
    data[right] = pivot;

    if (n < 3) 
		return;

	tempIndex = n - right - 1;

	if (right <= tempIndex)
	{
        FQuickSort(data + right + 1, n - right - 1);
        n = right;
	}
	else
	{
       FQuickSort(data, right);
	   data += right + 1;
	   n = tempIndex;
	}
   }
}


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

int compare(const void *arg1, const void *arg2)
{
   return (*(record*)arg1 == *(record*)arg2);
}

long cmp1()
{
    qsort((void *)bigArray, (size_t)sortNum, sizeof(record *), compare);
	return(0);
}

long cmp2()
{
	FQuickSort(bigArray, sortNum);
	return(0);
}


long cmp3()
{
	RadixStrSort(bigArray, sortNum, sortKey);
	return(0);
}


void SetArray(unsigned long n, unsigned long keylen)
{
	char tmp[1024];
	unsigned long i, j;

	for(i = 0 ; i < n; i++)
	{
		for (j = 0; j < keylen; j++)
			tmp[j] = (char)'A' + (rand() & 31);
		tmp[j] = 0x0;

		orgArray[i].setname(tmp);
	}
}

void InitArray(unsigned long n)
{
	sortNum = n;
	for(unsigned long i = 0; i < n ; i++)
	{
		bigArray[i] = orgArray[i];  
	}
}


void TestResult(record data[], unsigned long n)
{
	for(unsigned long i =1; i < n; i++)
		if (data[i] < data[i-1])
			cout << "ERROR " << endl;
}



int main (int argc, char *argv[])
{
	cout << "Comparing 'random filled arrays of records' sort" << endl;
    cout << "Keysize Records  Qsort  Quick  Radix" << endl;
    cout << "====================================" << endl;

	for(unsigned long i = 2; i <= MAXKEYLEN; i++)
	{
		cout << endl;
		SetArray(MAXSIZE, i);
		for(unsigned long j = 10000; j <= MAXSIZE; j+=10000)
		{
		   cout << setw(7) << i;	
		   cout << setw(7) << j;	
		
		   sortNum = j;
		   sortKey = i;

		//qsort
			InitArray(j);
			cout << setw(7) << time_fn(cmp1);
			TestResult(bigArray, j);
		//FQsort
			InitArray(j);
			cout << setw(7) << time_fn(cmp2);
			TestResult(bigArray, j);
		//Radix
			InitArray(j);
			cout << setw(7) << time_fn(cmp3) << endl;	
			TestResult(bigArray, j);
		}
	}

	int c = getchar();
	return (0);
}        
