#ifndef MULTITREE_H
#define MULTITREE_H

#include <iostream>
#include <algorithm>
#include "node.h"

using std::cout;
using std::string;
using std::cerr;
using std::endl;

class MultiTree
{
private:
  node *root = nullptr;
  node *curr = root;

  void printRecurse(node *rt, string indent);

public:
  /***Setup and deconstruction***/
  ~MultiTree();

  void print();
  void remove(node *&rt);


  /***adding and removing nodes***/
  //adds node at curr nodes vector postion
  void addNode(const coords &loc, const int &eval);

  void popRoot(node *switchTo);


  /***traversal***/

  //not sure which of these I'll need
  void move(int index); //moves the curr pntr to specified node in children vector
  void move(node index);
  void move(coords index, int val);

};

#endif // MULTITREE_H
