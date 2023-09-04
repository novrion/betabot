#include "bitboard.h"
using namespace std;


// Make Move
/*void MakeMove(U64 bb[13], U64& move, bool side) {

	int source = get_move_source(move);
	int target = get_move_target(move);
	int piece = get_move_piece(move);

	int _2pawn = get_move_2_pawn(move);
	int en_passant = get_move_en_passant(move);
	int castle = get_move_castle(move);

	int promotion = get_move_promotion(move);
	int capture = get_move_capture(move);


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
}*/

void MakeMove(U64 bb[13], const U64 move, bool side) {

	/// Make En Passant not be a capture!!!

	int source = get_move_source(move);
	int target = get_move_target(move);
	int piece = get_move_piece(move);

	int _2pawn = get_move_2_pawn(move);
	int en_passant = get_move_en_passant(move);
	int castle = get_move_castle(move);

	int promotion = get_move_promotion(move);
	int capture = get_move_capture(move);


	// Reset En Passant Square
	bb[0] &= en_passant_mask;

	// Update Rook Moved Flag
	if ((source == 56 || source == 63) && piece == 4) {

		if (source == 56) bb[0] |= w_l_rook_set;
		else bb[0] |= w_r_rook_set;
	}
	else if ((source == 0 || source == 7) && piece == 10) {

		if (source == 0) bb[0] |= b_l_rook_set;
		else bb[0] |= b_r_rook_set;
	}

	// Update King Moved Flag
	if (piece == 6) bb[0] |= w_king_set;
	else if (piece == 12) bb[0] |= b_king_set;



	if (capture) {

		pop_bit(bb[piece], source);

		if (side) {
			for (U64 i = 7; i < 13; ++i) {
				if (1ULL << target & bb[i]) {
					pop_bit(bb[i], target);
				}
			}
		}
		else {
			for (U64 i = 1; i < 7; ++i) {
				if (1ULL << target & bb[i]) {
					pop_bit(bb[i], target);
				}
			}
		}


		if (promotion) set_bit(bb[promotion], target);
		else set_bit(bb[piece], target);
	}

	else if (castle) {

		if (side) {

			bb[0] |= w_castle_set;
			pop_bit(bb[6], 60);
			
			if (target > source) {

				set_bit(bb[6], 62);

				pop_bit(bb[4], 63);
				set_bit(bb[4], 61);
			}

			else {

				set_bit(bb[6], 58);

				pop_bit(bb[4], 56);
				set_bit(bb[4], 59);
			}
		}

		else {

			bb[0] |= b_castle_set;
			pop_bit(bb[12], 4);

			if (target > source) {

				set_bit(bb[12], 6);

				pop_bit(bb[10], 7);
				set_bit(bb[10], 5);
			}

			else {

				set_bit(bb[12], 2);

				pop_bit(bb[10], 0);
				set_bit(bb[10], 3);
			}
		}
	}

	else if (en_passant) {

		if (side) {
			pop_bit(bb[1], source);
			set_bit(bb[1], target);

			pop_bit(bb[7], en_passant);
		}

		else {
			pop_bit(bb[7], source);
			set_bit(bb[7], target);

			pop_bit(bb[1], en_passant);
		}
	}

	else if (_2pawn) {

		pop_bit(bb[piece], source);
		set_bit(bb[piece], target);

		bb[0] |= target;
	}

	else {

		pop_bit(bb[piece], source);
		set_bit(bb[piece], target);
	}
}


// Bit Manipulation
int bitCount(U64 x) {

	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

	return ((x * 0x0101010101010101) >> 56);
}
int pop_lsb(U64& b) {

	//const int s = __builtin_ctzll(b);
	const int s = countr_zero(b);
	b &= b - 1;

	return s;
}


// Initialization
void _init_all(Board& b) {

	/*------------------------------------------------------------*/

	// (utility)
	b.bb[0] = 0ULL;

	// (white) Pawn, Knight, Bishop, Rook, Queen, King
	b.bb[1] = 71776119061217280ULL;
	b.bb[2] = 4755801206503243776ULL;
	b.bb[3] = 2594073385365405696ULL;
	b.bb[4] = 9295429630892703744ULL;
	b.bb[5] = 576460752303423488ULL;
	b.bb[6] = 1152921504606846976ULL;

	// (black) Pawn, Knight, Bishop, Rook, Queen, King
	b.bb[7] = 65280ULL;
	b.bb[8] = 66ULL;
	b.bb[9] = 36ULL;
	b.bb[10] = 129ULL;
	b.bb[11] = 8ULL;
	b.bb[12] = 16ULL;

	/*------------------------------------------------------------*/


	b.side = _init_side();
}
bool _init_side() {

	char ch;

	cout << "W/B: ";
	cin >> ch;

	return ((ch == 'W' || ch == 'w') ? true : false);
}