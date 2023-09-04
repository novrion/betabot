#pragma once

#include <chrono>
#include "macros.h"

static std::chrono::duration<double> total_time = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
static int time_count = 0;

void debug_cout_board(U64 bitboard);