#ifndef GENERATE_PERMUTATIONS
#define GENERATE_PERMUTATIONS

#include <vector>

#include "d_util.h"			// for writeVector()

using namespace std;

// output the list of all permutations of the
// integer values in the range [index,permList.size())
void permute(vector<int> permList, int index);

void permute(vector<int> permList, int index)
{
	int temp, i, vSize = permList.size();

	if (index == vSize-1)
		// display the permutation
		writeVector(permList);	
	else
	{
		// find all permutations over the range
		// [index, vSize)
		permute(permList, index+1);

		// exchange permList[index] with permList[i]
		// for i=index+1 to the end of the vector and
		// find all permutations
		for (i=index+1; i < vSize; i++)
		{
			temp = permList[i];							
			permList[i] = permList[index];
			permList[index] = temp;

			permute(permList, index+1);		
		}
	}
}

#endif	// GENERATE_PERMUTATIONS
