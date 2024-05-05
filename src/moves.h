#ifndef MOVES_H
#define MOVES_H


#include "macros.h"
#include "bb.h"


const U64 kNotAFile = 18374403900871474942ULL;
const U64 kNotHFile = 9187201950435737471ULL;
const U64 kNotABFile = 18229723555195321596ULL;
const U64 kNotGHFile = 4557430888798830399ULL;

const U64 kWCastleShortSpaceMask = 6917529027641081856ULL;
const U64 kWCastleLongSpaceMask = 1008806316530991104ULL;
const U64 kBCastleShortSpaceMask = 96ULL;
const U64 kBCastleLongSpaceMask = 14ULL;

const U64 kWCastleShortPawnMask = 69805794224242688ULL;
const U64 kWCastleShortKnightMask = 62197173760032768ULL;
const U64 kWCastleShortKingMask = 18014398509481984ULL;

const U64 kWCastleLongPawnMask = 17451448556060672ULL;
const U64 kWCastleLongKnightMask = 33563691949490176ULL;
const U64 kWCastleLongKingMask = 1688849860263936ULL;


const U64 kBCastleShortPawnMask = 63488ULL;
const U64 kBCastleShortKnightMask = 16309248ULL;
const U64 kBCastleShortKingMask = 16384ULL;

const U64 kBCastleLongPawnMask = 15872ULL;
const U64 kBCastleLongKnightMask = 4093696ULL;
const U64 kBCastleLongKingMask = 1536ULL;



void GenerateMoves(const U64 kBB[13], U64 moves[100], const bool kSide);
void GenerateCaptures(const U64 kBB[13], U64 moves[100], const bool kSide);

inline void AddMove(U64 moves[100], const U64 kMove);
inline bool CastleDiagonalInCheck(const U64 kBB[13], const U64 kWBlock, const U64 kBBlock, const int kSquare, const bool kSide);

inline void WPawnMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare);
inline void WKnightMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WBishopMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WRookMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WQueenMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WKingMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const U64 kBB[13]);

inline void BPawnMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare);
inline void BKnightMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BBishopMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BRookMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BQueenMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BKingMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const U64 kBB[13]);


inline void WPawnCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare);
inline void WKnightCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WBishopCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WRookCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WQueenCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void WKingCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);

inline void BPawnCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare);
inline void BKnightCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BBishopCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BRookCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BQueenCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);
inline void BKingCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]);


#endif // MOVES_H
