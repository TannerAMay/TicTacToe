#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include "coords.h"

using std::vector;
using std::string;

struct node
{
  string boardStr = "e";
  coords loc;
  vector<node*> children;
  node *parent;
  float eval;
  int heightAboveSolved = 1;

  node(const coords &rc, const float &val)
  {
    loc = rc;
    eval = val;

    children.push_back(nullptr);
  }

  node(const coords &rc, const float &val, node * const p)
  {
    loc = rc;
    eval = val;
    parent = p;

    children.push_back(nullptr);
  }

  node(const coords &rc, const float &val, node * const p, const string &str)
  {
    loc = rc;
    eval = val;
    parent = p;
    boardStr = str;

    children.push_back(nullptr);
  }

  //finds the max eval in children array
  node * max()
  {
    int sz = children.size();
    int top = 0;

    for(int i = 1; i < sz; i++)
    {
      if(children[i]->eval > children[top]->eval)
        top = i;
    }

    return children[top];
  }

  node * min()
  {
    int sz = children.size();
    int bot = 0; //number that is bigger than normal eval operations

    for(int i = 0; i < sz; i++)
    {
      if(children[i]->eval < children[bot]->eval)
        bot = i;
    }

    return children[bot];
  }

  inline bool operator==(const node &rs){ return loc == rs.loc && (abs(eval - rs.eval) < abs(eval) * 0.00001); }
};

#endif // NODE_H
