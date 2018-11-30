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
    char myBoard [9]; // Represents all spaces on the board
    vector<int> values;
    //vector<int> emptySpaces; // Represents the empty spaces on the board
    int numEmpty; // Number of empty spaces
    char whoami; // Whcih piece I am


    void grnHelper(const char player, int &pR, int &pC);
    // Recursive function called from playGame(). Will determine the value of
    // the given move. Player keeps track of the next player's turn.

    char otherPlayer(const char curr);
    // Returns the other player given the curr

    void updateMyBoard(char ** &board);
    // Update board according to opponent's move
    // Only called from playGame()

    void updateEmpSpaces(vector<int> &emptySpaces);

    char isSolved();
    // Returns if the board is solved or not
    // 'x', 'o', or 'n' is returned

    int makeAMove(const char player);
    // Makes a move depending on if it is me or the opponent
    // Makes an "optimal" move if it is me
    // Makes a "bad" move it is opponent
    void solveTester();
    void printMyBoard();
    void updateValues();
    void pickSpace(int &pR, int &pC);

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
      count++;
    }
  }
}

void CheetahAI::updateValues() {
  values.clear();
  for (int i = 0; i < 9; i++) {
    values.push_back(0);
  }
  return;
}

// playGame(board,pR,pC,0,'x') <- x or o depending who i am
// This function gets called from the main loop
// Makes a move based on the current board state aka the emptySpaces
void CheetahAI::playGame(char ** &board, int &pR, int &pC) {
  // First
  updateMyBoard(board);
  updateValues();

  int currMax;
  int bestSpace; // Represents the best space
  char winner;
  //solveTester();
  //cin >> val;
  //cout << "Going in" << endl;
  if (myBoard[4] == ' ') {
    pR = 1;
    pC = 1;
  } else {
    grnHelper(whoami,pR,pC); // Update all values
    // Now I should have the index of the best space in bestSpace
    pickSpace(pR,pC);
  }

  //cout << "Coming out ;)" << endl;
  //for (int i = 0; i < emptySpaces.size();i++){
  //  cout << emptySpaces[i] << endl;
  //}
  return;
}

void printArr(vector<int> arr) {
  for (int i = 0; i < arr.size(); i++) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

void printt(char arr[9]) {
  for (int i = 0; i < 9; i++) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

void CheetahAI::printMyBoard() {
  cout << myBoard[0] << " | " << myBoard[1] << " | " << myBoard[2] << endl;
  cout << myBoard[3] << " | " << myBoard[4] << " | " << myBoard[5] << endl;
  cout << myBoard[6] << " | " << myBoard[7] << " | " << myBoard[8] << endl;
}

void CheetahAI::solveTester() {
  myBoard[0] = 'o';
  myBoard[1] = 'o';
  myBoard[2] = 'x';
  myBoard[3] = ' ';
  myBoard[4] = ' ';
  myBoard[5] = 'o';
  myBoard[6] = ' ';
  myBoard[7] = ' ';
  myBoard[8] = 'x';

  cout << isSolved() << endl;
}


// Return the best space to move on given we move somewhere.
// This function will start with placing the enemy, then us
void CheetahAI::grnHelper(const char player, int &pR, int &pC) {
  char winner;
  vector<int> emptySpaces;

  updateEmpSpaces(emptySpaces);

  if (emptySpaces.size() == 0) { // The board is full
    return;
  } else {
    for (int i = 0; i < emptySpaces.size(); i++ ) { // i is index of empSpace in arr
      //printArr(emptySpaces);

      myBoard[emptySpaces[i]] = player; // Choose that space

      winner = isSolved();

      if (winner == whoami || winner == otherPlayer(whoami)) {
        values[emptySpaces[i]] += 1;
        break;
      } else {
        grnHelper(otherPlayer(player),pR,pC);
        //cout << "undo" << endl;
        myBoard[emptySpaces[i]] = ' ';
      }
    }
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

void CheetahAI::updateEmpSpaces(vector<int> &emptySpaces) {
  emptySpaces.clear();
  for (int ind = 0; ind < 9; ind++) {
    if (myBoard[ind] == ' ') {
      emptySpaces.push_back(ind);
    }
  }
}

void CheetahAI::pickSpace(int &pR, int &pC) {
  int bestSpace = 0; // index of best space
  int currMax = 0; // running max

  for (int i = 1; i < 9; i++) {
    if (values[i] > currMax) {
      bestSpace = i;
      currMax = values[i];
    }
  }
  pC = bestSpace % 3;
  if (bestSpace < 3) {
    pR = 0;
  } else if (bestSpace >= 3 && bestSpace <= 5) {
    pR = 1;
  } else {
    pR = 2;
  }
  return;
}

#endif
