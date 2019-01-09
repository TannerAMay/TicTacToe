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

char solved(char ** &board)
{
  int rDir[]{-1, -1, 0, 1, 1, 1, 0, -1};
  int cDir[]{0, 1, 1, 1, 0, -1, -1, -1};

  int rOgStep, cOgStep, rStep, cStep;
  char players [2] = {'x','o'};

  for (int i = 0; i < 2; i++) {

    for(int r = 0; r < 3; r++)
    {
      for(int c = 0; c < 3; c++)
      {
        rOgStep = r;
        cOgStep = c;

        if(board[r][c] == players[i])
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
                  if(board[rStep][cStep] == players[i])
                  {
                    if(l == 2)
                    {
                      return players[i];
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
    }

  return 'n';
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

  if(solved(board))
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
  const char AI_PLAYER = randPlayer();

  char player = 'x'; // Who starts
  int pR, pC;
  char winner;

  CheetahAI gav(AI_PLAYER); // Initialize me with who I am
  cout << "Game start" << endl;

  do {
    if (player == AI_PLAYER) { // AI
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

    board[pR][pC] = player; // Update board
    player = swapPlayer(player); // Swap players
    winner = solved(board);
  } while (winner == 'n' && !full(board));

  cout << endl;

  printBoard(board);

  if (winner != 'n') {
    cout << "Player " << winner << " has won!" << endl;
    return 1;
  } else {
    return 0; // Tie is handled in main
  }

  //throw "Something terrible has happened.";
}

bool play0(char ** &board)
{
  static map<int, int> choice;
  const char CHEETAH = 'x';
  const char TANNER = 'o';

  char player = randPlayer();
  int pR, pC;
  char winner;

  CheetahAI gav(CHEETAH);

  cout << "Game start" << endl;

  do {
    if (player == CHEETAH) { // Cheetah
      cout << "Cheetah's turn" << endl;
      do {
        gav.playGame(board,pR,pC);
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    } else { // Tanner
      do {
        // Tanner's function
        cout << "Placeholder" << endl;
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    }

    board[pR][pC] = player; // Update board
    player = swapPlayer(player); // Swap players
    winner = solved(board);
  } while (winner == 'n' && !full(board));

  printBoard(board);

  if(winner != 'n')
  {
    cout << "Player " << player << " has won!\n";
    //tannerAI(board, pR, pC, 1, choice);
    return 1;
  }

  //throw "Something terrible has happened.";
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
