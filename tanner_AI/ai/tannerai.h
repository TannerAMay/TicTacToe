#ifndef TANNERAI_H
#define TANNERAI_H

#include "../multitree2/multitree.h"
#include "../../mainGame/funcs2/board.h"

/*files included at this point
 * <iostream>
 * "../multitree2/coords.h"
 * <vector>
 * "../multitree2/node.h"
 * "../multitree2/multitree.h"
 * <iostream>       I don't know if these two lines will cause issues
 * "coords.h"       !
 * <random>
 * "misc_funcs.h"
 * "board.h"
 */

const char EMPTY = ' ';

class tannerAi
{
private:
  char player = '?'; //obviously incorrect
  multitree *tree;

  //recursive helper of gen_tree
  void gen_tree_r(board &b, const char p);
  //recursive helper of eval_tree
  void eval_tree_r();//board &b); //uncomment for testing
  //looks for the child that blocks the opponent and sets its score to 99
  void find_block(const vector<coords> &endSwap, const vector<coords> &midSwap);

  /***Board Functions***/
  //finds all the empty locations on board
  vector<coords> find_empty(const board &b) const;
  //finds all the locations that have a win in the middle:
  //x_x
  vector<coords> mid_empty(const board &b, const char p) const;

public:
  //f is the player that does not go  first, p goes first
  tannerAi(const char f, const char p);
  ~tannerAi() { delete tree; }

  /***tree functions***/
  //generates the tree, without scores
  void gen_tree(const char p);//board &b); //uncomment for testing
  //scores each node
  void eval_tree();//board &b); //uncomment for testing
  void print_tree() const { tree->print(); }
  //same but for ends
  vector<coords> end_empty(const board &b, const char p) const;

  //play
  void play(board &b);
};

#endif // TANNERAI_H
