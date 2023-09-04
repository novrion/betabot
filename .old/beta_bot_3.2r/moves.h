#pragma once

#include "__def_enum_macros.h"
#include "bitboard.h"


// Constants
const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;

const U64 w_castle_short_space_mask = 6917529027641081856ULL;
const U64 w_castle_long_space_mask = 1008806316530991104ULL;
const U64 b_castle_short_space_mask = 96ULL;
const U64 b_castle_long_space_mask = 14ULL;

const U64 w_castle_short_pawn_mask = 69805794224242688ULL;
const U64 w_castle_short_knight_mask = 62197173760032768ULL;
const U64 w_castle_short_king_mask = 18014398509481984ULL;

const U64 w_castle_long_pawn_mask = 17732923532771328ULL;
const U64 w_castle_long_knight_mask = 35816591274803200ULL;
const U64 w_castle_long_king_mask = 1688849860263936ULL;


const U64 b_castle_short_pawn_mask = 63488ULL;
const U64 b_castle_short_knight_mask = 16309248ULL;
const U64 b_castle_short_king_mask = 16384ULL;

const U64 b_castle_long_pawn_mask = 16128ULL;
const U64 b_castle_long_knight_mask = 4161280ULL;
const U64 b_castle_long_king_mask = 1536ULL;



// Add Move
static inline void AddMove(U64 moves[100], const U64 move);


// Move Generation
void generate_moves(const U64 bb[13], U64 moves[100], bool side);
void generate_captures(const U64 bb[13], U64 moves[100], bool side);


static inline void w_pawn_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square);
static inline void w_knight_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_bishop_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_rook_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_queen_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_king_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const U64 bb[13]);

static inline void b_pawn_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square);
static inline void b_knight_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_bishop_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_rook_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_queen_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_king_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const U64 bb[13]);


static inline void w_pawn_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square);
static inline void w_knight_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_bishop_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_rook_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_queen_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void w_king_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);

static inline void b_pawn_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square);
static inline void b_knight_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_bishop_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_rook_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_queen_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);
static inline void b_king_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]);