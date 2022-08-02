#include "BookTools.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <iomanip.h>


#define MAXELEM 30000
#define HASHTABLESIZE 1024


class EmployeeInfo
{  
private:
	unsigned long salarycode;
    char *name;
public:
	EmployeeInfo() {};
	EmployeeInfo(char *s, unsigned long id) 
	{
 	  name = new char[strlen(s)+1];
      strcpy(name, s);
	  salarycode = id;
	};

    void SetInfo(char *s, unsigned long id)
    {  
 	  name = new char[strlen(s)+1];
      strcpy(name, s);
	  salarycode = id;
    }
    void PrintInfo()
    {  
      cout << setw(8) << salarycode << " " << name << endl;
    }
    unsigned long GetCode()
    {  
 	  return(salarycode);
    }
    friend int operator<(const EmployeeInfo &r, const EmployeeInfo &s)
    {  
	   return(r.salarycode < s.salarycode);
    }
};


// *************** ARRAY

EmployeeInfo *array = NULL; 

long FillArray()
{
	array = new EmployeeInfo[MAXELEM];				
	for (unsigned long i = 0; i < MAXELEM; i++)
		array[i].SetInfo("JUST A NAME", i);         

	return(0);
}

EmployeeInfo *GetArrayItem1(unsigned long code)
{
	return(&array[code]);  
}

long binsearch(unsigned long item, EmployeeInfo data[], long lb, long ub)
{
   while(1)
   {
      long n = ub-lb;  

      if (n <= 1)
         if (item == data[lb].GetCode())
            return lb;
         else if (item == data[ub].GetCode())
            return ub;
         else
            return -1;

      long middle = ((n+1)/2) + lb;
      unsigned long mItem = data[middle].GetCode();
	
      if (item == mItem)
         return middle;

      if(item < mItem)
         ub = middle-1;
      else
         lb = middle+1;
   }
}


EmployeeInfo *GetArrayItem2(unsigned long code)
{ 
	unsigned long tst = MAXELEM >>1;

	return &array[binsearch(code, array, 0, MAXELEM)];
}

EmployeeInfo *GetArrayItem3(unsigned long code)
{ 
	for (unsigned long i = 0; i < MAXELEM; i++)
		if (array[i].GetCode() == code)
			return(&array[i]);
	return(NULL); 
}

// *************** LINKED LIST
class EmployeeListItem
{  
public:
	EmployeeInfo info;
    EmployeeListItem *next;

	
	EmployeeListItem() {};
	EmployeeListItem(char *s, unsigned long id) 
	{
		info.SetInfo(s, id);
	}

};

class EmployeeList
{  
public:
	EmployeeList()
	{
		items = 0;
		itemlist = NULL;
	}

	void AddListItem(char *s, unsigned long id)
	{
		EmployeeListItem *item = new EmployeeListItem(s, id);  
		item->next = NULL;
	
		if (itemlist == NULL)
			itemlist = item;    
		else
			last->next = item;

		last = item;
		items++;
	}

	EmployeeInfo *GetListItem(unsigned long code)
	{
		EmployeeListItem *p;
		for (p = itemlist; p != NULL; p = p->next)
		{
			if (p->info.GetCode() == code)
				return(&p->info);
		}
		return(NULL);
	}

	void TraverseList()
	{
		EmployeeListItem *p;
		for (p = itemlist; p != NULL; p = p->next)
		{
			// DO SOMETHING USEFUL
		}
	}
private:
	unsigned long items;
	EmployeeListItem *itemlist;
	EmployeeListItem *last;
};

EmployeeList *list = NULL;

long FillList()
{
	list = new EmployeeList;

	for (unsigned long i =0; i < MAXELEM; i++)
	{
		list->AddListItem("JUST A NAME", i);
	}
	return(0);
}


// *************** HASHTABLE

EmployeeList *hashtable = NULL;

unsigned long hash(unsigned long key)
{
    return (key % HASHTABLESIZE);
}

long FillHashtable()
{
	hashtable = new EmployeeList[HASHTABLESIZE];						
	memset(hashtable, 0x0, HASHTABLESIZE * sizeof (EmployeeListItem *));	

	for (unsigned long i =0; i < MAXELEM; i++)
		hashtable[hash(i)].AddListItem("JUST A NAME", i);

	return(0);
}

EmployeeInfo *GetHashtableItem(unsigned long code)
{
	return(hashtable[hash(code)].GetListItem(code));
}

// ************Binary Tree

class TreeNode
{
  friend class Tree;

  public:
    TreeNode(char *s, unsigned long id)
	{
		info.SetInfo(s, id);
		left = NULL;
		right = NULL;
	}
    EmployeeInfo *GetInfo()
	{
		return(&info);
	}

  private:
    TreeNode *left;
    TreeNode *right;
	EmployeeInfo info;
};

class Tree
{
  public:
    ~Tree();
    Tree() { root = NULL; };

	void AddNode(char *s, unsigned long id);
    
    void RemoveTree(TreeNode *current);

	TreeNode *GetNode(unsigned long id)						{ return(GetNode(root, id)); }
    TreeNode *GetNode(TreeNode *current, unsigned long id);

    void InorderWalk()								{ InorderWalk(root); }
    void InorderWalk(TreeNode *current);	
    void PreorderWalk()								{ PreorderWalk(root); }
    void PreorderWalk(TreeNode *current);  
    void PostorderWalk()							{ PostorderWalk(root); }
    void PostorderWalk(TreeNode *current); 

  private:
    TreeNode *root;
};


Tree::~Tree()
{
	RemoveTree(root);
}  

void Tree::RemoveTree(TreeNode *current)
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


TreeNode *Tree::GetNode(TreeNode *current, unsigned long id)
{
    if (current == NULL) 
		return(NULL);

	int result = id - current->info.GetCode();

	if (result == 0)
		return(current);   

    if (result < 0) 
		return(GetNode(current->left, id));
    else               
		return(GetNode(current->right, id));
}


void Tree::AddNode(char *s, unsigned long id)
{
	TreeNode *newNode;

	newNode = new TreeNode(s, id);

	if(root == NULL)	
		root = newNode;
	else
	{
		TreeNode *p =root, *q;

		while(p != NULL) 
		{
			 q = p;
			 if(newNode->info < p->info)
				p = p->left;
			 else
				p = p->right;
		}
		if(newNode->info < q->info)
			q->left = newNode;
		else
			q->right = newNode;
		}
}


void Tree::InorderWalk(TreeNode *current)
{
	if(current != NULL)
	{
		InorderWalk(current->left);
		current->info.PrintInfo();
		InorderWalk(current->right);
	}
}


void Tree::PreorderWalk(TreeNode *current)
{
	if(current != NULL)
	{
		current->info.PrintInfo();
		PreorderWalk(current->left);
		PreorderWalk(current->right);
	}
}


void Tree::PostorderWalk(TreeNode *current)
{
	if(current != NULL)
	{
		PostorderWalk(current->left);
		PostorderWalk(current->right);
		current->info.PrintInfo();
	}
}


Tree tree, tree2;

long FillTree()
{ 
	for (unsigned long i =0; i < MAXELEM; i++)
		tree.AddNode("JUST A NAME", i); 

	return(0);
}


void NiceFillTree(unsigned long lower, unsigned long upper)
{
	if (lower < upper)
	{
		unsigned long current = (lower+upper +1) >>1;

		tree2.AddNode("JUST A NAME", current); 
		NiceFillTree(lower, current-1);
		NiceFillTree(current+1, upper);
	}
	else
		if (lower == upper)
			tree2.AddNode("JUST A NAME", lower); 
}

long FillBalancedTree()
{ 

	NiceFillTree(0, MAXELEM);
	return(0);
}


//**************************************************************
// LOOKUP item.
long LookupArray1()
{
	unsigned long i;
	
	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i!= GetArrayItem1(i)->GetCode())
			cout << "Error" << endl;
	
	for (i = 0; i < 500; i++)
		if (i!= GetArrayItem1(i)->GetCode())
			cout << "Error" << endl;

	return(0);
}

long LookupArray2()
{
	unsigned long i;
	
	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i!= GetArrayItem2(i)->GetCode())
			cout << "Error" << endl;

	for (i = 0; i < 500; i++)
		if (i!= GetArrayItem2(i)->GetCode())
			cout << "Error" << endl;
	return(0);
}
long LookupArray3()
{
	unsigned long i;

	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i!= GetArrayItem3(i)->GetCode())
			cout << "Error" << endl;

	for (i = 0; i < 500; i++)
		if (i!= GetArrayItem3(i)->GetCode())
			cout << "Error" << endl;
	return(0);
}

long LookupList()
{
	unsigned long i;
	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i != list->GetListItem(i)->GetCode())  
				cout << "Error" << endl;

	for (i = 0; i < 500; i++)
		if (i != list->GetListItem(i)->GetCode())  
				cout << "Error" << endl;

	return(0);
}

long LookupHashtable()
{
	unsigned long i;

	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i != GetHashtableItem(i)->GetCode())
				cout << "Error" << endl;
			
	for (i = 0; i < 500; i++)
		if (i != GetHashtableItem(i)->GetCode())
				cout << "Error" << endl;
			

	return(0);
}

long LookupTree()
{
	unsigned long i;

	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i != tree.GetNode(i)->GetInfo()->GetCode())
				cout << "Error" << endl;
	for (i = 0; i < 500; i++)
		if (i != tree.GetNode(i)->GetInfo()->GetCode())
				cout << "Error" << endl;

	return(0);
}


long LookupBalancedTree()
{
	unsigned long i;

	for (i = MAXELEM - 500; i < MAXELEM; i++)
		if (i != tree2.GetNode(i)->GetInfo()->GetCode())
				cout << "Error" << endl;
	for (i = 0; i < 500; i++)
		if (i != tree2.GetNode(i)->GetInfo()->GetCode())
				cout << "Error" << endl;

	return(0);
}



//**************************


long TraverseArray()
{
	unsigned long i;
	
	for (i = 0; i < MAXELEM; i++)
		array[i];   // DO SOMETHING USEFUL
	
	return(0);
}

long TraverseList()
{
	list->TraverseList();
	return(0);
}

long TraverseBalancedTree()
{
	tree2.InorderWalk();
	return(0);
}


int main (int argc, char *argv[])
{

	cout << "Filling" << endl;
	cout << "  Array   List   Hash  UnbTr   BalTr" << endl;
	cout << setw(7) << time_fn(FillArray);	
    cout << setw(7) << time_fn(FillList);	
    cout << setw(7) << time_fn(FillHashtable);	
    cout << setw(7) << time_fn(FillTree);	
    cout << setw(7) << time_fn(FillBalancedTree);	

	cout << endl << endl;

	cout << "Lookup first and last 250 entries" << endl; 
	cout << "  Array1 Array2 Array3  List   Hash  UnbTr  BalTr" << endl;
	cout << setw(7) << time_fn(LookupArray1);	
	cout << setw(7) << time_fn(LookupArray2);	
	cout << setw(7) << time_fn(LookupArray3);	
    cout << setw(7) << time_fn(LookupList);	
    cout << setw(7) << time_fn(LookupHashtable);	
	cout << setw(7) << time_fn(LookupTree);	
    cout << setw(7) << time_fn(LookupBalancedTree);	

	cout << endl << endl << "Note:" << endl;
	cout << "Array1: if we can use 'key' as the index of the array" << endl;
	cout << "Array2: if input is sorted --> binary search" << endl;
	cout << "Array3: if input is unsorted" << endl;
	cout << "UnbTr : Unbalanced tree" << endl;
	cout << "Tree  : Balanced tree" << endl;
	cout << endl << endl;

	return (0);
}        

