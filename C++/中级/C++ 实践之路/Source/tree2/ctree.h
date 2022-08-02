#if !defined (CTREE_H)
#define CTREE_H
/* (c) Bartosz Milewski 2000 */

#define NUM_NODE 1
#define ADD_NODE 2
#define MULT_NODE 3

struct Node
{
	/* Node type */
	int type;
	/* Used only in numeric nodes */
	double val;
	/* Used only in binary nodes */
	struct Node * pLeft;
	struct Node * pRight;
};

double Calc (struct Node * pNode);

#endif
