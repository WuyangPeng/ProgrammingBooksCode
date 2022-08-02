/*
     srgp_mem.c
     Provides global dynamic memory allocation using Windows Local dynamic
     allocation functions.
*/

#include "srgplocal.h"

#define MAX_GLOBAL_BLOCKS 32

static WORD globalBlocks[MAX_GLOBAL_BLOCKS];
static WORD currentBlock;
static int numBlocks = 0;

boolean SRGP__memInit()
{
	if (numBlocks == 0) {
		numBlocks++;
		if ((globalBlocks[numBlocks-1] = GlobalAlloc(GPTR, GLOBAL_BLOCK_SIZE))
			== (HANDLE) 0)
			return FALSE;
		LocalInit(globalBlocks[numBlocks-1], 0, GLOBAL_BLOCK_SIZE-16);
        currentBlock = globalBlocks[numBlocks-1];
		return TRUE;
	} else return FALSE;
}

void FAR *SRGP_malloc(unsigned int size)
{
	void FAR *retval;
	register int dataSeg;
	void *newAddress;


	if ((size <= 0) || (size > (GLOBAL_BLOCK_SIZE-16)))
	return NULL;

	dataSeg = _DS;
	_DS = currentBlock;
	newAddress = (void *) LocalAlloc(LPTR, size);
	_DS = dataSeg;

	if (newAddress == NULL) {
		if (numBlocks < MAX_GLOBAL_BLOCKS) {
        	int i;
			for (i=numBlocks-2; (i>=0) && (newAddress == NULL); i--) {
				_DS = globalBlocks[i];
				newAddress = (void *) LocalAlloc(LPTR, size);
				_DS = dataSeg;
            }
			if (newAddress == NULL) {
				if ((globalBlocks[numBlocks] = GlobalAlloc(GPTR, GLOBAL_BLOCK_SIZE))
					== (HANDLE) 0) {
					retval = 0L;
				} else {
					numBlocks++;
					LocalInit(globalBlocks[numBlocks-1], 0, GLOBAL_BLOCK_SIZE-16);
					currentBlock = globalBlocks[numBlocks-1];
					dataSeg = _DS;
					_DS = currentBlock;
					newAddress = (void *) LocalAlloc(LPTR, size);
        	        _DS = dataSeg;
					retval = MAKELONG (newAddress, currentBlock);
				}
			} else {
				retval = MAKELONG (newAddress, globalBlocks[i+1]);
            }
		} else {
			retval = 0L;
		}
	} else {
		retval = MAKELONG (newAddress, currentBlock);
	}

	return(retval);
}

void FAR *SRGP_realloc(void far *ptr, unsigned int size)
{
	void FAR *retval;
	void *newAddress;
	int segment;
	register int dataSeg;

	if (ptr == NULL) {
		retval = SRGP_malloc(size);
	} else {
    	segment = HIWORD(ptr);
		dataSeg = _DS;
		_DS = segment;
		newAddress = (void *) LocalReAlloc(LOWORD(ptr), size, LMEM_NOCOMPACT);
		_DS = dataSeg;
        if (newAddress == NULL) {
			retval = SRGP_malloc(size);
			if (retval != NULL)
				memcpy(retval,ptr,size);
			SRGP_free(ptr);
		} else {
			retval = MAKELONG (newAddress, segment);
		}
	}
	return(retval);
}

void SRGP_free(void far *ptr)
{
	int dataSeg;

	if (ptr != NULL) {
		dataSeg = _DS;
		_DS = HIWORD(ptr);
		LocalFree(LOWORD(ptr));
		_DS = dataSeg;
	}
}

void SRGP__memFree()
{
	int i;

	for (i = 0; i < numBlocks; i++) {
		GlobalUnlock(globalBlocks[i]);
		GlobalFree(globalBlocks[i]);
		globalBlocks[i] = (HANDLE) 0;
	}
	numBlocks = 0;
}