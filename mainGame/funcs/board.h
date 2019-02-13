#ifndef BOARD_H
#define BOARD_H

#include "../../tanner_AI/multitree/coords.h"
#include "misc_funcs.h"

/*Files included so far:
 * <iostream>
 * "coords.h"
 * <random>
 * "misc_funcs.h"
 */

using std::string;

class board
{
private:
  char ** brd = nullptr;

public:
  board();
  ~board();

  //makes all locations in brd ' '
  //brd MUST be allocated, throws string if not
  void reset();

  //checks if there are any ' ' left
  bool full() const;
  //checks if all spaces are ' '
  bool empty() const;

  //checks (1, 0), (1, 1), (1, 2)
  //       (0, 1), (2, 1)
  //returns 'x', 'o', or 'n'; players or no-win state
  char solved() const;

  //places player at (r, c) if it is ' '
  //if it is not empty it throws string
  void place(const unsigned short r, const unsigned short c, const char player);

  //returns the char at (r, c)
  char at(const unsigned short r, const unsigned short c) const;

  void print() const;

  //convert brd to a string
  string to_string(const char p) const;

  //converts a string to brd
  void to_board(const string &s, const char p);
};

#endif // BOARD_H
