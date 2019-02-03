#include "play_funcs.h"
#include "cheetahAI.h"
#include "../tanner_AI/ai/tanner_ai2.h"

bool play2(char ** board, char player)
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

  if(solved(board) != 'n')
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

bool g_play1(char ** board)
{
  const char AI_PLAYER = randPlayer();

  char player = 'x'; // Who starts
  int pR, pC;
  char winner;

  CheetahAI gav(AI_PLAYER); // Initialize me with who I am

  do {
    if (player == AI_PLAYER) { // AI
      cout << "AI turn:" << endl;
      do {

        gav.playGame(board,pR,pC);
        //printBoard(board);
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    } else { // Human
      do {
        //printBoard(board);
        cout << "\nIt's your turn\n";
        cout << "r: ";
        cin >> pR;
        cout << "c: ";
        cin >>pC;
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    }

    board[pR][pC] = player; // Update board

    printBoard(board);

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
}

bool t_play1(char ** board)
{
  const char AI_PLAYER = randPlayer();

  char player = 'x'; // Who starts
  int pR, pC;
  char winner;

  tanner_ai2 tan(AI_PLAYER); // Initialize me with who I am

  do {
    if (player == AI_PLAYER) { // AI
      cout << "AI turn:" << endl;
      do {
        tan.play(board, pR, pC);
        //printBoard(board);
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    } else { // Human
      do {
        //printBoard(board);
        cout << "\nIt's your turn\n";
        cout << "r: ";
        cin >> pR;
        cout << "c: ";
        cin >>pC;
      } while ((pR < 0 || pR > 2 || pC < 0 || pC > 2) || !emptySlot(board, pR, pC));
    }

    board[pR][pC] = player; // Update board

    printBoard(board);

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
}

bool play0(char ** board)
{
  const char CHEETAH = 'x';
  const char TANNER = 'o';

  char player = randPlayer();
  int pR, pC;
  char winner;

  CheetahAI gav(CHEETAH);

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
}
