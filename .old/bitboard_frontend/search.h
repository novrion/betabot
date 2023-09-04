#pragma once

#include "__def_enum_macros.h"
#include "bitboard.h"



// Constants
const u64 time_flag = 9223372036854775808ULL;


// Search
std::pair<int, u64> iterative_deepening(Board& b, bool side, double max_time);

static inline std::pair<int, u64> layer_one_minimax(Board& b, int depth, bool side, double max_time);
static inline int minimax(Board& b, int depth, bool side, int alpha, int beta);
static inline int quiescence(Board& b, int depth, bool side, int alpha, int beta);