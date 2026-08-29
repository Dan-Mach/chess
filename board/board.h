//board.c
#ifndef BOARD_H
#define BOARD_H
#include "../defs.h"

extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void UpdateListMaterial(S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);

#endif