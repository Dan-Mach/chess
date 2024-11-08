#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

int main () {

     AllInit ();
     
     int PieceOne = rand();
     int PieceTwo = rand();
     int PieceThree = rand();
     int PieceFour = rand();

     printf("Piece one : %x \n ", PieceOne);
     printf("Piece Two : %x\n", PieceTwo);
     printf("Piece Three: %x\n", PieceThree);
     printf("Piece Four: %x\n", PieceFour);

     int Key = PieceOne ^ PieceTwo ^  PieceFour;

     int TempKey = PieceTwo;
     TempKey ^= PieceThree;
     TempKey ^= PieceFour;
     TempKey ^= PieceOne;

     printf("Key: %x\n", Key);
     printf("TempKey: %x \n", TempKey);

     TempKey ^= PieceThree;
     printf("(Three out ) TempKey : %x \n", TempKey);

     TempKey ^= PieceThree;
     printf("(Three in ) TempKey : %x \n", TempKey);

     return 0;
}