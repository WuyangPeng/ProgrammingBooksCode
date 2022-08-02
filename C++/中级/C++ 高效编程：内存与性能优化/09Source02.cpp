#include <stdio.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include "BookTools.h"

#define NAME_SIZE			50
#define MAX_ITEMS			200
//=====================================================================
class Stack					
{
	struct elem
	{
		struct			elem *next;
		char			name[NAME_SIZE];
		unsigned long	id;
	};

public:
	Stack() { end = NULL; elemcount = 0;}
	void push(const char *s, const unsigned long nr);   // store name - id  
	void pop(char *s, unsigned long &nr);

private:
	elem	*end;
	long	elemcount;
};


inline void Stack::push(const char *s, const unsigned long nr)
{ // add new item to the end of the list
	
	if (elemcount +1 > MAX_ITEMS)
	{
		cout << "Error, Stack Overflow!!" << endl;
	}
	else
	{
		elem *newelem = new elem;

		strncpy(newelem->name, s, NAME_SIZE);
		newelem->id = nr;
		newelem->next = end;
		end = newelem;
		elemcount++;
	}
}

inline void Stack::pop(char *s, unsigned long &nr)
{ // return last item of the list and free it
	if (end!=NULL)
	{
		elem *last = end;
		
		strncpy(s, last->name, NAME_SIZE);
		nr = last->id;
		end = last->next;
		free(last);
		elemcount--;
	}
	else	
	{
		cout << "Error, Stack Underflow!!" << endl;
	}
}


//=====================================================================
// New const!!
#define INITSIZE 20000


class BigChunkStack
{
 struct elem
 {
  int	id;
  int 	previousElemSize;
  int	nameSize;
  char  name;
 };


public:
	BigChunkStack() 
	{ totalSize = 0; MAXSIZE = 0;
	  emptyElemSize = sizeof(elem); lastElemSize = 0;}

	// store {name,id}
	void push(const char *s, const int nr);

	// retrieve {name,id}
	void pop(char *s, unsigned long &nr);

	// increase pool size.
	int grow();

	// decrease pool size.
	void shrink();

private:
	char 	*pool;
	int		MAXSIZE;
	int		totalSize;
	int		emptyElemSize;
	int		lastElemSize;
};


inline void BigChunkStack::push(const char *s, const int nr)
{ // add new item to the top of the stack

	int newStringSize	= strlen(s) + 1;
	int totalElemSize	= newStringSize + emptyElemSize;

	while (totalSize + totalElemSize > MAXSIZE)
	{
		if (!grow())
		{
			cout << "Error, Stack Overflow!!" << endl;
			return;
		}
	}

	elem *newElem		= (elem*) (pool + totalSize);
		
	newElem->id			= nr;
	newElem->nameSize	= newStringSize;
	newElem->previousElemSize = lastElemSize;
	strcpy(&newElem->name, s);
		
	lastElemSize = totalElemSize;
	totalSize  += totalElemSize;
}


inline int BigChunkStack::grow()
// Create or Enlarge the pool size.
{
	if (MAXSIZE == 0)
	{
		// create.
		pool = (char*) malloc(INITSIZE);
		if (pool == NULL) return 0;

		MAXSIZE = INITSIZE;
		return 1;
	}
	else
	{
		// enlarge.
		MAXSIZE *= 2;

		char* tempPool = (char*) realloc(pool, MAXSIZE);
		if (tempPool == NULL) return 0;
		
		pool = tempPool;
		return 1;
	}

}


inline void BigChunkStack::shrink()
// Shrink the pool size.
{
	if ((MAXSIZE/2) >= INITSIZE)
	{
		// shrink.
		char* tempPool = (char*) realloc(pool, MAXSIZE/2);
		if (tempPool == NULL) return ;
		
		MAXSIZE /= 2;
		pool = tempPool;
		return;
	}

}


inline void BigChunkStack::pop(char *s, unsigned long &nr)
{ // return item from the top of the stack and free it
	
	if (totalSize * 4 <= MAXSIZE)
		shrink();

	if (totalSize != 0)
	{
		totalSize		-= lastElemSize;
		elem *popped	= (elem*) (pool + totalSize);
		lastElemSize	= popped->previousElemSize;

		strcpy(s, &popped->name);
		nr		= popped->id;

	}
	else
	{
		cout << "Error, Stack Underflow!!" << endl;
	}
}


//=====================================================================
#define init_size  10    // initial 10 elements

class ResizeStack
{
	struct elem
	{
		char			name[NAME_SIZE];
		unsigned long	id;
	};

public:
	ResizeStack() {end = 0; max_items = 0;} 
	void push(const char *s, const unsigned long nr);   // store name - id  
	void pop(char *s, unsigned long &nr);

private:
	void grow() 
	{ 
		 if (max_items==0)
		 {
			 max_items = init_size;
			 pool = (elem*)malloc(max_items * sizeof(elem));
		 }
		 else
		 {
			 max_items <<= 1;
			 pool = (elem*)realloc(pool, max_items * sizeof(elem));
		 }
	}
	void schrink()
	{
		 if (max_items > 2)
		 {
			 max_items >>= 1;
     		 pool = (elem*)realloc(pool,  max_items * sizeof(elem));
		 }
	}

	long end, max_items;
	elem *pool;
};


inline void ResizeStack::push(const char *s, const unsigned long nr)
{ // add new item to the end of the list

	if (end > max_items-1)
		grow();

	elem *ptr = (elem *)(pool+end);
	strncpy(ptr->name, s, NAME_SIZE);
	ptr->id = nr;
	end++;
}


inline void ResizeStack::pop(char *s, unsigned long &nr)
{ // return last item of the list and free it

	if ((end << 2) <= max_items)
		schrink();				// check whether we can schrink or not
	
	if (end >=0)
	{
		end--;
		elem *ptr = (elem *)(pool+end);
		
		strncpy(s, ptr->name, NAME_SIZE);
		nr = ptr->id;
	}
	else	
	{
		cout << "Error, Stack Underflow!!" << endl;
	}
}


long TimePtr()
{
	Stack			q;
	char			name[NAME_SIZE];
	unsigned long	id;
	int i, j;


	for (i =0; i < 1000; i++)
	{
		for (j = 0; j <MAX_ITEMS; j++)
			q.push("Myname", j);
		for (j = 0; j <MAX_ITEMS; j++)
		{
			q.pop(name, id);
//			printf("%s: %ld\n", name, id);
		}
	}
	return(0);
}


long TimeArray()
{
	BigChunkStack	q;
	char			name[NAME_SIZE];
	unsigned long	id;
	int i, j;

    for (i =0; i < 1000; i++)
	{
		for (j = 0; j <MAX_ITEMS; j++)
			q.push("Myname", j);
		for (j = 0; j <MAX_ITEMS; j++)
		{
			q.pop(name, id);
//			printf("%s: %ld\n", name, id);
		}
	}
	return(0);
}

long TimeResizeArray()
{
	ResizeStack	q;
	char			name[NAME_SIZE];
	unsigned long	id;
	int i, j;

	for (i =0; i < 1000; i++)
	{
		for (j = 0; j < MAX_ITEMS; j++)
			q.push("Myname", j);
		for (j = 0; j < MAX_ITEMS; j++)
		{
			q.pop(name, id);
//			printf("%s: %ld\n", name, id);
		}
	}
	return(0);
}

void main()
{
	for(;;)
	{
		cout << "Ptr List  : " << time_fn(TimePtr, 5) << endl;
		cout << "Array     : " << time_fn(TimeArray, 5) << endl;
		cout << "Resizable : " << time_fn(TimeResizeArray, 5) << endl;
	}
}
