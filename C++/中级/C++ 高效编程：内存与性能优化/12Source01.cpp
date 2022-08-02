#include "BookTools.h"
#include <stdio.h>
#include <iomanip.h>
#include <string.h>

#define N 26*10
char input[N][255];


void FillInputArray(void)
{
	int loops = N / 26;

	int arrayIndex   = 0;
	char startChar   = 'a';
	char currentChar = 0;
	int startLength  = 20;
	int currentLength= 0;

	for(int i = 0; i < loops; i++)
	{
		currentLength = startLength;
		currentChar   = startChar;

		for (int j = 0; j < 26; j++)
		{

			for (int k = 0; k < currentLength; k++)
				input[arrayIndex][k] = currentChar;


			input[arrayIndex][currentLength] = '\0';
			currentChar++;
			currentLength+=2;
			arrayIndex++;
		}
	}

}
 

long CoutFlush(void)
{
	for(int i = 0; i < N ; i++)
	{
		cout << "Test " << input[i] << endl << flush;
	}

	return 0;
}


long CoutReturn(void)
{
	for(int i = 0; i < N ; i++)
	{
		cout << "Test " << input[i] << '\n';
	}

	return 0;
}


long Printf(void)
{
	for(int i = 0; i < N ; i++)
	{
		printf("Test %s \n",input[i]);
	}

	return 0;
}


char tmp[255];
long PutsCopy(void)
{
	strcpy(tmp, "Test ");
	for(int i = 0; i < N ; i++)
	{
		strcpy(&tmp[5], (char*)input[i]);
		puts(tmp);
	}

	return 0;
}


long PutsTwice(void)
{
	for(int i = 0; i < N ; i++)
	{
		puts("Test ");
		puts((char*)input[i]);
	}

	return 0;
}


char Test[] = "Test ";
long PutcharMACRO(void)
{
	char c;
	int j = 0;


	for(int i = 0; i < N ; i++)
	{
		while ((c = Test[j++]) != '\0')
			putchar(c);

		j = 0;
		while ((c = input[i][j++]) != '\0')
			putchar(c);
		putchar(13); 
		putchar(10);
		j = 0;
	}

	return 0;
}


long PutcharFunction(void)
{
	char c;
	int j = 0;

	for(int i = 0; i < N ; i++)
	{
		while ((c = Test[j++]) != '\0')
		(putchar)(c);

		j = 0;
		while ((c = input[i][j++]) != '\0')
			(putchar)(c);
		(putchar)((char)13);  
		(putchar)((char)10);
		j = 0;
	}

	return 0;
}

 
void main (void)
{

	FillInputArray();

	for(int i = 0;i < 5;i++)
	{
	long a = time_fn(CoutFlush);
	cout << endl;	
	long b = time_fn(CoutReturn);
	cout << endl;
	long c = time_fn(Printf);
	cout << endl; 	
	long d = time_fn(PutsTwice);
	cout << endl;	
	long e = time_fn(PutsCopy);
	cout << endl;
	long f = time_fn(PutcharFunction);
	cout << endl;	
	long g = time_fn(PutcharMACRO);
	cout << endl;	

	cout << "cout+endl   :" << a << endl;	
	cout << "cout+\\n     :" << b << endl;
	cout << "printf      :" << c << endl; 	
	cout << "2x puts     :" << d << endl;	
	cout << "copy+puts   :" << e << endl;
	cout << "putc funct  :" << f << endl;	
	cout << "putc MACRO  :" << g << endl;	
	}

	int c = getchar();
}        

