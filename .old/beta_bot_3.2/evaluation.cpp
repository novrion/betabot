#include "evaluation.h"
using namespace std;
using namespace std::chrono;


// Evaluation
int evaluation(const U64 bb[13]) {

	int evaluation = 0;

	evaluation += materialScore(bb);
	evaluation += positionScore(bb);

	return evaluation;
}


static inline int materialScore(const U64 bb[13]) {

	int total = 0;

	for (int board = 1; board < 7; ++board) {
		total += material_score[board] * bitCount(bb[board]);
		total += material_score[board + 6] * bitCount(bb[board + 6]);
	}

	return total;
}

static inline int positionScore(const U64 bb[13]) {

	int total = 0;
	U64 pieceBitboard;

	for (int i = 1; i < 7; i++) {

		// white pieces
		pieceBitboard = bb[i];

		while (pieceBitboard) {
			int location = pop_lsb(pieceBitboard);
			total += position[i][location];
		}


		// black pieces
		pieceBitboard = bb[i + 6];

		while (pieceBitboard) {
			int location = pop_lsb(pieceBitboard);
			total -= position[i + 6][location];
		}
	}

	return total;
}


// Bit Manipulation
static inline int bitCount(U64 x) {

	x -= (x >> 1) & 0x5555555555555555; // put count of each 2 bits into those 2 bits

	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333); // put count of each 4 bits into those 4 bits

	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f; // put count of each 8 bits into those 8 bits

	return ((x * 0x0101010101010101) >> 56);
}

static inline int pop_lsb(U64& b) {

	const int s = countr_zero(b);
	b &= b - 1;
	return s;
}