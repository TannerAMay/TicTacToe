#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <random>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;

char ** buildBoard();
void printBoard(char ** &board);
void deleteBoard(char ** &board);
void setBoard(char ** &board);
bool full(char ** &board);
char solved(char ** &board);
// Takes a board and will return one of three characters
// 'x', 'o', or 'n'. A player or a non-won board state
bool emptySlot(char ** &board, int r, int c);
char swapPlayer(const char player);

bool play2(char ** &board, char player);
bool play1(char ** &board);
bool play0(char ** &board);

char randPlayer();
//char randPlayerAI();

#endif // FUNCS_H
