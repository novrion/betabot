#pragma once

#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <map>
#include <bit>



// Macro
#define U64 unsigned long long
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)
//#define pop_bit(bitboard, square) (bitboard ^= (1ULL << square))

#define _w_block(x) (x[1] | x[2] | x[3] | x[4] | x[5] | x[6])
#define _b_block(x) (x[7] | x[8] | x[9] | x[10] | x[11] | x[12])


// Encode
#define encode_move(source, target, piece, capture, promotion, _2pawn, en_passant, castle) \
(source) | (target << 6) | (piece << 12) | (_2pawn << 16) | (en_passant << 17) | (castle << 18) | (promotion << 19) | (capture << 23) \


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


// Generate Moves
void gen_moves(U64 b2[13], int colour, U64 moves[100]);

void pawn_moves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
void knight_moves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
void king_moves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
void bishop_moves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
void rook_moves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);
void queen_moves(int square, int colour, U64 w_block, U64 b_block, U64 moves[100]);


// Make Move
void make_move(U64 b2[13], U64& move, int colour);
void undo_move(U64 b2[13], U64& move, int colour);


// Search
//int minimax(U64 b2[13], int depth, int colour);
U64 minimax(Board& b, int depth, int colour);