#include "beta.h"
using namespace std;

const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;



void pawn_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if (square / 8 == 1) {
			if (!((bitboard >> 8) & w_block & b_block)) moves.insert(encode_move(b2, square, square - 8, 2, 0, 0, 9, 0, 0));

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.insert(encode_move(b2, square, square - 7, 0, 1, 6, 0, 0, 0));
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.insert(encode_move(b2, square, square - 9, 0, 1, 6, 0, 0, 0));
		}

		else {

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.insert(encode_move(b2, square, square - 7, 0, 1, 0, 0, 0, 0));
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.insert(encode_move(b2, square, square - 9, 0, 1, 0, 0, 0, 0));

			if (!((bitboard >> 8) & w_block) && !((bitboard >> 8) & b_block)) {

				moves.insert(encode_move(b2, square, square - 8, 0, 0, 0, 0, 0, 0));
				if (square / 8 == 6 && !((bitboard >> 16) & w_block) && !((bitboard >> 16) & b_block)) moves.insert(encode_move(b2, square, square - 16, 0, 0, 0, 1, 0, 0));
			}
		}
	}

	else {

		if (square / 8 == 6) {
			if (!((bitboard << 8) & w_block & b_block)) moves.insert(encode_move(b2, square, square + 8, 6, 0, -9, 0, 0, 0));

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.insert(encode_move(b2, square, square + 7, 6, 1, 12, 0, 0, 0));
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.insert(encode_move(b2, square, square + 9, 6, 1, 12, 0, 0, 0));
		}

		else {

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.insert(encode_move(b2, square, square + 7, 6, 1, 0, 0, 0, 0));
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.insert(encode_move(b2, square, square + 9, 6, 1, 0, 0, 0, 0));

			if (!((bitboard << 8) & w_block) && !((bitboard << 8) & b_block)) {

				moves.insert(encode_move(b2, square, square + 8, 6, 0, 0, 0, 0, 0));
				if (square / 8 == 1 && !((bitboard << 16) & w_block) && !((bitboard << 16) & b_block)) moves.insert(encode_move(b2, square, square + 16, 6, 0, 0, 1, 0, 0));
			}
		}
	}
}

void knight_moves (U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & w_block)) {
			if (bitboard >> 6 & b_block) moves.insert(encode_move(b2, square, square - 6, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 6, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & w_block)) {
			if (bitboard >> 10 & b_block) moves.insert(encode_move(b2, square, square - 10, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 10, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & w_block)) {
			if (bitboard >> 15 & b_block) moves.insert(encode_move(b2, square, square - 15, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 15, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & w_block)) {
			if (bitboard >> 17 & b_block) moves.insert(encode_move(b2, square, square - 17, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 17, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & w_block)) {
			if (bitboard << 6 & b_block) moves.insert(encode_move(b2, square, square + 6, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 6, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & w_block)) {
			if (bitboard << 10 & b_block) moves.insert(encode_move(b2, square, square + 10, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 10, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & w_block)) {
			if (bitboard << 15 & b_block) moves.insert(encode_move(b2, square, square + 15, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 15, 1, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & w_block)) {
			if (bitboard << 17 & b_block) moves.insert(encode_move(b2, square, square + 17, 1, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 17, 1, 0, 0, 0, 0, 0));
		}
	}

	else {

		if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & b_block)) {
			if (bitboard >> 6 & w_block) moves.insert(encode_move(b2, square, square - 6, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 6, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & b_block)) {
			if (bitboard >> 10 & w_block) moves.insert(encode_move(b2, square, square - 10, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 10, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & b_block)) {
			if (bitboard >> 15 & w_block) moves.insert(encode_move(b2, square, square - 15, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 15, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & b_block)) {
			if (bitboard >> 17 & w_block) moves.insert(encode_move(b2, square, square - 17, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 17, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & b_block)) {
			if (bitboard << 6 & w_block) moves.insert(encode_move(b2, square, square + 6, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 6, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & b_block)) {
			if (bitboard << 10 & w_block) moves.insert(encode_move(b2, square, square + 10, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 10, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & b_block)) {
			if (bitboard << 15 & w_block) moves.insert(encode_move(b2, square, square + 15, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 15, 7, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & b_block)) {
			if (bitboard << 17 & w_block) moves.insert(encode_move(b2, square, square + 17, 7, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 17, 7, 0, 0, 0, 0, 0));
		}
	}
}

void king_moves (U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & w_block)) {
			if (bitboard >> 7 & b_block) moves.insert(encode_move(b2, square, square - 7, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 7, 5, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 8) && !(bitboard >> 8 & w_block)) {
			if (bitboard >> 8 & b_block) moves.insert(encode_move(b2, square, square - 8, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 8, 5, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & w_block)) {
			if (bitboard >> 9 & b_block) moves.insert(encode_move(b2, square, square - 9, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 9, 5, 0, 0, 0, 0, 0));
		}


		if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & w_block)) {
			if (bitboard >> 1 & b_block) moves.insert(encode_move(b2, square, square - 1, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 1, 5, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & w_block)) {
			if (bitboard << 1 & b_block) moves.insert(encode_move(b2, square, square + 1, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 1, 5, 0, 0, 0, 0, 0));
		}


		if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & w_block)) {
			if (bitboard << 7 & b_block) moves.insert(encode_move(b2, square, square + 7, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 7, 5, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 8) && !(bitboard << 8 & w_block)) {
			if (bitboard << 8 & b_block) moves.insert(encode_move(b2, square, square + 8, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 8, 5, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & w_block)) {
			if (bitboard << 9 & b_block) moves.insert(encode_move(b2, square, square + 9, 5, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 9, 5, 0, 0, 0, 0, 0));
		}
	}

	else {

		if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & b_block)) {
			if (bitboard >> 7 & w_block) moves.insert(encode_move(b2, square, square - 7, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 7, 11, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 8) && !(bitboard >> 8 & b_block)) {
			if (bitboard >> 8 & w_block) moves.insert(encode_move(b2, square, square - 8, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 8, 11, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & b_block)) {
			if (bitboard >> 9 & w_block) moves.insert(encode_move(b2, square, square - 9, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 9, 11, 0, 0, 0, 0, 0));
		}


		if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & b_block)) {
			if (bitboard >> 1 & w_block) moves.insert(encode_move(b2, square, square - 1, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square - 1, 11, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & b_block)) {
			if (bitboard << 1 & w_block) moves.insert(encode_move(b2, square, square + 1, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 1, 11, 0, 0, 0, 0, 0));
		}


		if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & b_block)) {
			if (bitboard << 7 & w_block) moves.insert(encode_move(b2, square, square + 7, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 7, 11, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 8) && !(bitboard << 8 & b_block)) {
			if (bitboard << 8 & w_block) moves.insert(encode_move(b2, square, square + 8, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 8, 11, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & b_block)) {
			if (bitboard << 9 & w_block) moves.insert(encode_move(b2, square, square + 9, 11, 1, 0, 0, 0, 0));
			else moves.insert(encode_move(b2, square, square + 9, 11, 0, 0, 0, 0, 0));
		}
	}
}


void bishop_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 2, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 2, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 2, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 2, 0, 0, 0, 0, 0));
		}
	}

	else {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 8, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 8, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 8, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 8, 0, 0, 0, 0, 0));
		}
	}
}

void rook_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 3, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 3, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 3, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 3, 0, 0, 0, 0, 0));
		}
	}

	else {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 9, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 9, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 9, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 9, 0, 0, 0, 0, 0));
		}
	}
}

void queen_moves(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 4, 0, 0, 0, 0, 0));
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 4, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 4, 0, 0, 0, 0, 0));
		}
	}

	else {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, x * 8 + y, 10, 0, 0, 0, 0, 0));
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 10, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, y * 8 + t_file, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.insert(encode_move(b2, square, t_rank * 8 + x, 10, 0, 0, 0, 0, 0));
		}
	}
}





void pawn_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if (square / 8 == 1) {
			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.insert(encode_move(b2, square, square - 7, 0, 1, 6, 0, 0, 0));
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.insert(encode_move(b2, square, square - 9, 0, 1, 6, 0, 0, 0));
		}

		else {

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.insert(encode_move(b2, square, square - 7, 0, 1, 0, 0, 0, 0));
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.insert(encode_move(b2, square, square - 9, 0, 1, 0, 0, 0, 0));
		}
	}

	else {

		if (square / 8 == 6) {
			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.insert(encode_move(b2, square, square + 7, 6, 1, 12, 0, 0, 0));
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.insert(encode_move(b2, square, square + 9, 6, 1, 12, 0, 0, 0));
		}

		else {

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.insert(encode_move(b2, square, square + 7, 6, 1, 0, 0, 0, 0));
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.insert(encode_move(b2, square, square + 9, 6, 1, 0, 0, 0, 0));
		}
	}
}

void knight_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if (bitboard >> 6 & not_ab_file & b_block) moves.insert(encode_move(b2, square, square - 6, 1, 1, 0, 0, 0, 0));
		if (bitboard >> 10 & not_gh_file & b_block) moves.insert(encode_move(b2, square, square - 10, 1, 1, 0, 0, 0, 0));
		if (bitboard >> 15 & not_a_file & b_block) moves.insert(encode_move(b2, square, square - 15, 1, 1, 0, 0, 0, 0));
		if (bitboard >> 17 & not_h_file & b_block) moves.insert(encode_move(b2, square, square - 17, 1, 1, 0, 0, 0, 0));

		if (bitboard << 6 & not_gh_file & b_block) moves.insert(encode_move(b2, square, square + 6, 1, 1, 0, 0, 0, 0));
		if (bitboard << 10 & not_ab_file & b_block) moves.insert(encode_move(b2, square, square + 10, 1, 1, 0, 0, 0, 0));
		if (bitboard << 15 & not_h_file & b_block) moves.insert(encode_move(b2, square, square + 15, 1, 1, 0, 0, 0, 0));
		if (bitboard << 17 & not_a_file & b_block) moves.insert(encode_move(b2, square, square + 17, 1, 1, 0, 0, 0, 0));
	}

	else {

		if (bitboard >> 6 & not_ab_file & w_block) moves.insert(encode_move(b2, square, square - 6, 7, 1, 0, 0, 0, 0));
		if (bitboard >> 10 & not_gh_file & w_block) moves.insert(encode_move(b2, square, square - 10, 7, 1, 0, 0, 0, 0));
		if (bitboard >> 15 & not_a_file & w_block) moves.insert(encode_move(b2, square, square - 15, 7, 1, 0, 0, 0, 0));
		if (bitboard >> 17 & not_h_file & w_block) moves.insert(encode_move(b2, square, square - 17, 7, 1, 0, 0, 0, 0));

		if (bitboard << 6 & not_gh_file & w_block) moves.insert(encode_move(b2, square, square + 6, 7, 1, 0, 0, 0, 0));
		if (bitboard << 10 & not_ab_file & w_block) moves.insert(encode_move(b2, square, square + 10, 7, 1, 0, 0, 0, 0));
		if (bitboard << 15 & not_h_file & w_block) moves.insert(encode_move(b2, square, square + 15, 7, 1, 0, 0, 0, 0));
		if (bitboard << 17 & not_a_file & w_block) moves.insert(encode_move(b2, square, square + 17, 7, 1, 0, 0, 0, 0));
	}
}

void king_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if (bitboard >> 7 & not_a_file & b_block) moves.insert(encode_move(b2, square, square - 7, 5, 1, 0, 0, 0, 0));
		if (bitboard >> 8 & b_block) moves.insert(encode_move(b2, square, square - 8, 5, 1, 0, 0, 0, 0));
		if (bitboard >> 9 & not_h_file & b_block) moves.insert(encode_move(b2, square, square - 9, 5, 1, 0, 0, 0, 0));

		if (bitboard >> 1 & not_h_file & b_block) moves.insert(encode_move(b2, square, square - 1, 5, 1, 0, 0, 0, 0));
		if (bitboard << 1 & not_a_file & b_block) moves.insert(encode_move(b2, square, square + 1, 5, 1, 0, 0, 0, 0));

		if (bitboard << 7 & not_h_file & b_block) moves.insert(encode_move(b2, square, square + 7, 5, 1, 0, 0, 0, 0));
		if (bitboard << 8 & b_block) moves.insert(encode_move(b2, square, square + 8, 5, 1, 0, 0, 0, 0));
		if (bitboard << 9 & not_a_file & b_block) moves.insert(encode_move(b2, square, square + 9, 5, 1, 0, 0, 0, 0));
	}

	else {

		if (bitboard >> 7 & not_a_file & w_block) moves.insert(encode_move(b2, square, square - 7, 11, 1, 0, 0, 0, 0));
		if (bitboard >> 8 & w_block) moves.insert(encode_move(b2, square, square - 8, 11, 1, 0, 0, 0, 0));
		if (bitboard >> 9 & not_h_file & w_block) moves.insert(encode_move(b2, square, square - 9, 11, 1, 0, 0, 0, 0));

		if (bitboard >> 1 & not_h_file & w_block) moves.insert(encode_move(b2, square, square - 1, 11, 1, 0, 0, 0, 0));
		if (bitboard << 1 & not_a_file & w_block) moves.insert(encode_move(b2, square, square + 1, 11, 1, 0, 0, 0, 0));

		if (bitboard << 7 & not_h_file & w_block) moves.insert(encode_move(b2, square, square + 7, 11, 1, 0, 0, 0, 0));
		if (bitboard << 8 & w_block) moves.insert(encode_move(b2, square, square + 8, 11, 1, 0, 0, 0, 0));
		if (bitboard << 9 & not_a_file & w_block) moves.insert(encode_move(b2, square, square + 9, 11, 1, 0, 0, 0, 0));
	}
}


void bishop_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 2, 1, 0, 0, 0, 0));
				break;
			}
		}
	}

	else {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 8, 1, 0, 0, 0, 0));
				break;
			}
		}
	}
}

void rook_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 3, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 3, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 3, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 3, 1, 0, 0, 0, 0));
				break;
			}
		}
	}

	else {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 9, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 9, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 9, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 9, 1, 0, 0, 0, 0));
				break;
			}
		}
	}
}

void queen_captures(U64 b2[13], int square, int colour, U64 w_block, U64 b_block, set<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 4, 1, 0, 0, 0, 0));
				break;
			}
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 4, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 4, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0));
				break;
			}
		}
	}

	else {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.insert(encode_move(b2, square, x * 8 + y, 10, 1, 0, 0, 0, 0));
				break;
			}
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 10, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.insert(encode_move(b2, square, y * 8 + t_file, 10, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0));
				break;
			}
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.insert(encode_move(b2, square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0));
				break;
			}
		}
	}
}