#include "board.h"

board::board()
{
  brd = new char *[3];

  for(unsigned int r = 0; r < 3; r++)
    brd[r] = new char[3];

  reset();
}

board::~board()
{
  for(unsigned int r = 0; r < 3; r++)
    delete[] brd;

  delete[] brd;
  brd = nullptr;
}

void board::reset()
{
  if(brd == nullptr)
    throw "Brd not allocated.";

  for(unsigned int r = 0; r < 3; r++)
  {
    for(unsigned int c = 0; c < 3; c++)
      brd[r][c] = ' ';
  }
}

bool board::full() const
{
  for(unsigned int r = 0; r < 3; r++)
  {
    for(unsigned int c = 0; c < 3; c++)
    {
      if(brd[r][c] == ' ')
        return false;
    }
  }

  return true;
}

bool board::empty() const
{
  for(unsigned int r = 0; r < 3; r++)
  {
    for(unsigned int c = 0; c < 3; c++)
    {
      if(brd[r][c] != ' ')
        return false;
    }
  }

  return true;
}

char board::solved() const
{
  char checkerChar = '?';
  coords checkers[] = {coords(1, 0), coords(1, 1), coords(1, 2), coords(0, 1), coords(2, 1)};

  for(unsigned int i = 0; i < 5; i++)
  {
    if(brd[checkers[i].get_r()][checkers[i].get_c()] != ' ')
    {
      checkerChar = brd[checkers[i].get_r()][checkers[i].get_c()];

      if(i == 0 || i == 2) //up down case
      {
        if(brd[checkers[i].get_r() - 1][checkers[i].get_c()] == checkerChar //up
           && brd[checkers[i].get_r() + 1][checkers[i].get_c()] == checkerChar) //down
          return checkerChar;
      }
      else if(i == 3 || i == 4) //left right case)
      {
        if(brd[checkers[i].get_r()][checkers[i].get_c() - 1] == checkerChar //left
           && brd[checkers[i].get_r()][checkers[i].get_c() + 1] == checkerChar) //right
          return checkerChar;
      }
      else //center square u,d,l,r,dur, dul, ddr, ddl
      {
        if((brd[0][1] == checkerChar //up
            && brd[2][1] == checkerChar) //down
           || (brd[1][0] == checkerChar //left
               && brd[1][2] == checkerChar) //right
           || (brd[0][2] == checkerChar //diag. up right
               && brd[2][0] == checkerChar) //diag down left
           || (brd[0][0] == checkerChar //diag up left
               && brd[2][2] == checkerChar)) //diag down right
          return checkerChar;
      }
    }
    else if(i == 4 && brd[checkers[i].get_r()][checkers[i].get_c()] == ' ')
      return 'n';
  }

  return 'n';
}

void board::place(const unsigned int r, const unsigned int c, const char player)
{
  if(brd[r][c] == ' ' && r < 3 && c < 3)
    brd[r][c] = player;
  else
    throw "Non-empty board location or invalid integer range.";
}

char board::at(const unsigned int r, const unsigned int c) const
{
  return brd[r][c];
}

void board::print() const
{
  cout << "   0   1   2 \n";
  cout << "  ___________\n";

  for(unsigned int r = 0; r < 3; r++)
  {
    cout << r << "|";

    for(unsigned int c = 0; c < 3; c++)
    {
      if(c == 2)
      {
        if(brd[r][c] == ' ')
          cout << "   \n";
        else
          cout << " " << brd[r][c] << " \n";
      }
      else
      {
        if(brd[r][c] == ' ')
          cout << "   |";
        else
          cout << " " << brd[r][c] << " |";
      }
    }

    if(r != 2)
      cout << " |---+---+---\n";
  }
  cout << endl;
}

string board::to_string(const char p) const
{
  string str = "";

  for(unsigned int r = 0; r < 3; r++)
  {
    for(unsigned int c = 0; c < 3; c++)
    {
      if(brd[r][c] == ' ')
        str.push_back('-');
      else if(brd[r][c] == p)
        str.push_back('1');
      else
        str.push_back('0');
    }
  }

  return str;
}

void board::to_board(const string &s, const char p)
{
  const coords crds[] = { coords(0, 0), coords(0, 1), coords(0, 2),
                        coords(1, 0), coords(1, 1), coords(1, 2),
                        coords(2, 0), coords(2, 1), coords(2, 2) };

  for(unsigned int i = 0; i < 9; i++)
  {
    if(s[i] == '-')
      brd[crds[i].get_r()][crds[i].get_c()] = ' ';
    else if(s[i] == '1')
      brd[crds[i].get_r()][crds[i].get_c()] = p;
    else
      brd[crds[i].get_r()][crds[i].get_c()] = swap_player(p);
  }
}
