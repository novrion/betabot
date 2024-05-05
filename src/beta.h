#ifndef BETA_H
#define BETA_H


#include "macros.h"
#include "ui.h"
#include "search.h"



void PlayBot();

inline void BotMove(Board& b, int& evaluation, U64& move, const bool kSide, const double kMaxSearchTime);
inline void UserMove(int& ply, Board& b, U64& move, const bool kSide, bool& back);
inline void SaveState(Board boards[400], int evaluations[400], U64 moves[400], const int kPly, Board& b, const int kEval, const U64 move);
inline void LoadState(Board boards[400], int evaluations[400], U64 moves[400], const int kPly, Board& b, int& evaluation, U64& move);

inline bool VerifyMove(Board& b, const U64 KMove, const bool kSide);

inline U64 TranslateToMove(Board& b, const int kSource, const int kTarget, const bool kSide);


#endif // BETA_H