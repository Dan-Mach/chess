#include <stdio.h>
#include "defs.h"

const int BitTable[64] = {
 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64

};

int PopBit( U64 *bb) {
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26 ];

}

int CountBits(U64 b) {
    int r;
    for (r = 0; b; r++, b &= b-1);
    return r;
}
void PrintBitBoard( U64 bb) {
    U64 shiftme = 1ULL;

    int rank = 0;
    int file = 0;
    int sq = 0;
    int sq64 = 0;

    printf("\n");

    for (rank = RANK_8; rank >= RANK_1; --rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file,rank);
            sq64 = SQ64(sq);
            if ((shiftme << sq64) & bb){
                printf("X");
            }
            else {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}