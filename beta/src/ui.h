#pragma once

#include "search.h"


const double kMaxSearchTime = 4.0;

const char piece[13] = { ' ', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k' };
const char character[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const int reverse_int[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };



// Play Bot
void PlayBot();

void BotMove(Board& b, int& evaluation, U64& move, const bool kSide, const double kMaxSearchTime);
void UserMove(int& ply, Board& b, U64& move, const bool kSide, bool& back);
void SaveState(const int kPly, Board& b, const int kEval, const U64 move);
void LoadState(const int kPly, Board& b, int& evaluation, U64& move);


// User Interaction
std::pair<int, int> UserInputMove();
void InputFen(Board& b);

// Interface
void PrintBoard(const char kBoard[64], const int kSource, const int kTarget);
void PrintState(Board& b, const int kEval, const U64 kNextMove, const int kPly);

// Translation
U64 TranslateToMove(Board& b, const int kSource, const int kTarget, const bool kSide);
std::string MoveToNotation(const U64 kMove);
int StringToSquare(const std::string kStr);

// Verify Move
bool VerifyMove(Board& b, const U64 KMove, const bool kSide);

// FEN
void ParseFen(Board& b, std::string& fen);
void PrintFen(Board& b, const bool kSide);