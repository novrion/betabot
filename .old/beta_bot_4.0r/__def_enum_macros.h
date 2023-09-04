#pragma once
#include <bit>
#include <iostream>


#define u64 unsigned long long

#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (bitboard &= ~(1ULL << square))

#define _w_block(bb) (bb[1] | bb[2] | bb[3] | bb[4] | bb[5] | bb[6])
#define _b_block(bb) (bb[7] | bb[8] | bb[9] | bb[10] | bb[11] | bb[12])


enum side { black, white };
enum pieces { zero, P, N, B, R, Q, K, p, n, b, r, q, k };

struct Board {

	u64 bb[13];
	int side;
};