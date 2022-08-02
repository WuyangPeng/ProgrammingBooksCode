#include "BookTools.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#define macro_strcmp(s1,s2) ((s1)[0] != (s2)[0] ? (s1)[0] - (s2)[0]:strcmp((s1), (s2)))
#define MAXLINE 200

#define search1 "Small Table#YELLOW #"
#define search2 "Small Table#MAGENTA#"
#define search3 "Small Table#SILVER #"
#define search4 "Small Table#BLACK  #"

struct item_c
{
	char	*line;
	item_c	*next;
};

struct item_cpp
{
	string   line;
	item_cpp *next;
};

item_c		*list_c = NULL;
item_cpp	*list_cpp = NULL;

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

void getlist_cpp()
{
	item_cpp *p = NULL, *q = NULL;
	
	ifstream ifs("\\dbase.txt");
	char s[MAXLINE];

	if (ifs)
	{
		while (ifs.getline(s, MAXLINE, '\n'))
		{
			p = new(item_cpp);
			p->line = (char *)s;
			p->next = NULL;
			if (list_cpp == NULL)
				list_cpp = p;
			else
				q->next = p;
			q = p;
		}
	}
	else
		cout << "Error reading input stream" << endl;

}


long cmp0()
{
	long j =0;
	item_c		*p_c;

	// Traverse C list
	p_c = list_c;
	while (p_c != NULL)
	{
		if ((memcmp(p_c->line, search1, 20) == 0) ||
			(memcmp(p_c->line, search2, 20) == 0) ||
		    (memcmp(p_c->line, search3, 20) == 0) ||
		    (memcmp(p_c->line, search4, 20) == 0)
		   )
			j++;
		p_c = p_c->next;
	}
	return(j);
}


long cmp1()
{
	long j =0;
	item_cpp	*p_cpp;

	// Traverse CPP list
	p_cpp = list_cpp;
	while (p_cpp != NULL)
	{
		if ((p_cpp->line == "Small Table#YELLOW #") ||
		    (p_cpp->line == "Small Table#MAGENTA#") ||
		    (p_cpp->line == "Small Table#SILVER #") ||
		    (p_cpp->line == "Small Table#BLACK  #")
		   )
		 	j++;
		p_cpp = p_cpp->next;
	}
	return(j);
}


long cmp2()
{
	long j =0;
	item_c		*p_c;

	// Traverse C list
	p_c = list_c;
	while (p_c != NULL)
	{
		if ((strcmp(p_c->line, search1) == 0) ||
			(strcmp(p_c->line, search2) == 0) ||
		    (strcmp(p_c->line, search3) == 0) ||
		    (strcmp(p_c->line, search4) == 0)
		   )
			j++;
		p_c = p_c->next;
	}
	return(j);
}


long cmp3()
{
	long j =0;
	item_c		*p_c;

	// Traverse C list
	p_c = list_c;
	while (p_c != NULL)
	{
		if ((macro_strcmp(p_c->line, search1) == 0) ||
		    (macro_strcmp(p_c->line, search2) == 0) ||
		    (macro_strcmp(p_c->line, search3) == 0) ||
		    (macro_strcmp(p_c->line, search4) == 0)
		   )
			j++;
		p_c = p_c->next;
	}

	return(j);
}

inline int int_strcmp(char *s1, char *s2, int len)
{
	if ((len & 0x03) != 0)
		return(macro_strcmp(s1, s2));

	for (int i =0; *(int*)&s1[i] == *(int*)&s2[i];)
	{
		i+=4;
		if (i >= len)
			return(true);              
	}
	
	return(false);
}

long cmp4()
{
	long j =0;
	item_c		*p_c;

	// Traverse C list
	p_c = list_c;
	while (p_c != NULL)
	{
		if ((int_strcmp(p_c->line, search1, 20)) ||
		    (int_strcmp(p_c->line, search2, 20)) ||
		    (int_strcmp(p_c->line, search3, 20)) ||
		    (int_strcmp(p_c->line, search4, 20)) 
		   )
			j++;
		p_c = p_c->next;
	}
	return(j);
}


long cmp5()
{
	long j =0;
	item_c		*p_c;

	// Traverse C list
	p_c = list_c;
	while (p_c != NULL)
	{
		if ((strncmp(p_c->line, search1, 20)) ||
		    (strncmp(p_c->line, search2, 20)) ||
		    (strncmp(p_c->line, search3, 20)) ||
		    (strncmp(p_c->line, search4, 20)) 
		   )
			j++;
		p_c = p_c->next;
	}
	return(j);
}


void main (int argc, char *argv[])
{
	cout << "Reading Input Data for C" << endl;
	getlist_c();
	cout << "Reading Input Data for CPP" << endl;
	getlist_cpp();
	cout << "Searching through data" << endl;

	for(;;)
	{
		cout << "Compare C++ string: " << time_fn(cmp1, 50) << " ms" << endl;	
		cout << "Memory compare    : " << time_fn(cmp0, 50) << " ms" << endl;	
		cout << "Compare strcmp    : " << time_fn(cmp2, 50) << " ms" << endl;	
		cout << "String 'n' compare: " << time_fn(cmp5, 50) << " ms" << endl;	
		cout << "Compare macro     : " << time_fn(cmp3, 50) << " ms" << endl;	
		cout << "Compare int's     : " << time_fn(cmp4, 50) << " ms" << endl;	
	}

}        



