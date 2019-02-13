#include "tannerai.h"

/*files included at this point
 * <iostream>
 * "coords.h"
 * <vector>
 * "node.h"
 * "multitree.h"
 * <iostream>       I don't know if these two lines will cause issues
 * "coords.h"       !
 * <random>
 * "misc_funcs.h"
 * "board.h"
 * "tannerai.h"
 */

int main()
{
  board b;

  b.place(0, 0, 'o');
  //b.place(0, 1, 'o');
  b.place(0, 2, 'o');
  //b.place(1, 0, 'q');
  b.place(1, 1, 'o');
  //b.place(1, 2, 'e');
  //b.place(2, 0, 'r');
  //b.place(2, 1, 't');
  //b.place(2, 2, 'y');

  b.print();

  //string stop;
  //std::cin >> stop;

  tannerAi t('o', 'x');

  vector<coords> v = t.end_empty(b, 'o');

  for(int i = 0; i < v.size(); i++)
  {
    cerr << v[i] << " ";
  }
  cerr << endl;

  t.gen_tree(b);
  t.eval_tree(b); //uncomment for testing
  t.print_tree();
  //b.print();

  return 0;
}
