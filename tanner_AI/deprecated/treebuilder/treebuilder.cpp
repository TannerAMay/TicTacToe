#include "../MultiTree/multitree.h"
#include "../../mainGame/funcs.h"


/*
 * This program is independent of the game.
 * Its purpose is to create the MultiTree of all the possible moves then gives move
 * a score based on its probability to win.
 * The MultiTree will then be exported to a file so that the massive tree does not
 * have to be generated everytime the game is run. *
 */

//formula: emptyEnd/emptyMiddle dividedby number of moves until end

//goes from bottom up applying formula to each node
void eval(MultiTree &tree, char ** board, const char player);//cnt must =0 on call
//builds the tree, does not assign evals
void gentree(MultiTree &tree, char ** board, const char player);

vector<coords> emptyMiddle(char ** board, const char player);
vector<coords> emptyEnd(char ** board, const char player);
vector<coords> vEmpty(char ** board);
void vPrint(vector<coords> v);

const char EMPTY = ' ';
const char o = 'o';
const char x = 'x';

int main()
{
  char **board = buildBoard();
  setBoard(board);

  /*board[0][0] = x;
  board[0][2] = x;
  board[2][2] = x;
  board[2][0] = x;

  vector<coords> tmp = emptyMiddle(board, x);

  vPrint(tmp);

  setBoard(board);

  board[0][0] = x;
  board[1][0] = x;
  board[2][0] = x;
  board[1][1] = x;
  board[0][1] = x;
  board[0][2] = x;

  tmp = emptyEnd(board, x);

  vPrint(tmp);

  cout << "\n\nGENTREE:\n";
  setBoard(board);*/
  MultiTree t0;
  //cout << "empty:\n";
  //t0.print();
  gentree(t0, board, x);
  //cout << "\ndone:\n";
  //t0.print();
  //cout << "\nexp:\n";
  //t0.exp();
  //cout << endl;

  //cout << "\n\n\n\n";

  //cout << "\neval:\n";
  eval(t0, board, x);
  t0.print();

  //t0.print();

  t0.exp();
}

void eval(MultiTree &tree, char ** board, const char player)
{
  /*static int iter = 1;
  cerr << "eval: " << iter << endl;
  iter++;*/

  if(tree.at()->children[0] == nullptr) //no children
  {
    board = stob(tree.at()->boardStr, player);

    if(full(board)) //if the board is full then there is no winning move
    {
      tree.at()->eval = 0;
    }
    else if(solved(board) != 'n') //if there is a winning move, this is it, score it at 100
    {
      tree.at()->eval = 100;
    }

    setBoard(board);

    return;
  }
  else
  {
    //move down, when all children are scored: move up
    for(int i = 0; i < tree.at()->children.size(); i++)
    {
      tree.move(tree.at()->children[i]);
      eval(tree, board, player);//, cnt);
      tree.moveUp();
    } //all children have been scored:

    //choose top score
    int top = 0;
    for(int i = 0; i < tree.at()->children.size(); i++)
    {
      //if the score of the child / its height above solved + 1 is greater than
      //the top scoring nod so far / its height above the node + 1
      if(tree.at()->children[i]->eval / (tree.at()->children[i]->heightAboveSolved + 1)
         > tree.at()->children[top]->eval / (tree.at()->children[top]->heightAboveSolved + 1))
      {
        top = i; //make i the new top node
        //tree.at()->heightAboveSolved = tree.at()->children[i]->heightAboveSolved + 1; //update this nodes height
      }
      //float tmp = tree.at()->children[i]->eval / tree.at()->children[top]->heightAboveSolved;
    }

    tree.at()->heightAboveSolved = tree.at()->children[top]->heightAboveSolved + 1; //update this nodes height
    tree.at()->eval = tree.at()->children[top]->eval / tree.at()->heightAboveSolved;
  }
}

void gentree(MultiTree &tree, char ** board, const char player)
{
  /*static int iter = 1;
  cerr << "still goin: " << iter << "\n";
  iter++;
  cerr << btos(board, player) << endl;
  cout << "\n\n\n\n";
  tree.print();
  cout << "\n\n\n\n";*/

  if(full(board) || solved(board) != 'n')
    return;

  vector<coords> empt = vEmpty(board);
  int sz = empt.size();

  for(int i = 0; i < sz; i++)
  {
    board[empt[i].row][empt[i].col] = player;
    tree.addNode(empt[i], -1); //-1 as placeholder until actual eval function
    tree.at()->children.back()->boardStr = btos(board, player);
    tree.move(tree.at()->children.back()); //move curr pointer
    //tree.at()->boardStr = btos(board, player);
    gentree(tree, board, swapPlayer(player));

    //move everything back
    board[empt[i].row][empt[i].col] = EMPTY;
    tree.moveUp();
  }
}

vector<coords> emptyMiddle(char ** board, const char player)
{
  vector<coords> tmp;

  if(emptyBoard(board))
    return tmp;

  if(emptySlot(board, 1, 1)) //if the middle is not empty skip all checks that require middle
  {
    if(at(board, 0, 0) == player && at(board, 2, 2) == player) //top left, bottom right
      tmp.push_back(coords(1, 1));

    if(at(board, 0, 1) == player && at(board, 2, 1) == player) //top mid, bottom mid
      tmp.push_back(coords(1, 1));

    if(at(board, 1, 0) == player && at(board, 1, 2) == player) //mid left, mid right
      tmp.push_back(coords(1, 1));

    if(at(board, 2, 0) == player && at(board, 0, 2) == player) //bottom left, top right
      tmp.push_back(coords(1, 1));
  }

  if(at(board, 0, 0) == player && at(board, 0, 2) == player
     && emptySlot(board, 0, 1)) //top left, top right
    tmp.push_back(coords(0, 1));

  if(at(board, 0, 0) == player && at(board, 2, 0) == player
     && emptySlot(board, 1, 0)) //top left, bottom left
    tmp.push_back(coords(1, 0));

  if(at(board, 0, 2) == player && at(board, 2, 2) == player
     && emptySlot(board, 1, 2)) //top right, bottom right
    tmp.push_back(coords(1, 2));

  if(at(board, 2, 0) == player && at(board, 2, 2) == player
     && emptySlot(board, 2, 1)) //bottom left, bottom right
    tmp.push_back(coords(2, 1));

  return tmp;
}

vector<coords> emptyEnd(char ** board, const char player)
{
  vector<coords> tmp;

  if(emptySlot(board, 0, 0)) //top left is empty
  {
    if((at(board, 1, 1) == player && at(board, 2, 2) == player) //diagonal
       || (at(board, 0, 2) == player && at(board, 0, 1) == player) //horizontal
       || (at(board, 2, 0) == player && at(board, 1, 0) == player)) //vertical
      tmp.push_back(coords(0, 0));
  }

  if(emptySlot(board, 0, 2)) //top right empty
  {
    if((at(board, 2, 0) == player && at(board, 1, 1) == player) //d
       || (at(board, 0, 0) == player && at(board, 0, 1) == player) //h
       || (at(board, 2, 2) == player && at(board, 1, 2) == player)) //v
      tmp.push_back(coords(0, 2));
  }

  if(emptySlot(board, 2, 0)) //bottom left empty
  {
    if((at(board, 0, 2) == player && at(board, 1, 1) == player) //d
       || (at(board, 2, 2) == player && at(board, 2, 1) == player) //h
       || (at(board, 0, 0) == player && at(board, 1, 0) == player)) //v
      tmp.push_back(coords(2, 0));
  }

  if(emptySlot(board, 2, 2)) //bottom right empty
  {
    if((at(board, 0, 0) == player && at(board, 1, 1) == player) //d
       || (at(board, 2, 0) == player && at(board, 2, 1) == player) //h
       || (at(board, 0, 2) == player && at(board, 1, 2) == player)) //v
      tmp.push_back(coords(2, 2));
  }

  if(at(board, 1, 1) == player)
  {
    if(emptySlot(board, 0, 1) && at(board, 2, 1) == player) //v, empty above
      tmp.push_back(coords(0, 1));

    if(emptySlot(board, 2, 1) && at(board, 0, 1) == player) //v, empty below
      tmp.push_back(coords(2, 1));

    if(emptySlot(board, 1, 2) && at(board, 1, 0) == player) //h, empty right
      tmp.push_back(coords(1, 2));

    if(emptySlot(board, 1, 0) && at(board, 1, 2) == player) //h, empty left
      tmp.push_back(coords(1, 0));
  }

  return tmp;
}

vector<coords> vEmpty(char ** board)
{
  vector<coords> tmp;

  for(int r = 0; r < 3; r++)
  {
    for(int c = 0; c < 3; c++)
    {
      if(board[r][c] == EMPTY)
        tmp.push_back(coords(r, c));
    }
  }

  return tmp;
}

void vPrint(vector<coords> v)
{
  int sz = v.size();

  for(int i = 0; i < sz; i++)
  {
    cout << v[i] << ", ";
  }

  cout << endl;
}

