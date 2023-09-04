#include "bitboard.h"


int bit_count(u64 bb) {

    bb -= (bb >> 1) & 0x5555555555555555;
    bb = (bb & 0x3333333333333333) + ((bb >> 2) & 0x3333333333333333);
    bb = (bb + (bb >> 4)) & 0x0f0f0f0f0f0f0f0f;

    return ((bb * 0x0101010101010101) >> 56);
}