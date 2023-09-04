#pragma once
#include "__def_enum_macros.h"
#include "bitboard.h"
#include "moves.h"


const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const char piece[13] = { ' ', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k' };
const char character[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const int reverse_int[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };



// Play Bot
void __play_bot__(Board& b, const double max_time);

// Initialization
void _init_board(Board& b);





// Input
bool input_side();
void input_fen(Board& b);
void input_move(Board& b);


// FEN
void parseFen(Board& b, std::string& fen);
void printFen(Board& b);


// Output
void print_board(u64 bb[13], const int source_square, const int target_square);
void print_state(Board& b, const u64 move, const int evaluation);


// Translation
int translate_to_square(const std::string& input);
std::string translate_to_notation(const u64 move);
u64 translate_to_move(u64 bb[13], bool side, const std::string& source, const std::string& target);