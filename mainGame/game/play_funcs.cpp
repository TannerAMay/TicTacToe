#include "play_funcs.h"

bool play_2(board &b)
{
  //if the board isn't empty just quit
  if(!b.empty())
    return false;

  char player = rand_player();

  cout << player << " goes first.\n";

  char solvedVar = '?';
  unsigned int row, col;

  do
  {
    cout << "\n==================================\n";
    //bring in (r, c)
    cout << "\nIt is " << player << "'s turn.\n";
    cout << "Row: ";
    cin >> row;
    cout << "Column: ";
    cin >> col;

    //try to place it there, b.place() handles out of bounds and stuff
    try
    {
      b.place(row, col, player);
    }
    catch(char const *)
    {
      cout << "Invalid placement. Try again.\n";
      continue; //skip checking for solved and swapping characters
    }

    b.print();

    //print, see if it's solved, swap the player in prep for next turn
    solvedVar = b.solved();
    player = swap_player(player);
  }while(!b.full() && (solvedVar == 'n' || solvedVar == '?'));

  if(solvedVar != 'n')
  {
    cout << solvedVar << " has won!\n";
    return 1;
  }

  //board is full, handled in main
  return 0;
}

bool play_1g(board &b)
{
  const char HUMAN = rand_player();
  const char AI = swap_player(HUMAN);
  unsigned short row, col;
  char solvedVar = '?';
  char currTurn = rand_player(); //who goes first

  cout << "You are " << HUMAN << endl;

  //GAVIN'S UPDATED AI INIT GOES HERE

  if(currTurn == HUMAN)
    cout << HUMAN << ", you, go first.\n";
  else
    cout << AI << ", Gavin's AI, goes first.\n";

  do
  {
    cout << "\n==================================\n";
    if(currTurn == HUMAN)
    {
      cout << "It is your turn.\n";
      cout << "Row: ";
      cin >> row;
      cout << "Column: ";
      cin >> col;

      try
      {
        b.place(row, col, HUMAN);
      }
      catch(char const *)
      {
        cout << "Invalid placement. Try again.\n";
        continue;
      }
    }
    else
    {
      cout << "AI's turn.\n";
      //GAVIN PLAY GAME, use same try, catch as above
    }

    b.print();
    solvedVar = b.solved();
    currTurn = swap_player(currTurn);
  }while(!b.full() && (solvedVar == 'n' || solvedVar == '?'));

  if(solvedVar == AI)
  {
    cout << AI << ", Gavin's AI, wins!\n";
    return 1;
  }
  else if(solvedVar == HUMAN)
  {
    cout << HUMAN << ", you, win!";
    return 1;
  }

  //tie handling in main
  return 0;
}

bool play_1t(board &b)
{
  const char HUMAN = rand_player();
  const char AI = swap_player(HUMAN);
  unsigned short row, col;
  char solvedVar = '?';
  char currTurn = rand_player(); //who goes first

  cout << "You are " << HUMAN << endl;

  if(currTurn == HUMAN)
    cout << HUMAN << ", you, go first.\n";
  else
    cout << AI << ", Tanner's AI, goes first.\n";

  //TANNER'S UPDATED AI INIT GOES HERE

  do
  {
    cout << "\n==================================\n";
    if(currTurn == HUMAN)
    {
      cout << "It is your turn.\n";
      cout << "Row: ";
      cin >> row;
      cout << "Column: ";
      cin >> col;

      try
      {
        b.place(row, col, HUMAN);
      }
      catch(char const *)
      {
        cout << "Invalid placement. Try again.\n";
        continue;
      }
    }
    else
    {
      cout << "AI's turn.\n";
      //TANNER PLAY GAME, use same try, catch as above
    }

    b.print();
    solvedVar = b.solved();
    currTurn = swap_player(currTurn);
  }while(!b.full() && (solvedVar == 'n' || solvedVar == '?'));

  if(solvedVar == AI)
  {
    cout << AI << ", Tanner's AI, wins!\n";
    return 1;
  }
  else if(solvedVar == HUMAN)
  {
    cout << HUMAN << ", you, win!";
    return 1;
  }

  //tie handling in main
  return 0;
}

bool play_0b(board &b)
{
  const char GAVIN_AI = rand_player();
  const char TANNER_AI = swap_player(GAVIN_AI);
  char currTurn = rand_player();
  char solvedVar = '?';

  if(currTurn == GAVIN_AI)
    cout << GAVIN_AI << ", Gavin's AI, goes first.\n";
  else
    cout << TANNER_AI << ", Tanner's AI, goes first.\n";

  //AI INITS GO HERE

  do
  {
    cout << "\n==================================\n";
    if(currTurn == GAVIN_AI)
    {
      //gavin play
    }
    else
    {
      //tanner play
    }

    b.print();
    solvedVar = b.solved();
    currTurn = swap_player(currTurn);
  }while(!b.full() && (solvedVar == 'n' || solvedVar == '?'));

  if(solvedVar == GAVIN_AI)
  {
    cout << GAVIN_AI << ", Gavin's AI, wins!\n";
    return 1;
  }
  else if(solvedVar == TANNER_AI)
  {
    cout << TANNER_AI << ", Tanner's AI, wins!\n";
    return 1;
  }

  return 0;
}

bool play_0g(board &b)
{
  const char GAVIN_AI_1 = rand_player();
  const char GAVIN_AI_2 = swap_player(GAVIN_AI_1);
  char currTurn = rand_player();
  char solvedVar = '?';

  if(currTurn == GAVIN_AI_1)
    cout << GAVIN_AI_1 << ", Gavin's AI #1, goes first.\n";
  else
    cout << GAVIN_AI_2 << ", Gavin's AI #2, goes first.\n";

  //AI INITS GO HERE

  do
  {
    cout << "\n==================================\n";
    if(currTurn == GAVIN_AI_1)
    {
      //gavin1 play
    }
    else
    {
      //gavin2 play
    }

    b.print();
    solvedVar = b.solved();
    currTurn = swap_player(currTurn);
  }while(!b.full() && (solvedVar == 'n' || solvedVar == '?'));

  if(solvedVar == GAVIN_AI_1)
  {
    cout << GAVIN_AI_1 << ", Gavin's AI #1, wins!\n";
    return 1;
  }
  else if(solvedVar == GAVIN_AI_2)
  {
    cout << GAVIN_AI_2 << ", Gavin's AI #2, wins!\n";
    return 1;
  }

  return 0;
}

bool play_0t(board &b)
{
  const char TANNER_AI_1 = rand_player();
  const char TANNER_AI_2 = swap_player(TANNER_AI_1);
  char currTurn = rand_player();
  char solvedVar = '?';

  if(currTurn == TANNER_AI_1)
    cout << TANNER_AI_1 << ", Tanner's AI #1, goes first.\n";
  else
    cout << TANNER_AI_2 << ", Tanner's AI #2, goes first.\n";

  //AI INITS GO HERE

  do
  {
    cout << "\n==================================\n";
    if(currTurn == TANNER_AI_1)
    {
      //tanner1 play
    }
    else
    {
      //tanner2 play
    }

    b.print();
    solvedVar = b.solved();
    currTurn = swap_player(currTurn);
  }while(!b.full() && (solvedVar == 'n' || solvedVar == '?'));

  if(solvedVar == TANNER_AI_1)
  {
    cout << TANNER_AI_1 << ", Gavin's AI #1, wins!\n";
    return 1;
  }
  else if(solvedVar == TANNER_AI_2)
  {
    cout << TANNER_AI_2 << ", Gavin's AI #2, wins!\n";
    return 1;
  }

  return 0;
}
