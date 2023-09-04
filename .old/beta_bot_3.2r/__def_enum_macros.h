#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <map>


/// > - < https://github.com/tmacksf/TtCE/blob/main/Bitboard.hpp

#define U64 unsigned long long

// Bit Manipulation
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (bitboard &= ~(1ULL << square))

// Blockers
#define _w_block(bb) (bb[1] | bb[2] | bb[3] | bb[4] | bb[5] | bb[6])
#define _b_block(bb) (bb[7] | bb[8] | bb[9] | bb[10] | bb[11] | bb[12])

// Encode Move
#define encode_move(source, target, piece, capture, promotion, _2pawn, en_passant, castle) \
(source) | (target << 6) | (piece << 12) | (_2pawn << 16) | (en_passant << 17) | (castle << 18) | (promotion << 19) | (capture << 23) \

// Decode Move
#define get_move_source(move) (move & 63ULL)
#define get_move_target(move) ((move & 4032ULL) >> 6)
#define get_move_piece(move) ((move & 61440ULL) >> 12)

#define get_move_2_pawn(move) (move & 65536ULL)
#define get_move_en_passant(move) (move & 131072ULL)
#define get_move_castle(move) (move & 262144ULL)

#define get_move_promotion(move) ((move & 7864320ULL) >> 19)
#define get_move_capture(move) ((move & 125829120ULL) >> 23)


// Decode Utility
#define get_utility_en_passant(utility) (utility & 127ULL)

#define get_utility_w_castle(utility) (utility & 128ULL)
#define get_utility_b_castle(utility) (utility & 256ULL)

#define get_utility_w_l_rook(utility) (utility & 512ULL)
#define get_utility_w_r_rook(utility) (utility & 1024ULL)
#define get_utility_b_l_rook(utility) (utility & 2048ULL)
#define get_utility_b_r_rook(utility) (utility & 4096ULL)

#define get_utility_w_king(utility) (utility & 8192ULL)
#define get_utility_b_king(utility) (utility & 16384ULL)


// Good sort :)
/*sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return a < (>) b; }); */
/*int i = moves.size() - 1; i >= 0; --i*/