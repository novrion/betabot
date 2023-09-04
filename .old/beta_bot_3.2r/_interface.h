#pragma once

#include "search.h"


// Play Bot
void __play_bot__(Board& b, double max_time);

// User Interaction
void user_MakeMove(Board& b);

// Interface
void cout_board(const char board[64]);
void cout_state(Board& b, int evaluation, U64 next_move);

// Translation
std::string translate_to_notation(U64 move);
int translate_to_square(std::string input);