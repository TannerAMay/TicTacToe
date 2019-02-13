#ifndef PLAY_FUNCS_H
#define PLAY_FUNCS_H

//file that contains the play functions for 0, 1, and 2 players

//#include "../funcs2/board.h"

#include "../../tanner_AI/ai2/tannerai.h"

/*files included at this point
 * <iostream>
 * "../multitree2/coords.h"
 * <vector>
 * "../multitree2/node.h"
 * "../multitree2/multitree.h"
 * <iostream>       I don't know if these two lines will cause issues
 * "coords.h"       !
 * <random>
 * "misc_funcs.h"
 * "board.h"
 * "tannerai.h"
 */

using std::cin;

//throws string if b isn't empty
bool play_2(board &b);
bool play_1g(board &b); //human vs gavin's ai
bool play_1t(board &b); //human vs tanner's ai
bool play_0b(board &b); //gavin's vs tanner's
bool play_0g(board &b); //gavin's vs gavin's
bool play_0t(board &b); //tanner's vs tanner's

#endif // PLAY_FUNCS_H
