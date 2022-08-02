

#include <ctime>
#include <stdio.h>

#define OFFSET 10		// secret value used in authentication check.

// Structure to pass as data to the functions.
struct Authentication
{
	unsigned char regCode[21];
	unsigned char user[7];
	unsigned char password[7];
};

// Globally defined instance of data, used in the global version of the 
//  CheckAuthentication function.
Authentication glob = 
	   {{0,3,1,0,0,4,0,4,2,1,0,5,0,2,1,0,5,0,2,}, "Bond01","shaken"}; 


// Global function.
int CheckAuthentication_Global()
{
	int result = 1;

	glob.user[result] = result;
	for (int i = 0; i < 7; i++)
	{
		if (glob.user[i] + glob.password[i] != 
(glob.regCode[i*3]-OFFSET)) 
		{
			result = 0;
			break;
		}
	}
	
	return result;
}

// Pass-By-Value function.
int CheckAuthentication_ByValue(Authentication value)
{
	int result = 1;

	value.user[result] = result;
	
	for (int i = 0; i < 7; i++)
	{
		if (value.user[i] + value.password[i] != 
(value.regCode[i*3]-OFFSET)) 
		{
			result = 0;
			break;
		}
	}
	
	return result;
}

// Pass-By-Reference function.
int CheckAuthentication_ByReference(Authentication &ref)
{
	int result = 1;

	ref.user[result] = result;
	for (int i = 0; i < 7; i++)
	{
		if (ref.user[i] + ref.password[i] != 
(ref.regCode[i*3]-OFFSET)) 
		{
			result = 0;
			break;
		}
	}
	
	return result;
}

// Pass-By-Reference -using a pointer- function.
int CheckAuthentication_ByPointer(Authentication *ref)
{
	int result = 1;

	ref->user[result] = result;
	for (int i = 0; i < 7; i++)
	{
		if (ref->user[i] + ref->password[i] != 
(ref->regCode[i*3]-OFFSET)) 
		{
			result = 0;
			break;
		}
	}
	
	return result;
}


void main(void)
{
// Locally defined instance of data, used in the non-global
//  versions of the CheckAuthentication functions.
	Authentication auth = 
	   {{0,3,1,0,0,4,0,4,2,1,0,5,0,2,1,0,5,0,2,}, "Bond01","shaken"}; 


	clock_t begin;
	clock_t end;
	int result1=0, result2=0, result3=0, result4=0;
	int i;

	// reference test.
	begin = clock();
	for (i = 0; i < 3000000; i++)
	{
		CheckAuthentication_ByReference(auth);
	}
	end = clock();
	result1 += (end - begin);
		
	// value test.
	begin = clock();
	for (i = 0; i < 3000000; i++)
	{
		CheckAuthentication_ByValue(auth);
	}
	end = clock();
	result2 += (end - begin);

	// pointer test.
	begin = clock();
	for (i = 0; i < 3000000; i++)
	{
		CheckAuthentication_ByPointer(&auth);
	}
	end = clock();
	result3 += (end - begin);

	// global test.
	begin = clock();
	for (i = 0; i < 3000000; i++)
	{
		CheckAuthentication_Global();
	}
	end = clock();
	result4 += (end - begin);

	printf("ref = %d, value = %d, pointer = %d, global %d ", 
			result1, result2, result3, result4);
	int c = getchar();
}
