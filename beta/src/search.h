#pragma once

#include "macros.h"
#include "moves.h"
#include "eval.h"


const U64 kTimeFlag = 9223372036854775808ULL;
const int kR = 2;
const int kMVVLVA[13][13] = {
  0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,
  0,  105, 205, 305, 405, 505, 605,  105, 205, 305, 405, 505, 605,
  0,  104, 204, 304, 404, 504, 604,  104, 204, 304, 404, 504, 604,
  0,  103, 203, 303, 403, 503, 603,  103, 203, 303, 403, 503, 603,
  0,  102, 202, 302, 402, 502, 602,  102, 202, 302, 402, 502, 602,
  0,  101, 201, 301, 401, 501, 601,  101, 201, 301, 401, 501, 601,
  0,  100, 200, 300, 400, 500, 600,  100, 200, 300, 400, 500, 600,

  0,  105, 205, 305, 405, 505, 605,  105, 205, 305, 405, 505, 605,
  0,  104, 204, 304, 404, 504, 604,  104, 204, 304, 404, 504, 604,
  0,  103, 203, 303, 403, 503, 603,  103, 203, 303, 403, 503, 603,
  0,  102, 202, 302, 402, 502, 602,  102, 202, 302, 402, 502, 602,
  0,  101, 201, 301, 401, 501, 601,  101, 201, 301, 401, 501, 601,
  0,  100, 200, 300, 400, 500, 600,  100, 200, 300, 400, 500, 600
};



void IterativeDeepening(Board& b, const bool kSide, const double kMaxTime, int& evaluation_out, U64& move_out, const bool kEndGame, std::unordered_map<U64, U64> hash);

inline std::pair<int, U64> LayerOneNegaMax(Board& b, const int kDepth, const bool kSide, const double kMaxTime, std::unordered_map<U64, U64> hash);
inline int NegaMax(Board& b, const int kDepth, const bool kSide, int alpha, int beta, std::unordered_map<U64, U64> hash);
inline int Quiescence(Board& b, const int kDepth, const bool kSide, int alpha, int beta);
