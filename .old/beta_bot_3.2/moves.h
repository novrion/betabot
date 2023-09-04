#pragma once

#include "macros.h"


// Constants
const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;


// Move Generation
std::vector<U64> generate_moves(const U64 bb[13], bool side);
std::vector<U64> generate_captures(const U64 bb[13], bool side);


static inline void w_pawn_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_knight_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_bishop_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_rook_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_queen_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_king_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);

static inline void b_pawn_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_knight_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_bishop_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_rook_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_queen_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_king_moves(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);


static inline void w_pawn_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_knight_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_bishop_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_rook_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_queen_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void w_king_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);

static inline void b_pawn_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_knight_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_bishop_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_rook_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_queen_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);
static inline void b_king_captures(int square, const U64 w_block, const U64 b_block, std::vector<U64>& moves);