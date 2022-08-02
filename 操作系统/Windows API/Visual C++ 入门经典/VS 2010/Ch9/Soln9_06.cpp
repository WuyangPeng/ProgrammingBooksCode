// Soln9_06.cpp : main project file.

#include "stdafx.h"

using namespace System;

generic<typename T > where T:IComparable ref class BinaryTree  
{
private:
  ref class Node
  {
  public:
    // Node constructor
    Node(T obj) : value(obj), left(nullptr), right(nullptr) {}

    // List the node values in order
    void listNode()
    {

      if(left)                           // If there's a left node
        left->listNode();                // Output its value

      Console::Write(format, value);     // Output the current node value
      if(++listCount % 5 == 0)
        Console::WriteLine();

      if(right)                          // If there's a right node
        right->listNode();               // Output its value
    }

    T value;                             // Value of the node
    Node^ left;                          // Reference to left node
    Node^ right;                         // Reference to right node
    static int listCount;                // Count of number of output values
    static String^ format;               // Output formatting string
  };

public:
  BinaryTree() : root(nullptr){}         // Constructor

  void add(T o);                         // Adds an object o to the tree
  void add(T o, Node^ node);             // Adds o relative to pNode node

  // List the nodes in sequences
  void listNodes()
  {
     // Determine format string to output in a column width+2 wide
    Node::format = L"{0," + (width+2) + L"}";
    Node::listCount = 0;
    if(!root)
      Console::WriteLine(L"Binary tree is empty.");
    else 
     root->listNode();
  }

private:
   Node^ root;                           // Reference to the root node
   static int width;                     // Maximum output value width
};

// Add a value to the tree
generic<typename T>
void BinaryTree<T>::add(T o)
{
  if(!root)                              // If there's no root node
    root = gcnew Node(o);                // the new node is the root
  else                                   // otherwise
    add(o, root);                        // add the node (recursive)

  // Determine the maximum output width to allow output formatting in columns
  width = System::Math::Max(width, o->ToString()->Length);
}

// Add a value relative to a given node
generic<typename T>
void BinaryTree<T>::add(T o, Node^ node)
{
  if(o == node->value)                   // If value equals current node
  { // Always add equal values as left node
    Node^ newNode = gcnew Node(o);       // Create the new node for the value
    Node^ temp = node->left;             // Save left for current node
    node->left = newNode;                // then make it refeence to new node
    newNode->left = temp;                // left for new node refer to old left node
  }
  else if(o->CompareTo(node->value) > 0) // If new value is greater than right node value
  {                                      // it must go to the right
    if(!node->right)                     // so if there's no right node
      node->right = gcnew Node(o);       // make the new node the right node
    else                                 // Otherwise
      add(o, node->right);               // add it relative to right node(recursive)
  }
  else                                   // New number is less than current node value
  {
    if(!node->left)                      // so if there's no left node
      node->left = gcnew Node(o);        // make the new node the left node
    else                                 // Otherwise
      add(o, node->left);                // add it relative to the left node(recursive)
  }
}

int main(array<System::String ^> ^args)
{
  BinaryTree<int>^ tree = gcnew BinaryTree<int>; // Create a binary tree to hold integers
  unsigned int number = 0;                       // Stores a number to be added to the tree
  Random^ generator = gcnew Random;

  Console::WriteLine(L"Random value inserted in the tree are:");

  // Add 100 random number to the tree
  for(int i = 0 ; i<100 ; i++)
  {
    number = generator->Next(1, 1000000);
    tree->add(number);
    Console::Write(L"{0,12}",number);
    if((i+1) % 5 == 0)
      Console::WriteLine();
  }
  Console::WriteLine(L"\nOutput from the tree is:");
  tree->listNodes();

  array<String^>^ words = {L"Success", L"is", L"the", L"ability", L"to" , 
                           L"go" , L"from", L"one", L"failure", L"to",
                           L"another", L"with", L"no", L"loss", L"of",
                           L"enthusiasm"};
  BinaryTree<String^>^ strTree = gcnew BinaryTree<String^>; // Create a binary tree to hold strings

  Console::WriteLine(L"\nLoading a new binary tree with the words:");
  int lineCount = 0;
  for each(String^ word in words)
  {
    strTree->add(word);
    Console::Write(L"{0,12}",word);
    if(++lineCount % 5 == 0)
      Console::WriteLine();
  }

  Console::WriteLine(L"\n\nOutput from the tree is:");
  strTree->listNodes();
  Console::WriteLine();
  Console::WriteLine(L"Press Enter to end.");
  Console::ReadLine();

   return 0;
}
