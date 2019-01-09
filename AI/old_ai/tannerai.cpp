#include "tannerai.h"

int tannerAi::locWeight(int row, int col)
{
  openLoc();
}

coords tannerAi::solvedLevel(char ** board, int col)
{
  int cStart[] = {0, 1, 2, 0, 2};
  int cDir[] = {0, 0, 0, 1, -1};
  coords loc;

  int colChck = cStart[col];
  int xcntr = 0;
  int ocntr = 0;

  if(board[0][colChck] == 'x' || board[0][colChck] = 'o')
  {
    colChck += cDir[col];
    if(board[1][colChck] == board[0][colChck - cDir[col]])
    {
      colChck += cDir[col];
      if(board[2][colChck] == board[colChck - cDir[col]])
      {
        loc.col = -1;
        loc.row = -1;
        return loc;
      }
      else
      {

      }

    }
  }

  switch(col)
  {
  case 0:
    /*for(int row = 0; row < 3; row++)
    {
      if(board[cStart[col]][row] == 'x')
        xcntr++;
      else if(board[cStart[col]][row] == 'o')
        ocntr++;
    }*/
    if(board[1][0] == board[0][0])
    {

    }
    else if(board[1][0] == board[2][0])
    {

    }
    else if()

    break;

  case 1:


    break;

  case 2:


    break;

  case 3:


    break;

  case 4:


    break;

  }
}

void tannerAi::openLoc()
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      if(board[r][c] == ' ')
      {
        coords tmp(r, c);
        openLocs.push_back(tmp);
      }
    }
  }
}

void tannerAi::play(const coords &loc, char **& board)
{
  board[loc.row][loc.col] = sym;
}

void tannerAi::decTrees()
{

}
