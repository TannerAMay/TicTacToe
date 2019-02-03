#ifndef NODE_H
#define NODE_H

#include "coords.h"
#include <vector>

/*files included at this point
 * <iostream>
 * "coords.h"
 * <vector>
 */

using std::vector;
using std::string;

class node
{
private:
  coords loc;
  char player;
  unsigned int score = 0;
  unsigned int heightAboveSolved = 0;
  //unsigned int numChildren = 0;
  vector<node*> children;
  node* parent;
  string boardStr = "nochange";

public:
  node(const coords &l, const char &p, node* par);

  //returns the index of the node with the highest score
  unsigned int top_score() const;

  //push_back on children and increments numChildren
  void add_child(node* c);

  friend ostream & operator<<(ostream &os, const node &out)
  {
    return os << out.get_boardStr() << " " << out.get_player() << " ("
              << out.get_loc().get_r() << ", " << out.get_loc().get_c()
              << "): " << out.get_score() << " " << out.get_numChildren();
  }

  //g/s
  coords get_loc() const { return loc; }
  char get_player() const { return player; }
  unsigned int get_score() const { return score; }
  unsigned int get_height() const { return heightAboveSolved; }
  unsigned int get_numChildren() const { return children.size(); }
  node* get_child(const unsigned int &i) const { return children.at(i); }
  node* get_parent() const {return parent; }
  string get_boardStr() const { return boardStr; }

  //void set_loc(const coords &l) { loc = l; }
  //void set_peice(const T &p) { piece = p; }
  void set_score(const unsigned int &s) { score = s; }
  void set_height(const unsigned int &h) { heightAboveSolved = h; }
  void set_boardStr(const string &s) { boardStr = s; }
};

#endif // NODE_H
