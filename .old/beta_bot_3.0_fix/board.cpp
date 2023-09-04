#include "beta.h"
using namespace std;

void gen_moves(U64 b2[13], int colour, set<U64>& moves) {

	U64 w_block = _w_block(b2);
	U64 b_block = _b_block(b2);

	if (colour) {

		for (int square = 0; square < 64; square++) {

			if (b2[0] & 1ULL << square) {
				pawn_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[1] & 1ULL << square) {
				knight_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[2] & 1ULL << square) {
				bishop_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[3] & 1ULL << square) {
				rook_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[4] & 1ULL << square) {
				queen_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[5] & 1ULL << square) {
				king_moves(b2, square, colour, w_block, b_block, moves);
			}
		}
	}

	else {

		for (int square = 0; square < 64; square++) {

			if (b2[6] & 1ULL << square) {
				pawn_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[7] & 1ULL << square) {
				knight_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[8] & 1ULL << square) {
				bishop_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[9] & 1ULL << square) {
				rook_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[10] & 1ULL << square) {
				queen_moves(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[11] & 1ULL << square) {
				king_moves(b2, square, colour, w_block, b_block, moves);
			}
		}
	}
}

void gen_captures(U64 b2[13], int colour, set<U64>& moves) {

	U64 w_block = _w_block(b2);
	U64 b_block = _b_block(b2);


	if (colour) {

		for (int square = 0; square < 64; square++) {

			if (b2[0] & 1ULL << square) {
				pawn_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[1] & 1ULL << square) {
				knight_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[2] & 1ULL << square) {
				bishop_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[3] & 1ULL << square) {
				rook_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[4] & 1ULL << square) {
				queen_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[5] & 1ULL << square) {
				king_captures(b2, square, colour, w_block, b_block, moves);
			}
		}
	}

	else {

		for (int square = 0; square < 64; square++) {

			if (b2[6] & 1ULL << square) {
				pawn_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[7] & 1ULL << square) {
				knight_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[8] & 1ULL << square) {
				bishop_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[9] & 1ULL << square) {
				rook_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[10] & 1ULL << square) {
				queen_captures(b2, square, colour, w_block, b_block, moves);
			}

			if (b2[11] & 1ULL << square) {
				king_captures(b2, square, colour, w_block, b_block, moves);
			}
		}
	}
}

U64 encode_move(U64 b2[13], int from, int to, int piece, int capture, int promotion, int _2pawn, int en_passant, int castle) {

	U64 move = 0ULL;

	if (capture) {

		if (piece < 6) {
			for (int i = 6; i < 12; i++) {
				if (1ULL << to & b2[i]) {
					capture = i;
					break;
				}
			}
		}

		else {
			for (int i = 0; i < 6; i++) {
				if (1ULL << to & b2[i]) {
					capture = i;
					break;
				}
			}
		}
	}

	move = ((move |= capture) << 4);
	move = ((move |= promotion) << 1);

	move = ((move |= castle) << 1);
	move = ((move |= en_passant) << 1);
	move = ((move |= _2pawn) << 4);

	move = ((move |= piece) << 6);
	move = ((move |= to) << 6);
	move = (move |= from);

	return move;
}

void make_move(U64 b2[13], U64 move, int colour) {

	int source = get_move_from(move);
	int target = get_move_to(move);
	int piece = get_move_piece(move);
	int capture = get_move_capture(move);


	if (!capture) {

		pop_bit(b2[piece], source);
		set_bit(b2[piece], target);
	}

	else {

		pop_bit(b2[piece], source);
		set_bit(b2[piece], target);


		pop_bit(b2[capture], target);
	}
}

void undo_move(U64 b2[13], U64 move, int colour) {

	int source = get_move_from(move);
	int target = get_move_to(move);
	int piece = get_move_piece(move);
	int capture = get_move_capture(move);



	if (colour) {

		if (!capture) {

			pop_bit(b2[piece], target);
			set_bit(b2[piece], source);
		}

		else {
			pop_bit(b2[piece], target);
			set_bit(b2[piece], source);

			set_bit(b2[capture], target);
		}
	}


	else {

		if (!capture) {

			pop_bit(b2[piece], target);
			set_bit(b2[piece], source);
		}

		else {

			pop_bit(b2[piece], target);
			set_bit(b2[piece], source);

			set_bit(b2[capture], target);
		}
	}
}