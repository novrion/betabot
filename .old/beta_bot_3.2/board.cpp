#include "board.h"


void make_move(U64 bb[13], U64& move, bool side) {

	

	int source = get_move_from(move);
	int target = get_move_to(move);

	int piece = get_move_piece(move);
	int capture = get_move_capture(move);

	int promotion = get_move_promotion(move);


	if (capture) {

		pop_bit(bb[piece], source);
		set_bit(bb[piece], target);


		if (side) {
			for (U64 i = 7; i < 13; ++i) {
				if (1ULL << target & bb[i]) {

					pop_bit(bb[i], target);

					move &= capture_mask;
					move |= (i << 23);

					return;
				}
			}
		}

		else {
			for (U64 i = 1; i < 7; ++i) {
				if (1ULL << target & bb[i]) {

					pop_bit(bb[i], target);

					move &= capture_mask;
					move |= (i << 23);

					return;
				}
			}
		}
	}

	else {

		pop_bit(bb[piece], source);
		set_bit(bb[piece], target);
	}
}

void undo_move(U64 bb[13], const U64 move) {

	int source = get_move_from(move);
	int target = get_move_to(move);
	int piece = get_move_piece(move);
	int capture = get_move_capture(move);


	if (!capture) {

		pop_bit(bb[piece], target);
		set_bit(bb[piece], source);
	}

	else {

		pop_bit(bb[piece], target);
		set_bit(bb[piece], source);

		set_bit(bb[capture], target);
	}
}