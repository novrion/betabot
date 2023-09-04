#pragma once

#include "__def_enum_macros.h"



// Board
struct Board {
	u64 bb[13];

	bool side;
};

// Make Move
//void MakeMove(u64 bb[13], const u64 move, bool side);