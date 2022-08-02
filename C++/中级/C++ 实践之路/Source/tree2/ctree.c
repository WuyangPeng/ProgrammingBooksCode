/* (c) Bartosz Milewski 2000 */
#include "ctree.h"
#include <stdio.h>
#include <malloc.h>

double Calc (struct Node * pNode)
{
	double x;
	x = 0.0;
	switch (pNode->type)
	{
	case NUM_NODE:
		x = pNode->val;
		break;
	case ADD_NODE:
		x = Calc (pNode->pLeft) + Calc (pNode->pRight);
		break;
	case MULT_NODE:
		x = Calc (pNode->pLeft) * Calc (pNode->pRight);
		break;
	}
	return x;
}

int main ()
{
	struct Node *pNode1, *pNode2, *pNode3, *pNode4, *pNode5;
	double x;
	/* ( 20.0 + (-10.0) ) * 0.1 */
	pNode1 = malloc (sizeof (struct Node));
	pNode1->type = NUM_NODE;
	pNode1->val = 20.0;
	
	pNode2 = malloc (sizeof (struct Node));
	pNode2->type = NUM_NODE;
	pNode2->val = -10.0;
	
	pNode3 = malloc (sizeof (struct Node));
	pNode3->type = ADD_NODE;
	pNode3->pLeft = pNode1;
	pNode3->pRight = pNode2;
	
	pNode4 = malloc (sizeof (struct Node));
	pNode4->type = NUM_NODE;
	pNode4->val = 0.1;
	
	pNode5 = malloc (sizeof (struct Node));
	pNode5->type = MULT_NODE;
	pNode5->pLeft = pNode3;
	pNode5->pRight = pNode4;
	
	printf ("Calculating the tree\n");
	x = Calc (pNode5);
	printf ("Result: %lf\n", x);
	
	free (pNode1);
	free (pNode2);
	free (pNode3);
	free (pNode4);
	free (pNode5);
	return 0;
}