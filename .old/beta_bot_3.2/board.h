#pragma once

#include "macros.h"


const U64 capture_mask = 8388607ULL;


void make_move(U64 bb[13], U64& move, bool side);
void undo_move(U64 bb[13], const U64 move);