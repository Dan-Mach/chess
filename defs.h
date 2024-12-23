#ifndef DEFS_H
#define DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)) { \
    printf("%s - Failed", #n); \
    printf(" On %s", __DATE__); \
    printf(" At %s", __TIME__); \
    printf(" In File %s", __FILE__); \
    printf(" At line %d\n", __LINE__); \
    exit(1); \
}
#endif

typedef unsigned long long U64;

#define NAME "Arora 1.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048
#define INVALID_SQUARE 65
#define MAXPOSITIONMOVES 256
#define MAXDEPTH 64

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define INFINITE 30000
#define ISMATE (INFINITE - MAXDEPTH)

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { WHITE, BLACK, BOTH };
enum {UCICODE, XBOARDMODE, CONSOLEMODE};
enum { FALSE, TRUE };
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum { HFNONE, HFALPHA, HFBETA, HFEXACT };

typedef struct {
    int move;
    int score;
}S_MOVE;

typedef struct {
    S_MOVE moves[MAXPOSITIONMOVES];
    int count;
}S_MOVELIST;

typedef struct {
    U64 posKey;
    int move;
    int score;
    int depth;
    int flags;
}S_HASHENTRY;

typedef struct {
    S_HASHENTRY *pTable;
    int numEntries;
    int newwrite;
    int overwrite;
    int hit;
    int cut;

}S_HASHTABLE;

typedef struct {
    int move;
    int castlePerm;
    int fiftyMove;
    U64 posKey;
} S_UNDO;

typedef struct {
    int pieces[BRD_SQ_NUM];

    U64 pawns[3];
    int KingSQ[2];

    int side;
    int enPas;
    int fiftyMove;
    int ply;
    int hisply;
    int castlePerm;

    U64 posKey;

    int pceNum[13];
    int bigPce[2];
    int majPce[2];
    int minPce[2];
    int material[2];

    S_UNDO history[MAXGAMEMOVES];
    int pList[13][10];

    S_HASHTABLE HashTable[1];
    int PvArray[MAXDEPTH];

    int searchHistory[13][BRD_SQ_NUM];
    int searchKillers[2][MAXDEPTH];
} S_BOARD;

typedef struct {

	int starttime;
	int stoptime;
	int depth;
	int timeset;
	int movestogo;

	long nodes;

	int quit;
	int stopped;

	float fh;
	float fhf;
	int nullCut;

	int GAME_MODE;
	int POST_THINKING;

} S_SEARCHINFO;

typedef struct {
	int UseBook;
} S_OPTIONS;


// Macros
#define FR2SQ(f,r) ((21 + (f)) + ((r) * 10))
#define SQ64(sq120) (Sq120ToSq64[sq120])
#define SQ120(sq64) (Sq64ToSq120[sq64])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb,sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb,sq) ((bb) |= SetMask[(sq)])

// Globals
extern U64 SetMask[64];
extern U64 ClearMask[64];

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

// Function Declarations

//init.c
extern void AllInit();
//bitboard.c
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);
//board.c
extern void PrintBoard(const S_BOARD *pos);
extern void ResetBoard(S_BOARD *pos);
extern int Parse_Fen(char *fen, S_BOARD *pos);
extern void UpdateListMaterial(S_BOARD *pos);
extern int CheckBoard(const S_BOARD *pos);
extern int PceListOk(const S_BOARD *pos);

//harshKeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);
extern void InitHashKeys();

#endif
