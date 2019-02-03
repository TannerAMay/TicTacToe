#ifndef TANNER_AI2_H
#define TANNER_AI2_H

#include "../MultiTree/multitree.h"
#include "../../mainGame/funcs.h"

const char EMPTY = ' ';
const char o = 'o';
const char x = 'x';

class tanner_ai2
{
private:
  //MultiTree tree;
  char player = 'y'; //set to a letter that is obviously wrong
  char ** board;

public:
  //for testing only!
  MultiTree tree;

  tanner_ai2(const char p);

  /***tree gen***/
  //goes from bottom up applying formula to each node
  void eval();
  //builds the tree, does not assign evals
  void gentree(const char player);

  /***tree gen helpers***/
  vector<coords> emptyMiddle();
  vector<coords> emptyEnd();
  vector<coords> vEmpty();
  void vPrint(vector<coords> v);

  /***play***/
  void play(char ** b, int &playR, int &playC);


};

#endif // TANNER_AI2_H
