#ifndef MULTITREE_H
#define MULTITREE_H

#include "node.h"

/*files included at this point
 * <iostream>
 * "coords.h"
 * <vector>
 * "node.h"
 */

class multitree
{
private:
  node* root;
  node* curr;

  //recursive helper for destructor
  void remove_all(node* rt);

  //recursive helper for print()
  //needs unicode
  void print_help(const node* rt, string indent) const;

public:
  multitree(const char &p);

  ~multitree();

  //adds a new node to the children vector of curr
  void add_node(const coords &l, const char &piece) {curr->add_child(new node(l, piece, curr)); }

  void move(const unsigned int &i) { curr = curr->get_child(i); }

  void move_up() { curr = curr->get_parent(); }

  void print() const;

  //g/s
  coords get_curr_loc() const { return curr->get_loc(); }
  char get_curr_player() const { return curr->get_player(); }
  unsigned int get_curr_score() const { return curr->get_score(); }
  unsigned int get_curr_height() const { return curr->get_height(); }
  unsigned int get_curr_numChildren() const { return curr->get_numChildren(); }
  string get_curr_boardStr() const { return curr->get_boardStr(); }

  void set_curr_score(const unsigned int &s) { curr->set_score(s); }
  void set_curr_height(const unsigned int &h) { curr->set_height(h); }
  void set_curr_boardStr(const string &s) { curr->set_boardStr(s); }
};

#endif // MULTITREE_H
