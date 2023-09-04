#pragma once

#include "macros.h"


const U64 kEnPassantMask = 960ULL;

const U64 kWShortCastleMask = 959ULL;
const U64 kWLongCastleMask = 895ULL;
const U64 kWBothCastleMask = 831ULL;

const U64 kBShortCastleMask = 767ULL;
const U64 kBLongCastleMask = 511ULL;
const U64 kBBothCastleMask = 255ULL;


// Board
struct Board {
	U64 bb[13];
	bool side;
};



// Initialization
void InitAll(Board& b, bool& kSide, double& max_search_time);
bool InitSide();
double InitMaxSearchTime();

// Make Move
void MakeMove(U64 bb[13], const U64 kMove, const bool kSide);

// Bit Manipulation
int BitCount(U64 x);
int PopLsb(U64& b);