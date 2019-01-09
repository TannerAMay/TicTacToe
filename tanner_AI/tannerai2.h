#ifndef TANNERAI2_H
#define TANNERAI2_H

#include "MultiTree/multitree.h"

using std::cin;

class tannerAi2
{
private:
  MultiTree *tree = nullptr;
  char ** copyBoard = nullptr;
  int ** scoreBoard = nullptr;
  char sym = 'M';

public:
  tannerAi2();
  tannerAi2(const char ** &board, const char &letter);
  ~tannerAi2();

  /***General Utilities***/
  void copyBoard(const char ** &board);

  /***Board and tree building utilities***/
  void buildTree(const char ** &board);
  void buildCopyBoard(const char ** &board);
  void buildScoreBoard(const char ** &board);
  bool emptyBoard(const char ** &board);
  int evaluate(const char ** &board);

  /***Evaluation Utilities***/
};

#endif // TANNERAI2_H
