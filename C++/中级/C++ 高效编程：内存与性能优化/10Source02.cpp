#include "BookTools.h"
#include <iostream>
#include <fstream>

using namespace std;

#define MAXLINE 200

unsigned char skips[256];  
unsigned char search_len;  
char * searchst;         


unsigned char searchstr[255];
unsigned char alfa[255];
unsigned char skipsInsens[255];  
unsigned char patlenInsens;

void initInsens(const char *str)
{
	int len1 = 0;

	unsigned char c = str[len1];
	while ( c != '\0')
	{
		alfa[len1] = 0;
		if (c >= 'A' && c <= 'Z')
		{
			searchstr[len1] = c + 0x20;
			alfa[len1] = 1;
		}
		else
		{
			searchstr[len1] = c;
			if (c >= 'a' && c <= 'z')
				alfa[len1] = 1;
		}
		c = str[++len1];
	}

	int len2 = len1 + 1;

	for (int i = 0; i < 255; i++)
		skipsInsens[i] = len2;  

	for ( i = 0; i < len1; i++)
	{
		skipsInsens[searchstr[i]] = len1 - i;                    
		if (alfa[i]) skipsInsens[searchstr[i]-0x20] = len1 - i;  
	}

	patlenInsens = len1;
}


char *searchInsens(const char *textf, int len)
{
	if (patlenInsens > len || patlenInsens == 0)
		return NULL;

	char * end = (char*) textf + len;
	int len2 = patlenInsens -1;
	int j;

	for(;;)
	{
		j = len2;
		while (
			((textf[j] == searchstr[j]) || ((alfa[j]) && (textf[j] == (char) (searchstr[j]-0x20))))
			&& --j >= 0) ;

		if (j != -1)
		{
			char* skipindex = (char*) textf + patlenInsens;
			if (skipindex >= end)
				return NULL;  

			textf += skipsInsens[*skipindex]; 

		}
		else
		{
			return (char*)textf;
		}

	}
	return NULL; 
}

void init(const char *str)
{
	search_len = strlen(str);
	int len2 = search_len + 1;

	for (int i = 0; i < 256;i++)
		skips[i] = len2;  

	for ( i = 0; i < search_len; i++)
		skips[str[i]] = search_len - i; 

	searchst = (char*) str;
}


char *search(const char *textf, int len)
{
	if (search_len > len || search_len == 0)
		return NULL;

	char * end = (char*) textf + len;
	int len2 = search_len -1;
	int j;

	for(;;)
	{
		j = len2;
		while (textf[j] == searchst[j] && --j >= 0) ;

		if (j != -1)
		{
			char* skipindex = (char*) textf + search_len;
			if (skipindex >= end)
				return NULL;  

			textf += skips[*skipindex]; 

		}
		else
		{
			return (char*)textf;
		}

	}
	return NULL; 
}

struct item_c
{
	char	*line;
	item_c	*next;
};


item_c		*list_c = NULL;

void getlist_c()
{
	item_c *p = NULL, *q = NULL;
	
	ifstream ifs("\\dbase.txt");
	char s[MAXLINE];

	if (ifs)
	{
		while (ifs.getline(s, MAXLINE, '\n'))
		{
			p = new(item_c);
			p->line = (char *)malloc(strlen(s)+1);
			strcpy(p->line, s);
			p->next = NULL;
			if (list_c == NULL)
				list_c = p;
			else
				q->next = p;
			q = p;
		}
	}
	else
		cout << "Error reading input stream" << endl;

}

char tmp[] = "InternaltotheOrganisation";

long cmp1()
{
	long j =0;
	item_c		*p_c;

	p_c = list_c;
	while (p_c != NULL)
	{
		if (strstr(p_c->line, tmp) != NULL)
			j++;
		p_c = p_c->next;
	}
	return(j);
}


long cmp2()
{
	long j =0;
	item_c		*p_c;

	init(tmp); 

	p_c = list_c;
	int linesize = strlen(p_c->line);

	while (p_c != NULL)
	{
		if (search(p_c->line, linesize) >= 0)
			j++;
		p_c = p_c->next;
	}
	return(j);
}

long cmp3()
{
	long j =0;
	item_c		*p_c;

	initInsens(tmp); 

	p_c = list_c;
	int linesize = strlen(p_c->line);

	while (p_c != NULL)
	{
		if (searchInsens(p_c->line, linesize) >= 0)
			j++;
		p_c = p_c->next;
	}
	return(j);
}

void main (int argc, char *argv[])
{

	cout << "Reading Input Data." << endl << endl;
	getlist_c();
	cout << "Searching through data" << endl;

	cout << "strstr    FastSearch    Case insensitive" << endl;
	for(;;)
	{
		cout << time_fn(cmp1, 10) << "        " << time_fn(cmp2, 10) << "            " << time_fn(cmp3, 10)<<" ms" << endl;	
	}

}        



