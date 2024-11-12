#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/4p3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1 "
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4p3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2 "
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4p3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2 "

int main () {

     AllInit ();

     S_BOARD board[1];

     Parse_Fen(START_FEN, board);
     PrintBoard(board);
     
     
     

     return 0;
}