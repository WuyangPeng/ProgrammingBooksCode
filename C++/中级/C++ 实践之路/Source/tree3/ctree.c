/* (c) Bartosz Milewski 2000 */
#include "ctree.h"
#include <stdio.h>
#include <malloc.h>

double Calc (struct Node * pNode)
{
	double x = 0.0;
	switch (pNode->type)
	{
		case NUM_NODE:
			x =((struct NumNode *)pNode)->val;
			break;
		case ADD_NODE:
		{
			struct BinNode * pN = (struct BinNode *) pNode;
			x = Calc (pN->pLeft) + Calc (pN->pRight);
			break;
		}
		case MULT_NODE:
		{
			struct BinNode * pN = (struct BinNode *) pNode;
			x = Calc (pN->pLeft) * Calc (pN->pRight);
			break;
		}
		default:
			printf ("Bad node type\n");
	}
	return x;
}

struct Node * CreateNumNode (double value)
{
	struct NumNode * pNode = 
			malloc (sizeof (struct NumNode));
	pNode->type = NUM_NODE;
	pNode->val = value;
	return (struct Node *) pNode;
}

struct Node * CreateBinNode (int type, struct Node * pLeft, struct Node * pRight)
{
	struct BinNode * pNode = 
			malloc (sizeof (struct BinNode));
	pNode->type = type;
	pNode->pLeft = pLeft;
	pNode->pRight = pRight;
	return (struct Node *) pNode;
}

int main ()
{
	struct Node *pNode1, *pNode2, *pNode3, *pNode4, *pNode5;
	double x;
	/* ( 20.0 + (-10.0) ) * 0.1 */
	pNode1 = CreateNumNode (20.0);
	pNode2 = CreateNumNode (-10.0);
	pNode3 = CreateBinNode (ADD_NODE, pNode1, pNode2);
	pNode4 = CreateNumNode (0.1);
	pNode5 = CreateBinNode (MULT_NODE, pNode3, pNode4);
	
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