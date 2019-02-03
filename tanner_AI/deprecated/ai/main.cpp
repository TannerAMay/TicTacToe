#include "tanner_ai2.h"

int main()
{
  char **board = buildBoard();
  setBoard(board);

  tanner_ai2 ai('x');

  /*int cntr = 0;
  while(ai.tree.at()->children[0] != nullptr)
  {
    cout << "Parent " << cntr << endl;

    for(int i = 0; i < ai.tree.at()->children.size(); i++)
    {
      cout << "child " << ai.tree.at()->children[i]->eval << endl;
    }

    ai.tree.move(0);
    cntr++;
  }*/

  //ai.tree.print();

  ai.tree.exp();

  return 0;
}
