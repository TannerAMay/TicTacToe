#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <random>
#include "../tanner_AI/MultiTree/coords.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

char ** buildBoard(); //board class
void printBoard(char ** &board); //baord class
void deleteBoard(char ** &board); //board class
void setBoard(char ** &board); //baord class
bool full(char ** &board); //board class
bool emptyBoard(char ** board); //board class
void copyBoard(char * const * const board, char ** b);

char solved(char ** &board); //board class
// Takes a board and will return one of three characters
// 'x', 'o', or 'n'. A player or a non-won board state

bool emptySlot(char ** &board, int r, int c); //replaced by at() in board class
char swapPlayer(const char player);
char at(char ** board, int r, int c); //board class

char randPlayer();

#endif // FUNCS_H
