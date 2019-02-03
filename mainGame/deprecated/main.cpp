#include "play_funcs.h"
#include <exception>

using std::exception;

int main()
{
  char **board = nullptr;
  int gNum, pNum;

  do
  {
    cout << "How many games? ";
    cin >> gNum;
  }while(gNum < 0);

  while(gNum > 0)
  {
    do
    {
      cout << "How many players? ";
      cin >> pNum;
    }while(pNum < 0 || pNum > 2);

    cout << endl;

    switch(pNum)
    {
    case 0:
      board = buildBoard();
      setBoard(board);

      printBoard(board);

//      int meme;
//      cin >> meme;
      if(!play0(board))
        cout << "Tie game\n";

      break;
    case 1:
      try
      {
        board = buildBoard();
        setBoard(board);

        char aiPlayer;
        do
        {
          cout << "Which AI player('g' for Gavin's, 't' for Tanner's)? ";
          cin >> aiPlayer;
        }while(aiPlayer != 'g' && aiPlayer != 't');

        printBoard(board);

        if(aiPlayer == 'g')
        {
          if(!g_play1(board))
            cout << "Tie game\n";
        }
        else //aiPlayer == 't'
        {
          if(!t_play1(board))
            cout << "Tie game\n";
        }
      }
      catch(char const *e)
      {
        cout << e << endl;
      }


      break;
    case 2:
      board = buildBoard();
      setBoard(board);

      printBoard(board);

      if(!play2(board, randPlayer()))
        cout << "Tie game\n";
      break;
    }

    deleteBoard(board);
    gNum--;
  }


  return 0;
}
