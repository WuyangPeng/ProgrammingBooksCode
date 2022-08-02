/* Code for exercise 7.7.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

#include <iostream>
#include <string>

struct Tnode {
   std::string word;
   int count;
   Tnode *left;
   Tnode *right;
};

Tnode* new_Tnode(std::string const &word) {
   Tnode *node = new Tnode;
   node->word = word;
   node->count = 1;
   node->left = node->right = 0;
   return node;
}

void enter_word(Tnode *&root, std::string const &word) {
   if (root!=0) {
      // First search for the node in the tree:
      Tnode *node = root;
      while (1) {
         int order = word.compare(node->word);
         if (order==0) { // Word is in the tree already
            ++node->count;
            break;
         } else {
            Tnode *&next = order<0? node->left
                                  : node->right;
            if (next==0) { // Word not yet in tree?
               next = new_Tnode(word);
               break;
            } else
               node = next;
         }
      }
   } else { // Create the first node at the root
      root = new_Tnode(word);
   }
}


void write(std::ostream &output, Tnode *node,
           bool indent, int spaces = 2) {
   if (node) {
      write(output, node->left, indent, spaces+2);
      if (indent)
         for (int k = 0; k!=spaces; ++k)
            cout << ' ';
      output << node->word
             << " (" << node->count << ")\n";
      write(output, node->right, indent, spaces+2);
   }
}



int main() {
   std::cout << "Enter words terminated by \"$done\"\n";
   Tnode *tree;
   while (1) {
      std::string word;
      std::cin >> word;
      if (word=="$done") {
         break;
      }
      enter_word(tree, word);
   }
   write(std::cout, tree, true /* do indent */);
   return 0;
}

