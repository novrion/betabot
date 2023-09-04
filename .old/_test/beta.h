#pragma once
#include <iostream>
#include <Windows.h>

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

enum {black, white};

#define U64 unsigned long long
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define del_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL >> square) : 0)



// in_out
void PrintBoard(U64 bitboard);


// Generate Moves
void init_moves();


U64 mask_pawn_attacks(int color, int square);

struct Board {

	Board() {
		// (white)	Pawn, Horse, Bishop, Rook, Queen, King
		b2[0] = 71776119061217280ULL;
		b2[1] = 4755801206503243776ULL;
		b2[2] = 2594073385365405696ULL;
		b2[3] = 9295429630892703744ULL;
		b2[4] = 576460752303423488ULL;
		b2[5] = 1152921504606846976ULL;

		// (black)	Pawn, Horse, Bishop, Rook, Queen, King
		b2[6] = 65280ULL;
		b2[7] = 66ULL;
		b2[8] = 36ULL;
		b2[9] = 129ULL;
		b2[10] = 8ULL;
		b2[11] = 16ULL;

		// (utility)
		b2[12] = 0ULL;
	}

	U64 b2[13];
};