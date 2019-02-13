#include "tannerai.h"

void tannerAi::gen_tree_r(board &b, const char p)
{
  if(b.full() || b.solved() != 'n')
    return;

  vector<coords> vEmpty = find_empty(b);
  unsigned short sz = vEmpty.size();

  for(unsigned short i = 0; i < sz; i++)
  {
    b.place(vEmpty[i].get_r(), vEmpty[i].get_c(), swap_player(tree->get_curr_player()));
    tree->add_node(vEmpty[i], swap_player(tree->get_curr_player())); //leave score to placeholder function
    tree->move(tree->get_curr_numChildren() - 1); //move to end of children array
    tree->set_curr_boardStr(b.to_string(player));
    gen_tree_r(b, tree->get_curr_player());

    //move everything back
    b.place(vEmpty[i].get_r(), vEmpty[i].get_c(), ' ');
    tree->move_up();
  }
}

void tannerAi::eval_tree_r()//board &b)// uncomment this for testing
{
  //comment this and if out for testing
  board b;

  if(tree->get_curr_boardStr() == "nochange")
    b.reset();
  else
    b.to_board(tree->get_curr_boardStr(), player); //to here

  const char solvedChar = b.solved();
  const bool fullState = b.full();

  vector<coords> midSwap = mid_empty(b, swap_player(player));
  vector<coords> endSwap = end_empty(b, swap_player(player));
  bool midSwapPresent = (midSwap.size() > 0) ? true : false;
  bool endSwapPresent = (endSwap.size() > 0) ? true : false;

  //board is full or winning condition
  if(fullState || solvedChar != 'n')
  {
    if(solvedChar == player) //I won so set score to 100
    {
      tree->set_curr_score(100); //increment height above solved for parent node with ++before
      tree->set_curr_win(true); //makes for easier calculations later
    }
    else
      tree->set_curr_score(0); //full/loss

    return;
  }
  else if(midSwapPresent || endSwapPresent)
  {
    //look for the child that is able to block opponent, set its score to 99
    //set height after recursion is done

    //move to first node in child array
    tree->move(0);
    if(tree->get_curr_player() == player)
    {
      //reverse the move down above
      tree->move_up();
      //find the blocking move
      find_block(endSwap, midSwap);
    }
    else
    {
      tree->move_up();

      //for each node in children, run the find block function
      //this is needed because of how the tree works when the AI goes 2nd
      for(unsigned short i = 0; i < tree->get_curr_numChildren(); i++)
      {
        tree->move(i);
        find_block(endSwap, midSwap);
        tree->move_up();
      }
    }

    //the recursion part
    //vector<coords> empt = find_empty(b); //t uncomment for testing
    for(unsigned short i = 0; i < tree->get_curr_numChildren(); i++)
    {
      //b.place(empt[i].get_r(), empt[i].get_c(), (empt.size() % 2 == 0) ? 'x' : 'o'); //t uncomment for testing
      //b.print(); //uncomment for testing
      tree->move(i);
      eval_tree_r(); //b); //uncomment for testing
      tree->move_up();
      //b.print(); //uncomment for testing
      //b.place(empt[i].get_r(), empt[i].get_c(), EMPTY); //t uncomment for testing
    }

    //now set the height of the children with score of 99
    for(unsigned short i = 0; i < tree->get_curr_numChildren(); i++)
    {
      tree->move(i);
      if(tree->get_curr_score() == 99)
      {
        tree->move(tree->get_curr_top_score());

        const unsigned short tmpHeight = tree->get_curr_height();
        tree->move_up();
        tree->set_curr_height(tmpHeight);
      }

      tree->move_up();
    }

    return;
  }
  else
  {
    //generate scores for children recursively
    //vector<coords> empt = find_empty(b); //t uncomment for testing
    for(unsigned short i = 0; i < tree->get_curr_numChildren(); i++)
    {
      //b.place(empt[i].get_r(), empt[i].get_c(), (empt.size() % 2 == 0) ? 'x' : 'o'); //t uncomment for testing
      tree->move(i);
      eval_tree_r();//b); //uncomment for testing
      tree->move_up();
      //b.place(empt[i].get_r(), empt[i].get_c(), EMPTY); //t uncomment for testing
    }

    //here->return: setting the score and the height
    tree->move(tree->get_curr_top_score());

    const unsigned int tmpHeight = tree->get_curr_height(); //these are the top scoring node's
    const bool tmpWin = tree->get_curr_win();

    tree->move_up();
    tree->set_curr_height(tmpHeight + 1);

    //get top score, divide it by child nodes height + 1
    if(tmpWin) //if the top scoring node is a win
    {
      tree->set_curr_score(100 / tree->get_curr_height());
      tree->set_curr_win(true);
    }
    //else no change in score because it's default is 0

    return;
  }
}

void tannerAi::find_block(const vector<coords> &endSwap, const vector<coords> &midSwap)
{
  for(unsigned int i = 0; i < tree->get_curr_numChildren(); i++)
  {
    tree->move(i);

    //check for i in midswap
    for(unsigned short k = 0; k < midSwap.size(); k++)
    {
      //if found
      if(tree->get_curr_loc() == midSwap[k])
      {
        //set score to 99
        tree->set_curr_score(99);
        //stop searching
        break;
      }
    }

    //check for i in endswap
    for(unsigned short k = 0; k < endSwap.size(); k++)
    {
      //if found
      if(tree->get_curr_loc() == endSwap[k])
      {
        //set score to 99
        tree->set_curr_score(99);
        //stop searching
        break;
      }
    }

    tree->move_up();
  }
}

vector<coords> tannerAi::find_empty(const board &b) const
{
  vector<coords> tmp;

  for(unsigned short r = 0; r < 3; r++)
  {
    for(unsigned short c = 0; c < 3; c++)
      if(b.at(r, c) == ' ')
        tmp.push_back(coords(r, c));
  }

  return tmp;
}

vector<coords> tannerAi::mid_empty(const board &b, const char p) const
{
  vector<coords> tmp;

  if(b.empty())
    return tmp;

  if(b.at(1, 1) != p) //if the middle is not p skip all checks that require middle
  {
    if(b.at(0, 0) == p && b.at(2, 2) == p) //top left, bottom right
      tmp.push_back(coords(1, 1));

    if(b.at(0, 1) == p && b.at(2, 1) == p) //top mid, bottom mid
      tmp.push_back(coords(1, 1));

    if(b.at(1, 0) == p && b.at(1, 2) == p) //mid left, mid right
      tmp.push_back(coords(1, 1));

    if(b.at(2, 0) == p && b.at(0, 2) == p) //bottom left, top right
      tmp.push_back(coords(1, 1));
  }

  if(b.at(0, 0) == p && b.at(0, 2) == p
     && b.at(0, 1) == EMPTY) //top left, top right
    tmp.push_back(coords(0, 1));

  if(b.at(0, 0) == p && b.at(2, 0) == p
     && b.at(1, 0) == EMPTY) //top left, bottom left
    tmp.push_back(coords(1, 0));

  if(b.at(0, 2) == p && b.at(2, 2) == p
     && b.at(1, 2) == EMPTY) //top right, bottom right
    tmp.push_back(coords(1, 2));

  if(b.at(2, 0) == p && b.at(2, 2) == p
     && b.at(2, 1) == EMPTY) //bottom left, bottom right
    tmp.push_back(coords(2, 1));

  return tmp;
}

vector<coords> tannerAi::end_empty(const board &b, const char p) const
{
  vector<coords> tmp;

  if(b.at(0, 0) == EMPTY) //top left is empty
  {
    if((b.at(1, 1) == p && b.at(2, 2) == p) //diagonal
       || (b.at(0, 2) == p && b.at(0, 1) == p) //horizontal
       || (b.at(2, 0) == p && b.at(1, 0) == p)) //vertical
      tmp.push_back(coords(0, 0));
  }

  if(b.at(0, 2) == EMPTY) //top right empty
  {
    if((b.at(2, 0) == p && b.at(1, 1) == p) //d
       || (b.at(0, 0) == p && b.at(0, 1) == p) //h
       || (b.at(2, 2) == p && b.at(1, 2) == p)) //v
      tmp.push_back(coords(0, 2));
  }

  if(b.at(2, 0) == EMPTY) //bottom left empty
  {
    if((b.at(0, 2) == p && b.at(1, 1) == p) //d
       || (b.at(2, 2) == p && b.at(2, 1) == p) //h
       || (b.at(0, 0) == p && b.at(1, 0) == p)) //v
      tmp.push_back(coords(2, 0));
  }

  if(b.at(2, 2) == EMPTY) //bottom right empty
  {
    if((b.at(0, 0) == p && b.at(1, 1) == p) //d
       || (b.at(2, 0) == p && b.at(2, 1) == p) //h
       || (b.at(0, 2) == p && b.at(1, 2) == p)) //v
      tmp.push_back(coords(2, 2));
  }

  if(b.at(1, 1) == p)
  {
    if(b.at(0, 1) == EMPTY && b.at(2, 1) == p) //v, empty above
      tmp.push_back(coords(0, 1));

    if(b.at(2, 1) == EMPTY && b.at(0, 1) == p) //v, empty below
      tmp.push_back(coords(2, 1));

    if(b.at(1, 2) == EMPTY && b.at(1, 0) == p) //h, empty right
      tmp.push_back(coords(1, 2));

    if(b.at(1, 0) == EMPTY && b.at(1, 2) == p) //h, empty left
      tmp.push_back(coords(1, 0));
  }

  return tmp;
}

tannerAi::tannerAi(const char f, const char p)
{
  tree = new multitree(f);
  player = p;

  gen_tree(f);
  eval_tree();
}

void tannerAi::gen_tree(const char p)//board &b) //uncomment for testing
{
  //commment for testing
  board b;
  b.reset();
  //to here

  gen_tree_r(b, p);
}

void tannerAi::eval_tree()//board &b) //uncomment for testing
{
  eval_tree_r();//b); //uncomment for testing
}

void tannerAi::play(board &b)
{
  for(unsigned int i = 0; i < tree->get_curr_numChildren(); i++)
  {
    tree->move(i);
    tree->move_up();
  }

  //get the player of the next level
  char levelPlayer = '?';
  if(tree->get_curr_numChildren() > 0)
  {
    tree->move(0);
    levelPlayer = tree->get_curr_player();
    tree->move_up();
  }

  //if the board is my node -> should only happen on root, I go first
  if(tree->get_curr_boardStr() == b.to_string(player) && levelPlayer == player)
  {
    tree->move(tree->get_curr_top_score());
    b.place(tree->get_curr_loc().get_r(), tree->get_curr_loc().get_c(), player);

    return;
  }

  //next level is me
  if(levelPlayer == player)
  {
    tree->move(tree->get_curr_top_score());
    b.place(tree->get_curr_loc().get_r(), tree->get_curr_loc().get_c(), player);

    return;
  }
  else //not me
  {
    //find the string that matches the board
    //switch to it, find its top scoring child
    //switch to it, play
    string bstr = b.to_string(player);

    for(unsigned short i = 0; i < tree->get_curr_numChildren(); i++)
    {
      tree->move(i);

      if(tree->get_curr_boardStr() == bstr)
        break;

      tree->move_up();
    }

    for(unsigned int i = 0; i < tree->get_curr_numChildren(); i++)
    {
      tree->move(i);
      tree->move_up();
    }

    tree->move(tree->get_curr_top_score());
    b.place(tree->get_curr_loc().get_r(), tree->get_curr_loc().get_c(), player);
  }
}


