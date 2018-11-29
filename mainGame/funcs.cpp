#include "funcs.h"
#include "cheetahAI.h"
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
  for(int r = 0; r < 3; r++)
  {
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
      cout << "---+---+---\n";
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

bool solved(char ** &board, char player)
{
  //if (board[0][0] == player && board[0][1] == player && board[0][2] == player ||
  //    board[1][0] == player && board[1][1] == player && board[1][2] == player ||
  //    board[2][0] == player && board[2][1] == player && board[2][2] == player ||
  //    board[0][0] == player && board[1][0] == player && board[2][0] == player ||
  //    board[0][1] == player && board[1][1] == player && board[2][1] == player ||
  //    board[0][2] == player && board[1][2] == player && board[2][2] == player ||
  //    board[0][0] == player && board[1][1] == player && board[2][2] == player ||
  //    board[0][2] == player && board[1][1] == player && board[2][0] == player) {
  //      return true;
  //    }
  //return false;
  int rDir[]{-1, -1, 0, 1, 1, 1, 0, -1};
  int cDir[]{0, 1, 1, 1, 0, -1, -1, -1};

  int rOgStep, cOgStep, rStep, cStep;

  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      rOgStep = r;
      cOgStep = c;

      if(board[r][c] == player)
      {
        for(int d = 0; d < 8; d++)
        {
          for(int l = 1; l < 3; l++)
          {
            rStep = rOgStep + rDir[d];
            cStep = cOgStep + cDir[d];

            if(rStep < 3 && rStep > -1
               && cStep < 3 && cStep > -1)
            {
              if(board[rStep][cStep] == player)
              {
                if(l == 2)
                {
                  return 1;
                }
                else if(l < 2)
                {
                  rOgStep = rStep;
                  cOgStep = cStep;
                }
              }
              else
              {
                l = 3;
                rOgStep = r;
                cOgStep = c;
              }
            }
            else
            {
              l = 3;
              rOgStep = r;
              cOgStep = c;
            }
          }
        }
      }
    }
  }

  return 0;
}

bool emptySlot(char ** &board, int r, int c)
{
  return board[r][c] == ' ';
}

char swapPlayer(const char player) {
  if (player == 'x')
    return 'o';
  return 'x';
}

bool play2(char ** &board, char player)
{
  if(full(board))
    return 0;

  int pR, pC;

  if(player == 'x')
  {
    do
    {
      cout << "\nPlayer " << player << "'s turn\n";
      cout << "r: ";
      cin >> pR;
      cout << "c: ";
      cin >>pC;
    }while((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));

    board[pR][pC] = 'x';
  }
  else
  {
    do
    {
      cout << "\nPlayer " << player << "'s turn\n";
      cout << "r: ";
      cin >> pR;
      cout << "c: ";
      cin >>pC;
    }while((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));

    board[pR][pC] = 'o';
  }

  cout << endl;

  printBoard(board);

  if(solved(board, player))
  {
    cout << "Player " << player << " has won!\n";
    return 1;
  }

  if(player == 'x')
    return play2(board, 'o');
  else
    return play2(board, 'x');

  throw "Something terrible has happened.";
}

bool play1(char ** &board)
{
  static map<int, int> choice;
  const char AI_PLAYER = 'x';

  char player = 'x'; // Who starts
  int pR, pC;
  int dumpster = 0; // Cause im dumb
  CheetahAI gav(AI_PLAYER); // Initialize me with who I am
  cout << "Game start" << endl;
  do {

    if (player == AI_PLAYER) {
      cout << "AI turn" << endl;
      do {
        gav.playGame(board,pR,pC);
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    } else { // Human
      do {
        printBoard(board);
        cout << "\nIt's your turn\n";
        cout << "r: ";
        cin >> pR;
        cout << "c: ";
        cin >>pC;
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    }

    board[pR][pC] = player;
    player = swapPlayer(player);
  } while (!solved(board, player) || !full(board));

  cout << endl;

  printBoard(board);

  if (solved(board, player)) {
    cout << "Player " << player << " has won!" << endl;
    return 1;
  } else {
    return 0; // Tie is handled in main
  }

  //throw "Something terrible has happened.";
}

bool play0(char ** &board, char player)
{
  static map<int, int> choice;

  if(full(board))
  {
    //tannerAI(board, pR, pC, 1, choice);
    return 0;
  }

  int pR, pC;

  if(player == 'x')
  {
    do
    {
      pR = 0;
      pC = 0;
      //tannerAI(board, pR, pC, 0, choice);
    }while((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));

    board[pR][pC] = 'x';
  }
  else
  {
    do
    {
      pR = 0;
      pC = 0;
      //gavinAI(board, pR, pC);
    }while((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));

    board[pR][pC] = 'o';
  }

  printBoard(board);

  if(solved(board, player))
  {
    cout << "Player " << player << " has won!\n";
    //tannerAI(board, pR, pC, 1, choice);
    return 1;
  }

  if(player == 'x')
    return play0(board, 'o');
  else
    return play0(board, 'x');

  throw "Something terrible has happened.";
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

/*void tannerAI(char const* const* const &board, int &pR, int &pC,
              bool nGame, map<int, int> &choice)
{
  if(nGame)
  {
    choice.clear();
    return;
  }




  return;
}*/

void treeMaker(char const* const* const &board)
{


  return;
}

/*void gavinAI(char const* const* const &board, int &pR, int &pC)
{
  return;
}*/
