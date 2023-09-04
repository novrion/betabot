#pragma once


#include "__def_enum_macros.h"
#include "bitboard.h"
#include "search.h"


const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const char piece[13] = { ' ', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k' };
const char character[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const int reverse_int[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };



// Play Bot
void __play_bot__(Board& b, const double max_time);


// Input
bool InputSide();
void InputFen(Board& b);
void InputMove(Board& b);


// Output
void PrintBoard(u64 bb[13], const int source_square, const int target_square);
void PrintState(Board& b, const u64 move, const int evaluation);


// Translation
int translateToSquare(const std::string& input);
std::string translateToNotation(const u64 move);

u64 translateToMove(u64 bb[13], bool side, const std::string& source, const std::string& target);


// FEN
void ParseFen(Board& b, std::string& fen);
void PrintFen(Board& b);