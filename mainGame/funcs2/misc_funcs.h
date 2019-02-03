#ifndef MISC_FUNCS_H
#define MISC_FUNCS_H

#include <random>

/*Functions that are just handy for everyone*/

//goes from x->o or o->x
char swap_player(const char p);

//generates number 1-10, if >5 returns 'x', otherwise 'o'
char rand_player();

#endif // MISC_FUNCS_H
