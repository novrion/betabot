#pragma once

#include <iostream>
#include <set>
#include <Windows.h>
#include <bit>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <map>
#include <string>


enum {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1
};
enum { black, white };

#define U64 unsigned long long
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

#define _w_block(x) (x[1] | x[2] | x[3] | x[4] | x[5] | x[6])
#define _b_block(x) (x[7] | x[8] | x[9] | x[10] | x[11] | x[12])


// Decode
#define get_move_from(move) (move & 63ULL)
#define get_move_to(move) ((move & 4032ULL) >> 6)
#define get_move_piece(move) ((move & 61440ULL) >> 12)

#define get_move_2_pawn(move) (move & 65536ULL)
#define get_move_en_passant(move) (move & 131072ULL)
#define get_move_castle(move) (move & 262144ULL)

#define get_move_promotion(move) ((move & 7864320ULL) >> 19)
#define get_move_capture(move) ((move & 125829120ULL) >> 23)


// Board
struct Board {

	Board() {

		// (white)	Pawn, Horse, Bishop, Rook, Queen, King
		b2[1] = 71776119061217280ULL;
		b2[2] = 4755801206503243776ULL;
		b2[3] = 2594073385365405696ULL;
		b2[4] = 9295429630892703744ULL;
		b2[5] = 576460752303423488ULL;
		b2[6] = 1152921504606846976ULL;

		// (black)	Pawn, Horse, Bishop, Rook, Queen, King
		b2[7] = 65280ULL;
		b2[8] = 66ULL;
		b2[9] = 36ULL;
		b2[10] = 129ULL;
		b2[11] = 8ULL;
		b2[12] = 16ULL;

		// (utility)
		b2[0] = 0ULL;

		// next move
		n_move = 0ULL;
	}

	U64 b2[13];
	U64 n_move;
};


// in_out
int input_match(Board& b);
int InputColor();

void cout_state(Board& b, int evaluation, U64 n_move, int colour);
void user_make_move(Board& b, int colour);

std::string translate_to_notation(U64 move);


// Encode 
U64 encode_move(U64 b2[13], int from, int to, int piece, int capture, int promotion, int _2pawn, int en_passant, int castle);


// Generate Moves
void gen_moves(U64 b2[13], int colour, std::set<U64>& moves);
void gen_captures(U64 b2[13], int colour, std::set<U64>& moves);

void pawn_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void knight_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void king_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void bishop_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void rook_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void queen_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);

void pawn_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void knight_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void king_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void bishop_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void rook_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);
void queen_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, std::set<U64>& moves);


// Make Move
void make_move(U64 b2[13], U64 move, int colour);
void undo_move(U64 b2[13], U64 move, int colour);


// Search
int iterative_deepening(Board& b, int colour, double max_time);