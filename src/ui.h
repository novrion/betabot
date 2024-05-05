#ifndef UI_H
#define UI_H


#include "search.h"


const double kMaxSearchTime = 4.0;

const char piece[13] = { ' ', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k' };
const char character[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const int reverse_int[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };



// Tutorial
void PrintTutorial();

// User Interaction
std::pair<int, int> UserInputMove();
void InputFen(Board& b);

// Interface
void clear_ui();
void PrintBoard(const char kBoard[64], const int kSource, const int kTarget);
void PrintState(Board& b, const int kEval, const U64 kNextMove, const int kPly, bool player_turn[400]);

// Translation
std::string MoveToNotation(const U64 kMove);
int StringToSquare(const std::string kStr);

// FEN
void ParseFen(Board& b, std::string& fen);
void PrintFen(Board& b, const bool kSide);


#endif // UI_H
