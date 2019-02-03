#ifndef TANNERAI_H
#define TANNERAI_H

#include "../multitree2/multitree.h"

/*files included at this point
 * <iostream>
 * "../multitree2/coords.h"
 * <vector>
 * "../multitree2/node.h"
 * "../multitree2/multitree.h"
 */

class tannerAi
{
private:
  const char player = '?'; //obviously incorrect
  multitree *tree;

public:
  tannerAi(const char p);
  ~tannerAi() { delete tree; }

  /***tree functions***/
  //generates the tree, without scores
  void gen_tree(char * const * const b);
  //adds the scores to the nodes
  void score_tree();
};

#endif // TANNERAI_H
