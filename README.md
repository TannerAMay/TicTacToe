# TicTacToe
Tanner May and Gavin Lewis

Made using C++11 on linux

Compile using "g++ mainGame/game/\*.cpp mainGame/funcs/\*.cpp tanner_AI/ai/tannerai.cpp tanner_AI/multitree/\*e.cpp -o game -std=c++11" from the root folder.

TicTacToe game for 0-2 people in the terminal. A joint project between Tanner May and Gavin Lewis. The goal was
to make two AIs battle each other, like the movie War Games.

Tanner's AI:
This is a basic chess AI adapted to work for tictactoe. It creates a tree of possible moves, then scores each move based
on winning conditions and the opponent's moves. After each play it indexes the tree and selects the highest scoring node.

Tanner's AI is finished and updated, Gavin's AI is not updated, so do not use his options.

Link to Gavin Lewis's github: https://github.com/GRNCheetah
