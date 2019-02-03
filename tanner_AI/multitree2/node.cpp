#include "node.h"

node::node(const coords &l, const char &p, node* par)
{
  loc = l;
  player = p;
  parent = par;
}

unsigned int node::top_score() const
{
  if(children.size() == 0)
    return 0;

  unsigned int top = 0;

  for(unsigned i = 0; i != children.size(); i++)
  {
    if(children.at(i)->score > children.at(top)->score)
      top = i;
  }

  return top;
}

void node::add_child(node* c)
{
  children.push_back(c);
}

