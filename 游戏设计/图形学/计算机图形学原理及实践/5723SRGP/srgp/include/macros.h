/** MEMORY ALLOCATION MACROS
Handles differences between Macintosh, UNIX, and MS Windows.
**/

#include <mem.h>
#include <alloc.h>

#ifdef THINK_C
#define MALLOCARGTYPE 	size_t
#else
#define MALLOCARGTYPE 	unsigned
#endif

/*
	NOTE for MS WINDOWS 3.0
	This application is a PIG.  It locks its global data so that it will
	not be moved between messages.
*/

#ifdef _Windows
#define ALLOC_RECORDS(PTR,TYPE,NUM) \
	{ \
	GLOBALHANDLE hGlobalMem; \
	if ((hGlobalMem = GlobalAlloc (GPTR, (NUM+1)*sizeof(TYPE))) == NULL) \
		REPORT_ERROR (ERR_MALLOC);\
		else PTR = (TYPE *) ((65536L % sizeof(TYPE)) +\
							 GlobalLock(hGlobalMem)); \
	}
#else
#define ALLOC_RECORDS(PTR,TYPE,NUM) \
	if ((PTR = (TYPE *) malloc((MALLOCARGTYPE)((NUM)*sizeof(TYPE)))) == NULL) \
		REPORT_ERROR (ERR_MALLOC); else

#endif

#if defined(THINK_C) || defined(__MSDOS__)
#define bzero(PTR,NUMBYTES) 	memset(PTR, 0, (size_t)NUMBYTES)
#define bcopy(SRC,DEST,NUMBYTES)	memcpy(DEST, SRC, (size_t)NUMBYTES)
#define bcmp(B1,B2,NUMBYTES)	memcmp(B1,B2,(size_t)NUMBYTES)
#define irint	/* nothing:  very risky! */
#endif