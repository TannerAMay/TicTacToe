#include "tanner_ai.h"

tannerAi::tannerAi()
{
  throw std::invalid_argument("Cannot use default constructor.");
}

tannerAi::tannerAi(const char ** &board, const char &letter)
{
  sym = letter;

  copyBoard(board);
  buildTree(board);

}

tannerAi::~tannerAi()
{
  delete tree;

  for(int r = 0; r < 3; r++)
    delete[] boardCopy[r];

  delete[] boardCopy;
  boardCopy = nullptr;
}

void tannerAi::copyBoard(const char ** &board)
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
      copyBoard[r][c] = board[r][c];
  }
}

void tannerAi::buildTree(const char ** &board)
{
  /*
   * To build tree:
   * 1) ensure board is empty
   * 2) assign scores to all locations
   * 3) add nodes to tree
   */

  if(tree != nullptr || !emptyBoard(board))
    throw std::invalid_argument("Tree or board is not empty.");




}

void tannerAi::buildCopyBoard(const char ** &board)
{
  copyBoard = new char *[3];

  for(int r = 0; r < 3; r++)
    copyBoard[3] = new char[3];

  copyBoard(board);
}

void tannerAi::buildScoreBoard(const char **&board)
{
  scoreBoard = new char *[3];

  for(int r = 0; r < 3; r++)
  {
    scoreBoard[3] = new char[3];

    for(int c = 0; c < 3; c++)
      scoreBoard[r][c] = -5;
  }
}

bool tannerAi::emptyBoard(const char ** &board)
{
  for (int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      if(board[r][c] != ' ')
        return false;
    }
  }

  return true;
}

int tannerAi::evaluate(const char **&board)
{
  copyBoard(board);

  if(emptyBoard(board))
  {
    for(int r = 0; r < 3; r += 2)
    {
      for(int c = 0; c < 3; c += 2)
        scoreBoard[r][c] = 5;
    }
  }



}


