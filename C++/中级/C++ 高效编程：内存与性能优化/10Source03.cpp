#include "BookTools.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iomanip.h>

#define MAXSIZE 600000
typedef unsigned long elemtype;
elemtype orgArray[MAXSIZE];
elemtype bigArray[MAXSIZE];
elemtype sortNum = MAXSIZE;


template <class T> void InsertionSort(T data[], unsigned long n) 
{
    unsigned long i, j;
	T item;

    for(i=1;i<n;i++) 
    {
        item = data[i];

        for(j=i; (j > 0) && (data[j-1] > item); j--) 
          data[j] = data[j-1]; 

        data[j] = item;
    }
}   


template <class T> void BubbleSort(T data[], unsigned long n)
{
    unsigned long i, j;
    bool changes = true;
    for(i=0;(i<n) && (changes == true);i++)
    {
        changes = false;
	    for(j=1;j<(n-i);j++)
        { 
           if( data[j-1]>data[j] ) 
		   {
				T dummy = data[j-1];  
                data[j-1] = data[j];
				data[j] = dummy;
                changes = true;
			}
        }
    }
}    

template <class T> void ShellSort(T data[], long lb, long ub) 
{
    long n, i, j, h; 
	T t;
    
    n = ub - lb + 1;
    h = 1;
    if (n < 14)
        h = 1;
    else 
	{
        while (h < n) 
			h = 3*h + 1;
        h /= 3;
        h /= 3;
    }

    while (h > 0) 
	{
        for (i = lb + h; i <= ub; i++) 
		{
            t = data[i];
            for (j = i-h; j >= lb && (data[j] > t); j -= h)
                data[j+h] = data[j];
            data[j+h] = t;
        }

        h /= 3;
    }
}



template <class T> void HeapSort(T data[], int n)
{
	int i, j, j2, k;
	T tmp;

	for(k = (n>>1) - 1; k >= 0; k--)
    {
		tmp = data[k];
		for(j = k; (j<<1) <= n-2; j = i)  
		{								 
			j2 = j <<1;
			 if (j2+2 > n-1) 
				i = j2+1;
			 else 
			 {
				 if (data[j2+1] < data[j2+2])
					 i = j2+2;
				 else 
					 i = j2+1;
			 }
			 if (tmp < data[i])
				 data[j] = data[i]; 
			 else 
				 break;
		}
		data[j] = tmp;
    }

	for(k=n-1; k>0; k--)
    {
		tmp = data[k];
		data[k] = data[0];
		for(j = 0; (j<<1) <= k-2; j = i) 
        {								
			j2 = j<<1;
			if ( j2+2 > k-1 )			
	            i = j2+1;
		    else 
			{
		       if ( data[j2+1] < data[j2+2] )
                  i = j2+2;
               else 
				  i = j2+1;
			}
			if (tmp < data[i])
				 data[j] = data[i]; 	
			else 
				break;
        }
		data[j] = tmp;
	}
}


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

    if (n < 3) return;

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



template <class T> inline void radix(int byte, unsigned long n, T *source, T *dest)
{
	unsigned long count[256], i, c, s=0;
    unsigned char *q;
    int size = sizeof(T);

    memset(&count[0], 0x0, 256*sizeof(unsigned long));

    q = (unsigned char *)source;
    for (i = 0; i < n; i++) 
    {
       count[q[byte]]++;
	   q+=size;
    }

    for (i = 0; i < 256; i++)
    {
         c = count[i];
         count[i] = s;
         s += c;
    }

    q = (unsigned char *)source;
    for (i = 0; i < n; i++) 
    {
         dest[count[q[byte]]++] = *(T*)q;
         q+=size;
    }
}

#define L_ENDIAN

template <class T> void RadixSort (T *data, unsigned long n)
{ 

    int i, elemsize = sizeof(T);
	T *temp = (T*)malloc (n * elemsize);

	if (temp != NULL)
    {
#ifdef L_ENDIAN
        for (i=0; i < elemsize-1; i+=2)   
		{
		   radix(i, n, data, temp);
    	   radix(i+1, n, temp, data);
		}
		if (elemsize & 1)    
		{
            radix(elemsize-1, n, data, temp);  
			memcpy(data, temp, n * elemsize);
		}
#else
        for (i = elemsize-1; i > 0; i-=2)   
		{
		   radix(i, n, data, temp);
    	   radix(i-1, n, temp, data);
		}
		if (elemsize & 1)   
		{
            radix(0, n, data, temp);
			memcpy(data, temp, n * elemsize);
		}
#endif

       free (temp);
    }
}


long cmp1()
{
	InsertionSort(bigArray, sortNum);
	return(0);
}

long cmp2()
{
	BubbleSort(bigArray, sortNum);
	return(0);
}


long cmp3()
{
	ShellSort(bigArray, 0, sortNum);
	return(0);
}

long cmp4()
{
	HeapSort(bigArray, sortNum);
	return(0);
}

int compare( const void *arg1, const void *arg2 )
{
	return ( *(elemtype*) arg1 -  *(elemtype*)arg2);
}

long cmp5()
{
    qsort( (void *)bigArray, (size_t)sortNum, sizeof(elemtype), compare);
	return(0);
}

long cmp6()
{
	FQuickSort(bigArray, sortNum);
	return(0);
}


long cmp7()
{
	RadixSort(bigArray, sortNum);
	return(0);
}


void TestResult(elemtype data[], unsigned long n)
{
	for(elemtype i =1; i < n; i++)
		if (data[i] < data[i-1])
			cout << "ERROR " << endl;

}

void SetArray(elemtype items)
{
    srand( (unsigned)time( NULL ) );
	for(unsigned long i = 0 ; i < items; i++)
		orgArray[i] = (elemtype) (rand());    
}

void InitArray(elemtype items)
{
	sortNum = items;
	for(unsigned long i = 0; i < items ; i++)
		bigArray[i] = orgArray[i];  
}


void main (int argc, char *argv[])
{
	SetArray(MAXSIZE);
	cout << "Comparing 'random filled arrays of numbers' sort" << endl;
    cout << "  Items   Insrt  Bubbl  Shell  Heaps  Qsort  FQsrt  Radix" << endl;
    cout << "=========================================================" << endl;


	for(elemtype i = 5000; i <= MAXSIZE; i+= 5000)
	{
	    
		cout << setw(8) << i;
	// INSERTION
		InitArray(i);
        cout << setw(7) << time_fn(cmp1);	
		TestResult(bigArray, sortNum);
	//BUBBLE
		InitArray(i);
        cout << setw(7) << time_fn(cmp2);	
		TestResult(bigArray, sortNum);
	// Shell
        InitArray(i);
        cout << setw(7) << time_fn(cmp3);	
		TestResult(bigArray, sortNum);
	//Heap
        InitArray(i);
        cout << setw(7) << time_fn(cmp4);	
		TestResult(bigArray, sortNum);
	//qsort
        InitArray(i);
        cout << setw(7) << time_fn(cmp5);	
		TestResult(bigArray, sortNum);
	//Quick
        InitArray(i);
        cout << setw(7) << time_fn(cmp6);	
		TestResult(bigArray, sortNum);
	//Radix
        InitArray(i);
        cout << setw(7) << time_fn(cmp7) << endl;	
		TestResult(bigArray, sortNum);
	}
}        

