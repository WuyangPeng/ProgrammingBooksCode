// Soln9_05.cpp : main project file.

#include "stdafx.h"

using namespace System;

ref class BinaryTree
{
private:
  ref class Node
  {
  public:
    // Node constructor
    Node(int n) : value(n), left(nullptr), right(nullptr) {}

    // List the node values in order
    void listNode()
    {

      if(left)                          // If there's a left node
        left->listNode();               // Output its value

      Console::Write(L"{0, 12}", value); // Output the current node value
      if(++listCount % 5 == 0)
        Console::WriteLine();

      if(right)                          // If there's a right node
        right->listNode();               // Output its value
    }

    int value;                           // Value of the node
    Node^ left;                          // Reference to left node
    Node^ right;                         // Reference to right node
    static int listCount;                // Count of number of output values
  };

public:
  BinaryTree() : root(nullptr){}         // Constructor

  void add(int n);                       // Adds a value to the tree
  void add(int n, Node^ node);           // Adds n relative to pNode node

  // List the nodes in sequences
  void listNodes()
  {
    Node::listCount = 0;
    if(!root)
      Console::WriteLine(L"Binary tree is empty.");
    else 
      root->listNode();
  }

private:
   Node^ root;                           // Reference to the root node
};

// Add a value to the tree
void BinaryTree::add(int n)
{
  if(!root)                              // If there's no root node
    root = gcnew Node(n);                // the new node is the root
  else                                   // otherwise
    add(n, root);                        // add the node (recursive)
}

// Add a value relative to a given node
void BinaryTree::add(int n, Node^ node)
{
  if(n == node->value)                   // If value equals current node
  { // Always add equal values as left node
    Node^ newNode = gcnew Node(n);       // Create the new node for the value
    Node^ temp = node->left;             // Save left for current node
    node->left = newNode;                // then make it refeence to new node
    newNode->left = temp;                // left for new node refer to old left node
  }
  else if(n > node->value)               // If new value is greater than right node value
  {                                      // it must go to the right
    if(!node->right)                     // so if there's no right node
      node->right = gcnew Node(n);       // make the new node the right node
    else                                 // Otherwise
      add(n, node->right);               // add it relative to right node(recursive)
  }
  else                                   // New number is less than current node value
  {
    if(!node->left)                      // so if there's no left node
      node->left = gcnew Node(n);        // make the new node the left node
    else                                 // Otherwise
      add(n, node->left);                // add it relative to the left node(recursive)
  }
}

int main(array<System::String ^> ^args)
{
  BinaryTree^ tree = gcnew BinaryTree; // Create a binary tree
  unsigned int number = 0;             // Stores a number to be added to the tree
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
  Console::WriteLine(L"Output from the tree is:");
  tree->listNodes();
  Console::WriteLine(L"Press Enter to end.");
  Console::ReadLine();
   return 0;
}
