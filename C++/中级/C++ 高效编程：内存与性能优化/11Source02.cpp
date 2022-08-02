#include "BookTools.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <iomanip.h>


#define MAXELEM 50000
class EmployeeInfo
{  
public:
	unsigned long salaryCode;
	char *name;
	
	EmployeeInfo() {};
	EmployeeInfo(char *s, unsigned long id) 
	{
		name = new char[strlen(s)+1];
		strcpy(name, s);
		salaryCode = id;
	};
	
	void Setdata(char *s, unsigned long id)
	{  
		name = new char[strlen(s)+1];
		strcpy(name, s);
		salaryCode = id;
	}
	void Printdata()
	{  
		cout << setw(8) << salaryCode << " " << name << endl;
	}
	unsigned long GetCode()
	{  
		return(salaryCode);
	}
	
	friend int operator==(const EmployeeInfo &r, const EmployeeInfo &s);
	friend int operator==(const EmployeeInfo &r, const unsigned long id);
	friend int operator==(const unsigned long id, const EmployeeInfo &s);
	
	friend int operator<(const EmployeeInfo &r, const EmployeeInfo &s);
	friend int operator<(const EmployeeInfo &r, const unsigned long id);
	friend int operator<(const unsigned long id, const EmployeeInfo &s);
	
	friend int operator>(const EmployeeInfo &r, const EmployeeInfo &s);
	friend int operator>(const EmployeeInfo &r, const unsigned long id);
	friend int operator>(const unsigned long id, const EmployeeInfo &s);
	
};


int operator==(const EmployeeInfo &r, const EmployeeInfo &s)
{  
	return(r.salaryCode == s.salaryCode);
}

int operator==(const EmployeeInfo &r, const unsigned long id)
{  
	return(r.salaryCode == id);
}

int operator==(const unsigned long id, const EmployeeInfo &s)
{  
	return(id == s.salaryCode);
}

int operator<(const EmployeeInfo &r, const EmployeeInfo &s)
{  
	return(r.salaryCode < s.salaryCode);
}

int operator<(const EmployeeInfo &r, const unsigned long id)
{  
	return(r.salaryCode < id);
}

int operator<(const unsigned long id, const EmployeeInfo &s)
{  
	return(id < s.salaryCode);
}

int operator>(const EmployeeInfo &r, const EmployeeInfo &s)
{  
	return(r.salaryCode > s.salaryCode);
}

int operator>(const EmployeeInfo &r, const unsigned long id)
{  
	return(r.salaryCode > id);
}

int operator>(const unsigned long id, const EmployeeInfo &s)
{  
	return(id > s.salaryCode);
}


// ************Binary Tree
typedef enum {RED, BLACK} Colors;

template <class T> class Node 
{
public:
    Node    *left;
    Node    *right;
    T        data;
    Node    *parent;  
    Colors    color;  
};

template <class T> class Tree
{
public:
    Node<T> *root;
    ~Tree();
    Tree() { root = NULL;};
    
    virtual Node <T> *InsertNode(T data);

    virtual void DeleteNode(unsigned long id) { DeleteNode(FindNode(id)); } 
    virtual void DeleteNode(T data)           { DeleteNode(FindNode(data)); }
    virtual void DeleteNode(Node<T> *del);
    
    T FindData(unsigned long id)                { return(FindData(root, id)); }
    T FindData(Node<T> *current, unsigned long id);

    Node <T>*FindNode(unsigned long id)            { return(FindNode(root, id)); }
    Node <T>*FindNode(Node<T> *current, unsigned long id);            
    Node <T>*FindNode(T data)                   { return(FindNode(root, data));}        
    Node <T>*FindNode(Node<T> *current, T data);            
    
    void InorderWalk()                                { InorderWalk(root); }
    void InorderWalk(Node<T> *current);    
    void PreorderWalk()                                { PreorderWalk(root); }
    void PreorderWalk(Node<T> *current);  
    void PostorderWalk()                            { PostorderWalk(root); }
    void PostorderWalk(Node<T> *current); 
private:
    void RemoveTree(Node<T> *current);
    void ReInsertTree(Node<T> *current)             { ReInsertTree(root, current); }
    void ReInsertTree(Node<T> *entrance, Node<T> *current);
};


template <class T>
Tree<T>::~Tree()
{
    RemoveTree(root);
}  

template <class T>
void Tree<T>::RemoveTree(Node<T> *current)
{
    if (current != NULL)
    {
        if(current->right != NULL)
            RemoveTree(current->right);
        if(current->left != NULL)
            RemoveTree(current->left);
        
        delete current;
    }
}

template <class T>
void Tree<T>::ReInsertTree(Node<T> *entrance, Node<T> *current)
{
    if (current != NULL)
    {
        if(current->right != NULL)
            ReInsertTree(entrance, current->right);
        if(current->left != NULL)
            ReInsertTree(entrance, current->left);
        
        InsertNode(current->data);
        delete current;
    }
}

template <class T>
T Tree<T>::FindData(Node<T> *current, unsigned long id)
{
    while (current != NULL) 
    {
        if (*(T) current->data == id) 
            return (current->data);
        current = (id < *(T) current->data) ? current->left : current->right;
    }
    
    return(NULL);
}

template <class T>
Node<T> *Tree<T>::FindNode(Node<T> *current, unsigned long id)
{
    while (current != NULL) 
    {
        if (*(T) current->data == id) 
            return (current);
        current = (id < *(T) current->data) ? current->left : current->right;
    }
    
    return(NULL);
}


template <class T>
Node<T> *Tree<T>::FindNode(Node<T> *current, T data)
{
    while (current != NULL) 
    {
        if (*(T) current->data == *(T)data) 
            return (current);
        current = (*(T)data < *(T) current->data) ? current->left : current->right;
    }
    
    return(NULL);
}

template <class T>
Node <T>*Tree<T>::InsertNode(T data) 
{ 
    Node<T> *current = root;
    Node<T> *newNode = NULL;
    Node<T> *oldNode = NULL;
    
    while(current != NULL) 
    {
        if(*(T)data == *(T)current->data)
            return(current);

        oldNode = current;
        if(*(T)data < *(T)current->data)
            current = current->left;
         else
            current = current->right;
    }

    if ((newNode = (Node<T>*)malloc (sizeof(*newNode))) == NULL) 
        return(NULL);  
    
    newNode->right    = NULL;
    newNode->left    = NULL;
    newNode->data    = data;
    newNode->parent = oldNode;
    
    if(root == NULL)    
        root = newNode;
    else
    {
        if(*(T)data < *(T)oldNode->data)
            oldNode->left = newNode;
        else
            oldNode->right = newNode;
    }
    return(newNode);
}

template <class T>
void Tree<T>::DeleteNode(Node <T> *del)
{
    if(del != NULL)
    {
        if (del == root)
        {
            if (root->left != NULL)
            {
                root = root->left;
                ReInsertTree(root, del->right);
            }
            else
                root = root->right;
        }
        else
        {
            if (del->parent->left == del)
                del->parent->left = del->left;
            else
                del->parent->right = NULL;

            ReInsertTree(del->parent, del->right);
        }
        if (del == root)
                root = NULL;
        delete del;
    }
}


template <class T>
void Tree<T>::InorderWalk(Node<T> *current)
{
    if(current != NULL)
    {
        InorderWalk(current->left);
        current->data->Printdata();
        InorderWalk(current->right);
    }
}


template <class T>
void Tree<T>::PreorderWalk(Node<T> *current)
{
    if(current != NULL)
    {
        current->data->Printdata();
        PreorderWalk(current->left);
        PreorderWalk(current->right);
    }
}

template <class T>
void Tree<T>::PostorderWalk(Node<T> *current)
{
    if(current != NULL)
    {
        PostorderWalk(current->left);
        PostorderWalk(current->right);
        current->data->Printdata();
    }
}



//****************** RedBlackTree

template <class T> class RedBlackTree : public Tree <T>
{
    
public:

    RedBlackTree() 
    { 
        LEAF = new Node <T>;
        LEAF->parent = NULL;
        LEAF->left   = LEAF;
        LEAF->right  = LEAF;
        LEAF->data   = NULL; 
        LEAF->color  = BLACK;
        root = LEAF;
    };
    ~RedBlackTree() 
    {   
        ReplaceSentinels(root);
        if (root == LEAF)
            root = NULL;
        delete LEAF;
        LEAF = NULL;
    };
    Node <T>*InsertNode(T data);
    void DeleteNode(unsigned long id) { DeleteNode(FindNode(id)); } 
    void DeleteNode(T data)           { DeleteNode(FindNode(data)); }
    void DeleteNode(Node <T> *del); 
    
private:
    Node <T>*LEAF ;
    void RotateLeft(Node <T>*pivot);
    void RotateRight(Node <T>*pivot); 
    void InsertRebalance(Node <T>*pivot); 
    void DeleteRebalance(Node <T>*pivot); 
    void ReplaceSentinels(Node <T>*pivot);
};

template <class T>
void RedBlackTree<T>::ReplaceSentinels(Node <T>*current) 
{
    if ((current) && (current != LEAF))
    {
        if (current->left == LEAF)
            current->left = NULL;
        else
            ReplaceSentinels(current->left);
        if (current->right == LEAF)
            current->right = NULL;
        else
            ReplaceSentinels(current->right);
    }
}


template <class T>
void RedBlackTree<T>::RotateLeft(Node <T>*pivot) 
{
    Node <T>*pivotChild = pivot->right;
    
    pivot->right = pivotChild->left;
    if (pivotChild->left != LEAF) 
        pivotChild->left->parent = pivot;
    
    if (pivotChild != LEAF) 
        pivotChild->parent = pivot->parent;
    if (pivot->parent) 
    {
        if (pivot == pivot->parent->left)
            pivot->parent->left = pivotChild;
        else
            pivot->parent->right = pivotChild;
    }
    else 
        root = pivotChild;
    
    pivotChild->left = pivot;
    if (pivot != LEAF) 
        pivot->parent = pivotChild;
}

template <class T >
void RedBlackTree<T>::RotateRight(Node <T>*pivot) 
{
    Node <T> *pivotChild = pivot->left;
    
    pivot->left = pivotChild->right;
    if (pivotChild->right != LEAF) 
        pivotChild->right->parent = pivot;
    
    if (pivotChild != LEAF) 
        pivotChild->parent = pivot->parent;
    if (pivot->parent) 
    {
        if (pivot == pivot->parent->right)
            pivot->parent->right = pivotChild;
        else
            pivot->parent->left = pivotChild;
    }
    else 
        root = pivotChild;
    
    pivotChild->right = pivot;
    if (pivot != LEAF) 
        pivot->parent = pivotChild;
}

template <class T >
void RedBlackTree<T>::DeleteRebalance(Node <T>*subTree) 
{
    Node <T> *sibling;
    
    while (subTree != root && subTree->color == BLACK) 
    {
        if (subTree == subTree->parent->left) 
        {
            sibling = subTree->parent->right;
            if (sibling->color == RED) 
            {
                subTree->parent->color = RED;
                sibling->color = BLACK;
                RotateLeft (subTree->parent);
                sibling = subTree->parent->right;
            }
            if (sibling->left->color != RED && sibling->right->color != RED) 
            {
                subTree = subTree->parent;
                sibling->color = RED;
            }
            else 
            {
                if (sibling->right->color != RED) 
                {
                    sibling->color = RED;
                    sibling->left->color = BLACK;
                    RotateRight (sibling);
                    sibling = subTree->parent->right;
                }
                
                subTree->parent->color = BLACK;
                sibling->right->color = BLACK;
                sibling->color = subTree->parent->color;
                RotateLeft (subTree->parent);
                subTree = root;
            }
        }
        else 
        {
            sibling = subTree->parent->left;
            if (sibling->color == RED) 
            {
                sibling->color = BLACK;
                subTree->parent->color = RED;
                RotateRight (subTree->parent);
                sibling = subTree->parent->left;
            }
            if (sibling->left->color != RED && sibling->right->color != RED) 
            {
                subTree = subTree->parent;
                sibling->color = RED;
            }
            else 
            {
                if (sibling->left->color == BLACK) 
                {
                    sibling->color = RED;
                    sibling->right->color = BLACK;
                    RotateLeft (sibling);
                    sibling = subTree->parent->left;
                }
                
                subTree->parent->color = BLACK;
                sibling->left->color = BLACK;
                sibling->color = subTree->parent->color;
                RotateRight (subTree->parent);
                subTree = root;
            }
        }
    }
    subTree->color = BLACK;
}


template <class T >
void RedBlackTree<T>::InsertRebalance(Node <T>*newNode) 
{
    Node <T>*tempNode;
    
    while (newNode != root && newNode->parent->color == RED) 
    {
        if (newNode->parent == newNode->parent->parent->left) 
        {
            tempNode = newNode->parent->parent->right;
            if (tempNode->color == BLACK) 
            {
                if (newNode == newNode->parent->right) 
                {
                    newNode = newNode->parent;
                    RotateLeft(newNode);
                }
                newNode->parent->parent->color = RED;
                newNode->parent->color = BLACK;
                RotateRight(newNode->parent->parent);
            }
            else 
            {
                tempNode->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
        } 
        else 
        {
            tempNode = newNode->parent->parent->left;
            if (tempNode->color == BLACK) 
            {
                if (newNode == newNode->parent->left) 
                {
                    newNode = newNode->parent;
                    RotateRight(newNode);
                }
                newNode->parent->parent->color = RED;
                newNode->parent->color = BLACK;
                RotateLeft(newNode->parent->parent);
            }
            else 
            {
                newNode->parent->parent->color = RED;
                newNode->parent->color = BLACK;
                tempNode->color = BLACK;
                newNode = newNode->parent->parent;
            }
        }
    }
    root->color = BLACK;
}


template <class T >
Node <T>*RedBlackTree<T>::InsertNode(T data) 
{
    Node <T>*current, *parent, *newNode;
    
    current = root;
    parent = 0;
    while ((current) && (current != LEAF)) 
    {
        if (*(T) data == *(T) current->data) 
            return (current);
        parent = current;
        current = (*(T) data < *(T) current->data) ? current->left : current->right;
    }
    
    if ((newNode = (Node<T>*)malloc (sizeof(*newNode))) == NULL) 
        return(NULL); 
    
    newNode->parent = parent;
    newNode->right    = LEAF;
    newNode->left    = LEAF;
    newNode->data    = data;
    newNode->color    = RED;
    
    if(parent) 
    {
        if(*(T) data < *(T) parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    } 
    else 
        root = newNode;
    
    InsertRebalance(newNode);
    
    return(newNode);
}


template <class T >
void RedBlackTree<T>::DeleteNode(Node <T>*del) 
{
    Node<T> *successorChild, *successor;
    
    if (root == NULL || !del || del == LEAF)
        return;
    
    
    if (del->left == LEAF || del->right == LEAF) 
    {
        successor = del; 
    }
    else 
    {
        successor = del->right;
        while (successor->left != LEAF) 
            successor = successor->left;
    }
    
    if (successor->left != LEAF)
        successorChild = successor->left;
    else
        successorChild = successor->right;
    
    successorChild->parent = successor->parent;
    if (successor->parent)
        if (successor == successor->parent->left)
            successor->parent->left = successorChild;
        else
            successor->parent->right = successorChild;
    else
        root = successorChild;
    
    if (successor != del) 
        del->data = successor->data;
    
    if (successor->color == BLACK)
        DeleteRebalance (successorChild);
    
    free (successor);
}



Tree <EmployeeInfo*> tree;
RedBlackTree <EmployeeInfo*> RBTree;

void NiceFillTree(unsigned long lower, unsigned long upper)
{
	if (lower < upper)
	{
		unsigned long current = (lower+upper +1) >>1;
		
		EmployeeInfo *data = new EmployeeInfo("JUST A NAME", current);
		tree.InsertNode(data);  
		NiceFillTree(lower, current-1);
		NiceFillTree(current+1, upper);
	}
	else
		if (lower == upper)
		{
     		EmployeeInfo *data = new EmployeeInfo("JUST A NAME", lower);
			tree.InsertNode(data); 
		}
}

long FillBalancedTree()
{
	
	NiceFillTree(1, MAXELEM);
	return(0);
}


long CheckBalancedTree()
{
	unsigned long i, code = 0;
	EmployeeInfo *info;
	
	for (i = 1; i <= MAXELEM; i++)
	{
		info =tree.FindData(i);
		if (!info)
			cout << "Error: Data Block Missing" << i << endl;
		else
		{
			if (info->salaryCode <= code)
				cout << "Error: Order" << i << "expected but found " << info->salaryCode << endl;
    		code = info->salaryCode;
		}
	}	
	return(0);
}

long DeleteFromBalancedTree()
{
	for (unsigned long i = 1; i <= MAXELEM; i++)
	{
		tree.DeleteNode(i);
	}	
	return(0);
}

long DeleteFromRBTree()
{
	for (unsigned long i = 1; i <= MAXELEM; i++)
	{
		RBTree.DeleteNode(i);
	}	
	return(0);
}

long FillRBTree()
{ 
	unsigned long i;
	
	for (i =1; i <= MAXELEM; i++)
	{
		EmployeeInfo *p = new EmployeeInfo("JUST A NAME", i);
		RBTree.InsertNode(p); 
	}
	return(0);
}

long CheckRBTree()
{
	unsigned long i, code = 0;
	EmployeeInfo *info;
	
	for (i = 1; i <= MAXELEM; i++)
	{
		info =RBTree.FindData(i);
		if (!info)
			cout << "Error: Data Block Missing" << i << endl;
		else
		{
			if (info->salaryCode <= code)
				cout << "Error: Order" << i << "expected but found " << info->salaryCode << endl;

			code = info->salaryCode;
		}
	}	
	return(0);
}


void main ()
{
		cout << "Filling" << endl;
		cout << "   Tree RBTree" << endl;
		cout << setw(7) << time_fn(FillBalancedTree);	
		cout << setw(7) << time_fn(FillRBTree);	
		
		cout << endl << endl;
		
		cout << "Lookup and check all entries" << endl; 
		cout << "   Tree RBTree" << endl;
		cout << setw(7) << time_fn(CheckBalancedTree);	
		cout << setw(7) << time_fn(CheckRBTree);	
		
		cout << endl << endl;

		cout << "Remove all entries one by one" << endl; 
		cout << "   Tree RBTree" << endl;
		cout << setw(7) << time_fn(DeleteFromBalancedTree);	
		cout << setw(7) << time_fn(DeleteFromRBTree);	

		cout << endl << endl;

		int c = getchar();
}

