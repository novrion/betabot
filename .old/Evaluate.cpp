// Evaluation
int Evaluate(const U64 bb[13]) {

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