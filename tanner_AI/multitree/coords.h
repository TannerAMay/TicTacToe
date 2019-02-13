#ifndef COORDS_H
#define COORDS_H

#include <iostream>

using std::ostream;
using std::cout;
using std::endl;
using std::cerr;

class coords
{
private:
  unsigned int r;
  unsigned int c;

public:
  inline coords() { r = 100; c = 100; } //obviously incorrect for TicTacToe
  inline coords(const unsigned int row, const unsigned int col){ r = row; c = col; }

  unsigned int get_r() const { return r; }
  unsigned int get_c() const { return c; }

  void set_r(const unsigned int row) { r = row; }
  void set_c(const unsigned int col) { c = col; }

  inline bool operator==(const coords &rs) const { return r == rs.r && c == rs.c; }
  inline void operator=(const coords &rs) { r = rs.r; c = rs.c; }

  friend ostream & operator<<(ostream &os, const coords &out)
  {
    return os << "(" << out.r << ", " << out.c << ")";
  }

};

#endif // COORDS_H
