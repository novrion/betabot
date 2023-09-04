#include "beta.h"
using namespace std;

int minimax(U64 b2[13], int depth, int colour) {

	if (!depth) return 1;

	int evaluation = 0;

	set<U64> moves;
	gen_moves(b2, colour, moves);


	if (colour) {

		for (U64 move : moves) {

			make_move(b2, move, colour);
			evaluation += minimax(b2, depth - 1, 0);
			undo_move(b2, move, colour);

		}

		return evaluation;
	}


	else {

		for (U64 move : moves) {

			make_move(b2, move, colour);
			evaluation += minimax(b2, depth - 1, 1);
			undo_move(b2, move, colour);

		}

		return evaluation;
	}
}
