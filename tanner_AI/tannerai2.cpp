#include "tannerai2.h"

tannerAi2::tannerAi2()
{
  throw std::invalid_argument("Cannot use default constructor.");
}

tannerAi2::tannerAi2(const char ** &board, const char &letter)
{
  sym = letter;

  copyBoard(board);
  buildTree(board);

}

tannerAi2::~tannerAi2()
{
  delete tree;

  for(int r = 0; r < 3; r++)
    delete[] boardCopy[r];

  delete[] boardCopy;
  boardCopy = nullptr;
}

void tannerAi2::copyBoard(const char ** &board)
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
      copyBoard[r][c] = board[r][c];
  }
}

void tannerAi2::buildTree(const char ** &board)
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

void tannerAi2::buildCopyBoard(const char ** &board)
{
  copyBoard = new char *[3];

  for(int r = 0; r < 3; r++)
    copyBoard[3] = new char[3];

  copyBoard(board);
}

void tannerAi2::buildScoreBoard(const char **&board)
{
  scoreBoard = new char *[3];

  for(int r = 0; r < 3; r++)
  {
    scoreBoard[3] = new char[3];

    for(int c = 0; c < 3; c++)
      scoreBoard[r][c] = -5;
  }
}

bool tannerAi2::emptyBoard(const char ** &board)
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

int tannerAi2::evaluate(const char **&board)
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


