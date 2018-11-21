#ifndef NODE_H
#define NODE_H

#include <vector>
#include "coords.h"

using std::vector;

struct node
{
  coords loc;
  vector<node*> children;
  int eval;

  node(const coords &rc, const int &val)
  {
    loc = rc;
    eval = val;

    children.push_back(nullptr);
  }
};

#endif // NODE_H
