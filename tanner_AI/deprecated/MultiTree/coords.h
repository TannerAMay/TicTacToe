#ifndef COORDS_H
#define COORDS_H

#include <iostream>

using std::ostream;

struct coords
{
  int row;
  int col;

  inline coords(int r,  int c) {row = r; col = c;}
  inline coords() {row = 0; col = 0;}

  inline bool operator==(const coords &rs){ return row == rs.row && col == rs.col; }

  friend ostream & operator<<(ostream &os, const coords &c)
  {
    return os << "(" << c.row << ", " << c.col << ")";
  }
};

#endif // COORDS_H
