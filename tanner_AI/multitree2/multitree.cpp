#include "multitree.h"

/*************
 *  PRIVATE  *
 *************/

void multitree::remove_all(node* rt)
{
  if(rt->get_numChildren() == 0)
    delete rt;
  else
  {
    for(unsigned int i = 0; i < rt->get_numChildren(); i++)
      remove_all(rt->get_child(i));

    delete rt;
  }
}

void multitree::print_help(const node* rt, string indent) const
{
  if(rt->get_numChildren() == 0)
  {
    //unicode for pretty arrows
    cout << indent << "  \u21B1 empty\n"; //up-right arrow
    cout << indent << *rt << endl;
    cout << indent << "  \u21b3 empty\n"; //down-right arr
  }
  else
  {
    const int size = rt->get_numChildren();
    int index = size - 1;

    //"right side" of tree
    for(; index >= size / 2; index--)
      print_help(rt->get_child(index), indent + "  ");

    cout << indent << *rt << endl;

    //"left side" of tree
    for(; index >= 0; index--)
      print_help(rt->get_child(index), indent + "  ");
  }
}

/*************
 *  PUBLIC   *
 *************/


multitree::multitree(const char &p)
{
  root = new node(coords(-1, -1), p, nullptr);
  curr = root;
}


multitree::~multitree()
{
  remove_all(root);

  root = nullptr;
  curr = nullptr;
}

void multitree::print() const
{
  cout << "/*************/\n";
  cout << "/   Printing  /\n";
  cout << "/*************/\n\n";

  print_help(root, "");

  cout << "\n\n/----Done----/\n";
}
