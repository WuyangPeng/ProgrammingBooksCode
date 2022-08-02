#include <iostream>
#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;
using std::cout;

struct node : instrumented
  { // struct to demonstrate cycles
  shared_ptr<node> next;
  weak_ptr<node> weak_next;
  };

static void cycle()
  { // constructs two nodes, destroys none
  cout << "Cycle:\n";
  node *head = new node;
  node *N1 = new node;
  shared_ptr<node> root(head);
  head->next = shared_ptr<node>(N1);
  N1->next = root;          // cycle
  }

static void no_cycle()
  { // constructs two nodes, destroys both
  cout << "Break cycle:\n";
  node *head = new node;
  node *N1 = new node;
  shared_ptr<node> root(head);
  head->next = shared_ptr<node>(N1);
  N1->weak_next = root;     // no cycle
  }

int main()
  { // demonstrate creating cycle and breaking cycle
  cycle();
  no_cycle();
  return 0;
  }