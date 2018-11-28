#ifndef CHEETAHAI_H
#define CHEETAHAI_H

#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

// Needs to be able to update the board on it's turn
// Will return a row and column of where I want to move

class CheetahAI {

  private:
    int myBoard [9]; // Represents all spaces on the board
    vector<int> emptySpaces; // Represents the empty spaces on the board
    int numEmpty; // Number of empty spaces
    char whoami; // Whcih piece I am


    void grnHelper(const char player, int &val);
    // Recursive function called from playGame(). Will determine the value of
    // the given move. Player keeps track of the next player's turn.

    char otherPlayer(const char curr);
    // Returns the other player given the curr

    void updateMyBoard(char ** &board);
    // Update board according to opponent's move
    // Only called from playGame()

    char isSolved();
    // Returns if the board is solved or not
    // 'x', 'o', or 'n' is returned

    int makeAMove(const char player);
    // Makes a move depending on if it is me or the opponent
    // Makes an "optimal" move if it is me
    // Makes a "bad" move it is opponent

  public:
    CheetahAI();

    CheetahAI(const char whoami);

    void playGame(char ** &board, int &pR, int &pC);
};

// When initialized I should only know who I am
CheetahAI::CheetahAI(const char me) {
  whoami = me;
}

// Update my board with opponent's move
void CheetahAI::updateMyBoard(char ** &board) {
  int count = 0;
  myBoard;

  for (int r = 0; r <= 2; r++) {
    for (int c = 0; c <= 2; c++) {
      myBoard[count] = board[r][c];
      if (board[r][c] == ' ') {
        emptySpaces.push_back(count);
      }
      count++;
    }
  }

}

// playGame(board,pR,pC,0,'x') <- x or o depending who i am
// This function gets called from the main loop
// Makes a move based on the current board state aka the emptySpaces
void CheetahAI::playGame(char ** &board, int &pR, int &pC, int &val, const char player) {
  // First
  updateMyBoard(board);

  int currMax;
  int bestSpace; // Represents the best space
  char winner;

  if (emptySpaces.size() == 0) { // The board is full
    return;
  } else {
    currMax = 0;
    for (int i = 0; i < emptySpaces.size(); i++ ) { // i is
      if (player == whoami) { // choosing my move
        val = 0;
        myBoard[emptySpaces[i]] = whoami;
        playGame(board,pR,pC,val,otherPlayer(player)); // Returns the val of choosing this space
        winner = isSolved;
        // assign values here
        myBoard[emptySpaces[i] = ' '];
        if (val > currMax) {
          bestSpace = emptySpaces[i];
        }

      } else {

      }
    }
  }
  // Now I should have the index of the best space in bestSpace
  pC = bestSpace % 3;
  if (bestSpace < 3) {
    pR = 0;
  } else if (bestSpace >= 3 && bestSpace <= 5) {
    pR = 1;
  } else {
    pR = 2;
  }

  //for (int i = 0; i < emptySpaces.size();i++){
  //  cout << emptySpaces[i] << endl;
  //}
  return;
}

// Return the best space to move on given we move somewhere.
// This function will start with placing the enemy, then us
void CheetahAI::grnHelper(const char player, int &val) {
  char winner = isSolved();
  int move;

  if (winner == whoami) { // This is a winning move
    val = 10;
  } else if (winner == otherPlayer(whoami)) { // This is a losing move
    val = -10;
  } else if (winner == 'n') {
    move = makeAMove(player);
    grnHelper(otherPlayer(player),val);
    myBoard[move] = ' '; // undo the move on the out recursion
  }
  return;
}

char CheetahAI::isSolved() {
  char winner = 'n';
  char opt [2] = {'x','o'};

  for (int i = 0; i < 2; i++){
      if (myBoard[0] == opt[i] && myBoard[1] == opt[i] && myBoard[2] == opt[i] ||
          myBoard[3] == opt[i] && myBoard[4] == opt[i] && myBoard[5] == opt[i] ||
          myBoard[6] == opt[i] && myBoard[7] == opt[i] && myBoard[8] == opt[i] ||
          myBoard[0] == opt[i] && myBoard[3] == opt[i] && myBoard[6] == opt[i] ||
          myBoard[1] == opt[i] && myBoard[4] == opt[i] && myBoard[7] == opt[i] ||
          myBoard[2] == opt[i] && myBoard[5] == opt[i] && myBoard[8] == opt[i] ||
          myBoard[0] == opt[i] && myBoard[4] == opt[i] && myBoard[8] == opt[i] ||
          myBoard[2] == opt[i] && myBoard[4] == opt[i] && myBoard[6] == opt[i]) {
            return opt[i];
          }

  }
  return winner;
}

int CheetahAI::makeAMove(const char player) {
  return 1;
}

// Returns the opposite player
char CheetahAI::otherPlayer(const char curr) {
  if (curr == 'x')
    return 'o';
  return 'x';
}


#endif
