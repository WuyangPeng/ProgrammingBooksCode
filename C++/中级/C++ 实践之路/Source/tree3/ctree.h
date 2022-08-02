#if !defined (CTREE_H)
#define CTREE_H
/* (c) Bartosz Milewski 2000 */

#define NUM_NODE 1
#define ADD_NODE 2
#define MULT_NODE 3

struct Node
{
	int type;
};

struct NumNode
{
	int type;
	double val;
};

struct BinNode
{
	int type;
	struct Node * pLeft;
	struct Node * pRight;
};

double Calc (struct Node * pNode);
struct Node * CreateNumNode (double value);
struct Node * CreateBinNode (int type, struct Node * pLeft, struct Node * pRight);

#endif
