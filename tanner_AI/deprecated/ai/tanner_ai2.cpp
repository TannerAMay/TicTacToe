#include "tanner_ai2.h"
#include "../../mainGame/funcs.h"

tanner_ai2::tanner_ai2(const char p)
{
  player = p;

  board = buildBoard();
  setBoard(board);

  gentree(player);
  eval();
}

void tanner_ai2::eval()
{
  if(tree.at()->children[0] == nullptr) //no children
  {
    board = stob(tree.at()->boardStr, player);

    if(full(board)) //if the board is full then there is no winning move
      tree.at()->eval = 0;
    else if(solved(board) != 'n') //if there is a winning move, this is it, score it at 100
      tree.at()->eval = 100;

    setBoard(board);

    return;
  }
  else
  {
    //move down, when all children are scored: move up
    for(int i = 0; i < tree.at()->children.size(); i++)
    {
      tree.move(tree.at()->children[i]);
      eval();
      tree.moveUp();
    } //all children have been scored:

    //choose top score
    board = stob(tree.at()->boardStr, player);
    vector<coords> mid = emptyMiddle();
    vector<coords> end = emptyEnd();
    int msz = mid.size();
    int esz = end.size();
    int top = 0;
    for(int i = 0; i < tree.at()->children.size(); i++)
    {
      cerr << "mid: ";
      vPrint(mid);
      cerr << "end: ";
      vPrint(end);

      //If there are moves to block the other player, either mid or end.
      if(msz != 0 || esz != 0)
      {
        cerr << "IN vector size if\n";
        for(int i = 0; i < msz; i++) //mid
        {
          cerr << "msz\n";
          cerr << tree.at()->loc << endl;
          if(mid[i] == tree.at()->loc)
            tree.at()->eval = 99; //not 100 because it should go for the winning move 
                                  //not block its opponent if they are on the same level
        }

        for(int i = 0; i < esz; i++) //end
        {
          cerr << "esz\n";
          cerr << tree.at()->loc << ":" << tree.at()->eval << " " << tree.at()->children.size() << " " << player << endl;
          cerr << "end[i]" << end[i] << endl;
          if(end[i] == tree.at()->loc)
            tree.at()->eval = 99;
          cerr << tree.at()->loc << ":" << tree.at()->eval << " " << tree.at()->children.size() << endl;
        }

        break; //break out of for loop above
      }
      cerr << "msz and esz: " << msz << " " << esz << endl;
      //if the score of the child / its height above solved + 1 is greater than
      //the top scoring node so far / its height above the node + 1
      if(tree.at()->children[i]->eval / (tree.at()->children[i]->heightAboveSolved + 1)
         > tree.at()->children[top]->eval / (tree.at()->children[top]->heightAboveSolved + 1))
      {
        top = i; //make i the new top node
      }
    }

    tree.at()->heightAboveSolved = tree.at()->children[top]->heightAboveSolved + 1; //update this nodes height
    if(msz == 0 && esz == 0) //only update score if there isn't a blocking move
    {
      cerr << "should be 0: " << msz << " " << esz << endl;
      tree.at()->eval = tree.at()->children[top]->eval / tree.at()->heightAboveSolved;
    }
    else
    {
      tree.exp();
      exit(0);
    }
  }
}

void tanner_ai2::gentree(const char player)
{
  if(full(board) || solved(board) != 'n')
    return;

  vector<coords> empt = vEmpty();
  int sz = empt.size();

  for(int i = 0; i < sz; i++)
  {
    board[empt[i].row][empt[i].col] = player;
    tree.addNode(empt[i], -1); //-1 as placeholder until actual eval function
    tree.at()->children.back()->boardStr = btos(board, player);
    tree.move(tree.at()->children.back()); //move curr pointer
    gentree(swapPlayer(player));

    //move everything back
    board[empt[i].row][empt[i].col] = EMPTY;
    tree.moveUp();
  }
}

vector<coords> tanner_ai2::emptyMiddle()
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

vector<coords> tanner_ai2::emptyEnd()
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

vector<coords> tanner_ai2::vEmpty()
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

void tanner_ai2::vPrint(vector<coords> v)
{
  int sz = v.size();

  for(int i = 0; i < sz; i++)
    cerr << v[i] << ", ";

  cerr << endl;
}

void tanner_ai2::play(char ** b, int &playR, int &playC)
{
  if(full(b) || solved(b) != 'n')
    return;

  cerr << "\n\nai player: " << player << endl;

  string bStr;
  bStr = btos(b, swapPlayer(player));

  cerr << "\n\nbtos output: " << bStr << endl;

  if(bStr != "---------")
  {
    //switch to node that matches the current board
    for(int i = 0; i < tree.at()->children.size(); i++)
    {
      cerr << "\n\nBoardStr of node " << i << ": "
           << tree.at()->children[i]->boardStr << endl;

      if(tree.at()->children[i]->boardStr == bStr)
      {
        cerr << "\n\nin if\n";
        tree.move(i);
        break;
      }
    }

    if(tree.at()->boardStr != bStr) //for terminated and didnt find node
      throw "Invalid board set.";
  }

  //select the best move
  int top = -1; //index of child with top score
  for(int i = 1; i < tree.at()->children.size(); i++)
  {
    if(tree.at()->children[top]->eval < tree.at()->children[i]->eval
       && emptySlot(b, tree.at()->children[top]->loc.row, tree.at()->children[top]->loc.col))
      top = i;
  }

  //play best move
  if(top != -1)
  {
    //b[tree.at()->children[top]->loc.row][tree.at()->children[top]->loc.col] = player;
    playR = tree.at()->children[top]->loc.row;
    playC = tree.at()->children[top]->loc.col;
  }
  else
    throw "No valid move found, but also not full or solved.";

  //move tree to the new move
  tree.move(top);
}
