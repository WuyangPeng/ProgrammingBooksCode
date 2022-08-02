#include "Macro.h"

int numEntries = MAX_INDEX;
int tableIndex[MAX_INDEX];

void Test()
{
    for (int entryCount = 0; entryCount < numEntries; entryCount++)
        LookupEntry2(entryCount, tableIndex[entryCount]);
}