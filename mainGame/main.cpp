#include "funcs.h"


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

      int meme;
      cin >> meme;
      if(!play0(board))
      {
        cout << "Tie game\n";

      }

      break;
    case 1:
      board = buildBoard();
      setBoard(board);

      printBoard(board);
      cout << "Here" << endl;
      if(!play1(board))
      {
        cout << "Tie game\n";
      }
      cout << "Out" << endl;

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
