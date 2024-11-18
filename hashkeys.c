#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"

#define RAND_64 ((U64)rand() | \
                 (U64)rand() << 15 | \
                 (U64)rand() << 30 | \
                 (U64)rand() << 45 | \
                 ((U64)rand() & 0xf) << 60)

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

U64 GeneratePosKey(const S_BOARD *pos) {
    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    for (sq = 0; sq < BRD_SQ_NUM; ++sq) {
        piece = pos->pieces[sq];
        if (piece != NO_SQ && piece != EMPTY && piece != OFFBOARD) {
            ASSERT(piece >= wP && piece <= bK);
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    if (pos->side == WHITE) {
        finalKey ^= SideKey;
    }

    if (pos->enPas != NO_SQ) {
        ASSERT(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}

void InitHashKeys() {
    srand(time(NULL));  // Seed the random number generator for unique keys.

    for (int index = 0; index < 13; ++index) {
        for (int index2 = 0; index2 < 120; ++index2) {
            PieceKeys[index][index2] = RAND_64;
        }
    }

    SideKey = RAND_64;
    for (int index = 0; index < 16; ++index) {
        CastleKeys[index] = RAND_64;
    }
}
