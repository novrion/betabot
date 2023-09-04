#include "bitboard.h"
using namespace std;



// Bit Manipulation
int bit_count(u64 x) {

	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

	return ((x * 0x0101010101010101) >> 56);
}
int pop_lsb(u64& b) {

	//const int s = __builtin_ctzll(b);
	const int s = countr_zero(b);
	b &= b - 1;

	return s;
}