#pragma once

#include "macros.h"
#include "search.h"


// Constants
const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Board
struct Board {

	U64 bb[13];
	bool side;
};

// Play Bot
void __play_bot__(Board &b, double max_time);

// Initialization
void _init_all(Board &b);
bool _init_side();

// User Interaction
void user_make_move(Board& b);


// Interface
void cout_board(const char board[64]);
void cout_state(Board& b, int evaluation, U64 next_move);

// Translation
std::string translate_to_notation(U64 move);
int translate_to_square(std::string input);