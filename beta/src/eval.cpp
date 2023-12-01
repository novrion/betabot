#include "eval.h"



int Evaluate(const U64 kBB[13]) {

	int evaluation = 0;

	evaluation += MaterialScore(kBB);
	evaluation += PositionScore(kBB);

	return evaluation;
}


inline int MaterialScore(const U64 kBB[13]) {

	int total = 0;

	for (int board = 1; board < 7; ++board) {
		total += kMaterialScore[board] * BitCount(kBB[board]);
		total += kMaterialScore[board + 6] * BitCount(kBB[board + 6]);
	}

	return total;
}

inline int PositionScore(const U64 kBB[13]) {

	int total = 0;
	U64 pieceBitboard;

	for (int i = 1; i < 7; i++) {

		// white pieces
		pieceBitboard = kBB[i];

		while (pieceBitboard) {
			int location = PopLsb(pieceBitboard);
			total += kPositionScore[i][location];
		}


		// black pieces
		pieceBitboard = kBB[i + 6];

		while (pieceBitboard) {
			int location = PopLsb(pieceBitboard);
			total -= kPositionScore[i + 6][location];
		}
	}

	return total;
}