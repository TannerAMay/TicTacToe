#ifndef TANNERAI_H
#define TANNERAI_H

#include "node.h"

class tannerAi
{
  vector<Node> trees;
  vector<coords> openLocs;
  char sym;


public:
  //tannerAi();

  tannerAi(char piece) {sym = piece;}

  //calculates the weight of that specific board location
  int locWeight(int row, int col);

  //only 1: returns 1; 2 in row: returns 2
  coords solvedLevel(char ** board, int col);

  //how many open spaces there are. Starts at 1
  void openLoc();

  //place piece
  void play(int row, int col, char **& board);

  //makes decision trees
  void decTrees();
};

#endif // TANNERAI_H
