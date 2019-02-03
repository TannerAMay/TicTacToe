#include "funcs.h"

using std::cerr;

char ** buildBoard()
{
  char **board = new char *[3];

  for(int r = 0; r < 3; r++)
  {
    board[r] = new char [3];
  }

  return board;
}

void printBoard(char ** &board)
{
  cout << "   0   1   2 \n";
  cout << " ------------\n";

  for(int r = 0; r < 3; r++)
  {
    cout << r << "|";

    for(int c = 0; c < 3; c++)
    {
      if(c == 2)
      {
        if(board[r][c] == ' ')
          cout << "   \n";
        else
          cout << " " << board[r][c] << " \n";
      }
      else
      {
        if(board[r][c] == ' ')
          cout << "   |";
        else
          cout << " " << board[r][c] << " |";
      }
    }

    if(r != 2)
      cout << " |---+---+---\n";
  }
  cout << endl;
}

void deleteBoard(char ** &board)
{
  for(int r = 0; r < 3; r++)
  {
    delete[] board[r];
  }

  delete[] board;
  board = nullptr;
}

void setBoard(char ** &board)
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      board[r][c] = ' ';
    }
  }
}

bool full(char ** &board)
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      if(board[r][c] == ' ')
        return 0;
    }
  }

  return 1;
}

bool emptyBoard(char ** board)
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      if(board[r][c] != ' ')
        return false;
    }
  }

  return true;
}

void copyBoard(char * const * const board, char ** b)
{
  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
      b[r][c] = board[r][c];
  }
}

char solved(char ** &board)
{
  char checkerChar = 'c';
  coords checkers[] = {coords(1, 0), coords(1, 1), coords(1, 2), coords(0, 1), coords(2, 1)};

  
  for(int i = 0; i < 5; i++)
  {
    if(board[checkers[i].row][checkers[i].col] != ' ')
    {
      checkerChar = board[checkers[i].row][checkers[i].col];

      if(i == 0 || i == 2) //up down case
      {
        if(board[checkers[i].row - 1][checkers[i].col] == checkerChar //up
           && board[checkers[i].row + 1][checkers[i].col] == checkerChar) //down
          return checkerChar;
      }
      else if(i == 3 || i == 4) //left right case)
      {
        if(board[checkers[i].row][checkers[i].col - 1] == checkerChar //left
           && board[checkers[i].row][checkers[i].col + 1] == checkerChar) //right
          return checkerChar;
      }
      else //center square u,d,l,r,dur, dul, ddr, ddl
      {
        if((board[0][1] == checkerChar //up
            && board[2][1] == checkerChar) //down
           || (board[1][0] == checkerChar //left
               && board[1][2] == checkerChar) //right
           || (board[0][2] == checkerChar //diag. up right
               && board[2][0] == checkerChar) //diag down left
           || (board[0][0] == checkerChar //diag up left
               && board[2][2] == checkerChar)) //diag down right
          return checkerChar;
      }
    }
    else if(i == 4 && board[checkers[i].row][checkers[i].col] == ' ')
      return 'n';
  }

  return 'n';
}

bool emptySlot(char ** &board, int r, int c)
{
  return board[r][c] == ' ';
}

char swapPlayer(const char player)
{
  if (player == 'x')
    return 'o';
  return 'x';
}

char at(char ** board, int r, int c)
{
  return board[r][c];
}

char ** stob(const string &str, const char player)
{
  char ** board = buildBoard();
  setBoard(board);

  const coords crds[] = { coords(0, 0), coords(0, 1), coords(0, 2),
                        coords(1, 0), coords(1, 1), coords(1, 2),
                        coords(2, 0), coords(2, 1), coords(2, 2) };

  for(int i = 0; i < 9; i++)
  {
    if(str[i] == '-')
      board[crds[i].row][crds[i].col] = ' ';
    else if(str[i] == '1')
      board[crds[i].row][crds[i].col] = player;
    else
      board[crds[i].row][crds[i].col] = swapPlayer(player);
  }

  return board;
}

char randPlayer()
{
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);

  if(dis(gen) > 5)
    return 'x';

  return 'o';
}
