#pragma once
#include "__def_enum_macros.h"



// Board
struct Board {
	u64 bb[13];
	bool side;
};


// Bit Manipulation
int bit_count(u64 x);
int pop_lsb(u64& b);