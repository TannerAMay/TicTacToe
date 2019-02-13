#include "misc_funcs.h"

char swap_player(const char p)
{
  if(p == 'x')
    return 'o';

  return 'x';
}

char rand_player()
{
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);

  if(dis(gen) > 5)
    return 'x';

  return 'o';
}
