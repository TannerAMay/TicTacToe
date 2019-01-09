#include "multitree.h"

void MultiTree::remove(node *&rt)
{
  if(rt == nullptr)
    return;

  int size = rt->children.size();

  for(int index = 0; index < size; index++)
    remove(rt->children.at(index));

  delete rt;
  rt = nullptr;
}

void MultiTree::printRecurse(node *rt, string indent)
{
  if(rt == nullptr)
  {
    cout << indent << "   empty" << endl;
  }
  else
  {
    int size = rt->children.size();
    int index = size - 1;

    for(index; index >= size / 2 || index == 0; index--)
        printRecurse(rt->children.at(index), indent + "  ");

    if(index == -1)
      index++;

    cout << indent << " (" << rt->loc.row << ", "
         << rt->loc.col << ") " << rt->eval << endl;

    for(index; index >= 0; index--)
      printRecurse(rt->children.at(index), indent + "  ");
  }

}

MultiTree::~MultiTree()
{
  remove(root);
}

void MultiTree::print()
{
  printRecurse(root, "");
}

void MultiTree::addNode(const coords &loc, const int &eval)
{
  if(root == nullptr)
  {
    root = new node(loc, eval);
    curr = root;
  }
  else
  {
    if(curr->children.front() == nullptr)
      curr->children.front() = new node(loc, eval);
    else
      curr->children.push_back(new node(loc, eval));
  }
}

void MultiTree::popRoot(node *switchTo)
{
  if(root == nullptr)
    return;

  int size = root->children.size();

  for(int index = size - 1; index > 0; index--)
  {
    if(root->children.at(index) == switchTo)
    {
      std::iter_swap(root->children.begin() + 0,
                     root->children.begin() + index);
    }

    remove(root);
    curr = root->children.front();
    delete root;
  }
}

void MultiTree::move(int index)
{
  if(index > curr->children.size())
    throw std::out_of_range("Move \"curr\" failed.");

  curr = curr->children.at(index);
}

void MultiTree::move(node index)
{
  int size = curr->children.size();

  for(int i = 0; i < size; i++)
  {
    if(curr->children.at(i)->loc == index.loc
       && curr->children.at(i)->eval == index.eval)
    {
      curr = curr->children.at(i);
      return;
    }
  }
}

void MultiTree::move(coords index, int val)
{
  int size = curr->children.size();

  for(int i = 0; i < size; i++)
  {
    if(curr->children.at(i)->loc == index
       && curr->children.at(i)->eval == val)
    {
      curr = curr->children.at(i);
      return;
    }
  }
}
