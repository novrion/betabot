#include "beta.h"
using namespace std;
using namespace std::chrono;

const U64 capture_mask = 8388607ULL;



void gen_moves(U64 b2[13], int colour, vector<U64>& moves) {

	//duration<double> time;
	//time_point<chrono::high_resolution_clock> start_time;
	//start_time = high_resolution_clock::now();

	U64 w_block = _w_block(b2);
	U64 b_block = _b_block(b2);
	int square = 0;

	if (colour) {

		U64 w_piece = w_block;
		while (w_piece) {

			square = countr_zero(w_piece);
			pop_bit(w_piece, square);

			if (b2[1] & 1ULL << square) {
				pawn_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[2] & 1ULL << square) {
				knight_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[3] & 1ULL << square) {
				bishop_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[4] & 1ULL << square) {
				rook_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[5] & 1ULL << square) {
				queen_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[6] & 1ULL << square) {
				king_moves(square, colour, w_block, b_block, moves);
			}
		}
	}

	else {

		U64 b_piece = b_block;
		while (b_piece) {

			square = countr_zero(b_piece);
			pop_bit(b_piece, square);

			if (b2[7] & 1ULL << square) {
				pawn_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[8] & 1ULL << square) {
				knight_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[9] & 1ULL << square) {
				bishop_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[10] & 1ULL << square) {
				rook_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[11] & 1ULL << square) {
				queen_moves(square, colour, w_block, b_block, moves);
			}

			else if (b2[12] & 1ULL << square) {
				king_moves(square, colour, w_block, b_block, moves);
			}
		}
	}

	//time = high_resolution_clock::now() - start_time;
	//cout << time.count() << "\n";
}

void gen_captures(U64 b2[13], int colour, vector<U64>& moves) {

	U64 w_block = _w_block(b2);
	U64 b_block = _b_block(b2);

	if (colour) {

		for (int square = 0; square < 64; ++square) {

			if (b2[1] & 1ULL << square) {
				pawn_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[2] & 1ULL << square) {
				knight_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[3] & 1ULL << square) {
				bishop_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[4] & 1ULL << square) {
				rook_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[5] & 1ULL << square) {
				queen_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[6] & 1ULL << square) {
				king_captures(square, colour, w_block, b_block, moves);
			}
		}
	}

	else {

		for (int square = 0; square < 64; ++square) {

			if (b2[7] & 1ULL << square) {
				pawn_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[8] & 1ULL << square) {
				knight_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[9] & 1ULL << square) {
				bishop_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[10] & 1ULL << square) {
				rook_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[11] & 1ULL << square) {
				queen_captures(square, colour, w_block, b_block, moves);
			}

			else if (b2[12] & 1ULL << square) {
				king_captures(square, colour, w_block, b_block, moves);
			}
		}
	}
}

void make_move(U64 b2[13], U64& move, int colour) {

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


		if (colour) {
			for (int i = 7; i < 13; ++i) {
				if (1ULL << target & b2[i]) {
					pop_bit(b2[i], target);
					move &= capture_mask;
					move |= (i << 23);
					return;
				}
			}
		}

		else {
			for (int i = 1; i < 7; ++i) {
				if (1ULL << target & b2[i]) {
					pop_bit(b2[i], target);
					move &= capture_mask;
					move |= (i << 23);
					return;
				}
			}
		}
	}
}

void undo_move(U64 b2[13], U64 move, int colour) {

	int source = get_move_from(move);
	int target = get_move_to(move);
	int piece = get_move_piece(move);
	int capture = get_move_capture(move);


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