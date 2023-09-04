#pragma once

#include "__def_enum_macros.h"


const U64 en_passant_mask = 18446744073709551488ULL;

const U64 w_castle_set = 128ULL;
const U64 b_castle_set = 256ULL;

const U64 w_l_rook_set = 512ULL;
const U64 w_r_rook_set = 1024ULL;
const U64 b_l_rook_set = 2048ULL;
const U64 b_r_rook_set = 4096ULL;

const U64 w_king_set = 8192ULL;
const U64 b_king_set = 16384ULL;


// Board
struct Board {
	U64 bb[13];
	bool side;
};

// Initialization
void _init_all(Board& b);
bool _init_side();

// Make Move
void MakeMove(U64 bb[13], const U64 move, bool side);

// Bit Manipulation
int bitCount(U64 x);
int pop_lsb(U64& b);