#pragma once

#include "macros.h"
#include "moves.h"
#include "board.h"
#include "evaluation.h"


const U64 time_flag = 9223372036854775808ULL;


// Search
std::pair<int, U64> iterative_deepening(U64 bb[13], bool side, double max_time);

static inline std::pair<int, U64> layer_one_minimax(U64 bb[13], int depth, bool side, double max_time);
static inline int minimax(U64 bb[13], int depth, bool side, int alpha, int beta);
static inline int quiescence(U64 bb[13], int depth, bool side, int alpha, int beta);