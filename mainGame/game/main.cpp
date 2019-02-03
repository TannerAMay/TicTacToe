#include "play_funcs.h"

/*Files included at this point
 * <iostream>
 * "coords.h"
 * <random>
 * "misc_funcs.h"
 * "board.h"
 * "play_funcs.h"
 */

int main()
{
  board b;
  unsigned short numGames, numPlayers;

  cout << "How many games? ";
  cin >> numGames;

  while(numGames > 0)
  {
    do
    {
      cout << "How many players(0, 1, 2)? ";
      cin >> numPlayers;
    }while(numPlayers > 2);

    cout << endl;

    if(numPlayers == 0)
    {
      char who = '?';

      do
      {
        cout << "Gavin's vs. Tanner's(b); "
             << "Gavin's vs. Gavin's(g); "
             << "Tanner's vs. Tanner's(t)? ";
        cin >> who;
      }while(who != 'b' && who != 'g' && who != 't');

      b.print();

      if(who == 'b')
      {
        if(!play_0b(b))
          cout << "Tie game.\n";
      }
      else if(who == 'g')
      {
        if(!play_0g(b))
          cout << "Tie game.\n";
      }
      else //tanner v tanner
      {
        if(!play_0t(b))
          cout << "Tie game.\n";
      }
    }
    else if(numPlayers == 1)
    {
      char who = '?';

      do
      {
        cout << "You vs. Gavin's(g); "
             << "You vs. Tanner's(t)? ";
        cin >> who;
      }while(who != 'g' && who != 't');

      b.print();

      if(who == 'g')
      {
        if(!play_1g(b))
          cout << "Tie game.\n";
      }
      else //tanner
      {
        if(!play_1t(b))
          cout << "Tie game.\n";
      }
    }
    else
    {
      b.print();

      if(!play_2(b))
        cout << "Tie game.\n";
    }

    b.reset();
    numGames--;
  }

  cout << "Thanks for playing." << endl;

  return 0;
}
