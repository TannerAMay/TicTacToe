#ifndef MULTITREE_H
#define MULTITREE_H

#include <algorithm>
#include <fstream>
#include "node.h"

using std::cout;
using std::string;
using std::cerr;
using std::endl;

class MultiTree
{
private:
  node *root = new node(coords(-1, -1), -1, nullptr, "---------");
  node *curr = root;

  void printRecurse(node *rt, string indent);
  void expRecurse(node *rt);
  void impRecurse(std::ifstream &file);

public:
  /***Setup and deconstruction***/
  ~MultiTree();

  void print();
  void remove(node *&rt);


  /***adding and removing nodes***/
  //adds node at curr nodes vector postion
  void addNode(const coords &loc, const float &eval);
  void popRoot(node *switchTo);
  void popRoot(int index);

  /***traversal***/
  //not sure which of these I'll need
  void move(int index); //moves the curr pntr to specified node in children vector
  void move(node *index);
  void move(coords index, float val);
  void moveUp();
  node * at(){ return curr; } //returns the node that curr is pointing to

  /***import/export***/
  void exp(){ expRecurse(root); }
  void imp();

};

#endif // MULTITREE_H
