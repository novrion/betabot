#include "moves.h"
using namespace std;


// Add Moves
static inline void AddMove(U64 moves[100], const U64 move) {
	moves[moves[99]++] = move;
}


// Generate Moves
void generate_moves(const U64 bb[13], U64 moves[100], bool side) {

	U64 w_block = _w_block(bb);
	U64 b_block = _b_block(bb);


	if (side) {

		U64 pieceBitboard = bb[1];
		while (pieceBitboard) w_pawn_moves(pop_lsb(pieceBitboard), w_block, b_block, moves, get_utility_en_passant(bb[0]));
		pieceBitboard = bb[2];
		while (pieceBitboard) w_knight_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[3];
		while (pieceBitboard) w_bishop_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[4];
		while (pieceBitboard) w_rook_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[5];
		while (pieceBitboard) w_queen_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[6];
		while (pieceBitboard) w_king_moves(pop_lsb(pieceBitboard), w_block, b_block, moves, bb);
	}

	else {

		U64 pieceBitboard = bb[7];
		while (pieceBitboard) b_pawn_moves(pop_lsb(pieceBitboard), w_block, b_block, moves, get_utility_en_passant(bb[0]));
		pieceBitboard = bb[8];
		while (pieceBitboard) b_knight_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[9];
		while (pieceBitboard) b_bishop_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[10];
		while (pieceBitboard) b_rook_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[11];
		while (pieceBitboard) b_queen_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[12];
		while (pieceBitboard) b_king_moves(pop_lsb(pieceBitboard), w_block, b_block, moves, bb);
	}

	/*
		if (side) {

			for (int square = 0; square < 64; ++square) {

				if (!(w_block & 1ULL << square)) continue;

				else if (bb[1] & 1ULL << square) w_pawn_moves(square, w_block, b_block, moves);
				else if (bb[2] & 1ULL << square) w_knight_moves(square, w_block, b_block, moves);
				else if (bb[3] & 1ULL << square) w_bishop_moves(square, w_block, b_block, moves);
				else if (bb[4] & 1ULL << square) w_rook_moves(square, w_block, b_block, moves);
				else if (bb[5] & 1ULL << square) w_queen_moves(square, w_block, b_block, moves);
				else if (bb[6] & 1ULL << square) w_king_moves(square, w_block, b_block, moves);
			}
		}

		else {

			for (int square = 0; square < 64; ++square) {

				if (!(b_block & 1ULL << square)) continue;

				else if (bb[7] & 1ULL << square) b_pawn_moves(square, w_block, b_block, moves);
				else if (bb[8] & 1ULL << square) b_knight_moves(square, w_block, b_block, moves);
				else if (bb[9] & 1ULL << square) b_bishop_moves(square, w_block, b_block, moves);
				else if (bb[10] & 1ULL << square) b_rook_moves(square, w_block, b_block, moves);
				else if (bb[11] & 1ULL << square) b_queen_moves(square, w_block, b_block, moves);
				else if (bb[12] & 1ULL << square) b_king_moves(square, w_block, b_block, moves);
			}
		}*/

}
void generate_captures(const U64 bb[13], U64 moves[100], bool side) {

	U64 w_block = _w_block(bb);
	U64 b_block = _b_block(bb);

	if (side) {

		for (int square = 0; square < 64; ++square) {

			if (!(w_block & 1ULL << square)) continue;

			else if (bb[1] & 1ULL << square) w_pawn_captures(square, w_block, b_block, moves, get_utility_en_passant(bb[0]));
			else if (bb[2] & 1ULL << square) w_knight_captures(square, w_block, b_block, moves);
			else if (bb[3] & 1ULL << square) w_bishop_captures(square, w_block, b_block, moves);
			else if (bb[4] & 1ULL << square) w_rook_captures(square, w_block, b_block, moves);
			else if (bb[5] & 1ULL << square) w_queen_captures(square, w_block, b_block, moves);
			else if (bb[6] & 1ULL << square) w_king_captures(square, w_block, b_block, moves);
		}
	}

	else {

		for (int square = 0; square < 64; ++square) {

			if (!(b_block & 1ULL << square)) continue;

			else if (bb[7] & 1ULL << square) b_pawn_captures(square, w_block, b_block, moves, get_utility_en_passant(bb[0]));
			else if (bb[8] & 1ULL << square) b_knight_captures(square, w_block, b_block, moves);
			else if (bb[9] & 1ULL << square) b_bishop_captures(square, w_block, b_block, moves);
			else if (bb[10] & 1ULL << square) b_rook_captures(square, w_block, b_block, moves);
			else if (bb[11] & 1ULL << square) b_queen_captures(square, w_block, b_block, moves);
			else if (bb[12] & 1ULL << square) b_king_captures(square, w_block, b_block, moves);
		}
	}
}


// Moves
static inline void w_pawn_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square) {
	U64 bitboard = 1ULL << square;

	int rank = square / 8;


	if (rank == 1) {

		if (!((bitboard >> 8) & (w_block | b_block))) AddMove(moves, encode_move(square, (square - 8), 1, 0, 5, 0, 0, 0));

		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) AddMove(moves, encode_move(square, (square - 7), 1, 1, 5, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) AddMove(moves, encode_move(square, (square - 9), 1, 1, 5, 0, 0, 0));
	}

	else {

		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) AddMove(moves, encode_move(square, (square - 7), 1, 1, 0, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) AddMove(moves, encode_move(square, (square - 9), 1, 1, 0, 0, 0, 0));

		if (!((bitboard >> 8) & (w_block | b_block))) {
			AddMove(moves, encode_move(square, (square - 8), 1, 0, 0, 0, 0, 0));
			if (rank == 6 && !((bitboard >> 16) & (w_block | b_block))) AddMove(moves, encode_move(square, (square - 16), 1, 0, 0, 1, 0, 0));
		}

		// En Passant
		if (en_passant_square && rank == 2) {

			if (en_passant_square == square - 1) AddMove(moves, encode_move(square, (square - 9), 1, 0, 0, 0, 1, 0));
			else if (en_passant_square == square + 1) AddMove(moves, encode_move(square, (square - 7), 1, 0, 0, 0, 1, 0));
		}
	}
}
static inline void w_knight_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & w_block)) {
		if (bitboard >> 6 & b_block) AddMove(moves, encode_move(square, (square - 6), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 6), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & w_block)) {
		if (bitboard >> 10 & b_block) AddMove(moves, encode_move(square, (square - 10), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 10), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & w_block)) {
		if (bitboard >> 15 & b_block) AddMove(moves, encode_move(square, (square - 15), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 15), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & w_block)) {
		if (bitboard >> 17 & b_block) AddMove(moves, encode_move(square, (square - 17), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 17), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & w_block)) {
		if (bitboard << 6 & b_block) AddMove(moves, encode_move(square, (square + 6), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 6), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & w_block)) {
		if (bitboard << 10 & b_block) AddMove(moves, encode_move(square, (square + 10), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 10), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & w_block)) {
		if (bitboard << 15 & b_block) AddMove(moves, encode_move(square, (square + 15), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 15), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & w_block)) {
		if (bitboard << 17 & b_block) AddMove(moves, encode_move(square, (square + 17), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 17), 2, 0, 0, 0, 0, 0));
	}
}
static inline void w_bishop_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}
}
static inline void w_rook_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 4, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 4, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 4, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 4, 0, 0, 0, 0, 0));
	}
}
static inline void w_queen_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 5, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 5, 0, 0, 0, 0, 0));
	}
}
static inline void w_king_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const U64 bb[13]) {
	U64 bitboard = 1ULL << square;

	bool w_castle = get_utility_w_castle(bb[0]);
	bool w_king = get_utility_w_king(bb[0]);
	bool w_l_rook = get_utility_w_l_rook(bb[0]);
	bool w_r_rook = get_utility_w_r_rook(bb[0]);


	if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & w_block)) {
		if (bitboard >> 7 & b_block) AddMove(moves, encode_move(square, (square - 7), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 7), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 8) && !(bitboard >> 8 & w_block)) {
		if (bitboard >> 8 & b_block) AddMove(moves, encode_move(square, (square - 8), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 8), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & w_block)) {
		if (bitboard >> 9 & b_block) AddMove(moves, encode_move(square, (square - 9), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 9), 6, 0, 0, 0, 0, 0));
	}


	if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & w_block)) {
		if (bitboard >> 1 & b_block) AddMove(moves, encode_move(square, (square - 1), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 1), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & w_block)) {
		if (bitboard << 1 & b_block) AddMove(moves, encode_move(square, (square + 1), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 1), 6, 0, 0, 0, 0, 0));
	}


	if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & w_block)) {
		if (bitboard << 7 & b_block) AddMove(moves, encode_move(square, (square + 7), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 7), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 8) && !(bitboard << 8 & w_block)) {
		if (bitboard << 8 & b_block) AddMove(moves, encode_move(square, (square + 8), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 8), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & w_block)) {
		if (bitboard << 9 & b_block) AddMove(moves, encode_move(square, (square + 9), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 9), 6, 0, 0, 0, 0, 0));
	}


	// Castle
	if (!w_castle && !w_king) {

		if (!(w_castle_short_space_mask & (w_block | b_block)) && !w_r_rook && !(bb[7] & w_castle_short_pawn_mask) && !(bb[8] & w_castle_short_knight_mask) && !(bb[12] & w_castle_short_king_mask)) {
			
			bool can_castle = true;

			for (int square = 60; square < 63; ++square) {

				int t_rank = square / 8;
				int t_file = square % 8;

				for (int x = t_rank - 1, y = t_file - 1; t_rank > -1 && t_file > -1; --t_rank, --t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[9] | bb[11])) can_castle = false;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}

				for (int x = t_rank - 1; t_rank > -1; --t_rank) {

					if (1ULL << (x * 8 + t_file) & w_block) break;
					else if (1ULL << (x * 8 + t_file) & bb[10]) can_castle = false;
					else if (1ULL << (x * 8 + t_file) & b_block) break;

				}

				for (int x = t_rank - 1, y = t_file + 1; t_rank > -1 && t_file < 8; --t_rank, ++t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[9] | bb[11])) can_castle = false;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}
			}

			if (can_castle) {
				AddMove(moves, encode_move(60, 62, 6, 0, 0, 0, 0, 1));
			}
		}

		if (!(w_castle_long_space_mask & (w_block | b_block)) && !w_l_rook && !(bb[7] & w_castle_long_pawn_mask) && !(bb[8] & w_castle_long_knight_mask) && !(bb[12] & w_castle_long_king_mask)) {

			for (int square = 60; square > 56; --square) {

				int t_rank = square / 8;
				int t_file = square % 8;

				for (int x = t_rank - 1, y = t_file - 1; t_rank > -1 && t_file > -1; --t_rank, --t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[9] | bb[11])) return;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}

				for (int x = t_rank - 1; t_rank > -1; --t_rank) {

					if (1ULL << (x * 8 + t_file) & w_block) break;
					else if (1ULL << (x * 8 + t_file) & bb[10]) return;
					else if (1ULL << (x * 8 + t_file) & b_block) break;
				}

				for (int x = t_rank - 1, y = t_file + 1; t_rank > -1 && t_file < 8; --t_rank, ++t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[9] | bb[11])) return;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}
			}

			AddMove(moves, encode_move(60, 58, 6, 0, 0, 0, 0, 1));
		}
	}
}

static inline void b_pawn_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square) {

	U64 bitboard = 1ULL << square;

	int rank = square / 8;


	if (rank == 6) {
		if (!((bitboard << 8) & (w_block | b_block))) AddMove(moves, encode_move(square, (square + 8), 7, 0, 11, 0, 0, 0));

		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) AddMove(moves, encode_move(square, (square + 7), 7, 1, 11, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) AddMove(moves, encode_move(square, (square + 9), 7, 1, 11, 0, 0, 0));
	}

	else {

		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) AddMove(moves, encode_move(square, (square + 7), 7, 1, 0, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) AddMove(moves, encode_move(square, (square + 9), 7, 1, 0, 0, 0, 0));

		if (!((bitboard << 8) & (w_block | b_block))) {

			AddMove(moves, encode_move(square, (square + 8), 7, 0, 0, 0, 0, 0));
			if (rank == 1 && !((bitboard << 16) & (w_block | b_block))) AddMove(moves, encode_move(square, (square + 16), 7, 0, 0, 1, 0, 0));
		}

		// En Passant
		if (en_passant_square && rank == 5) {

			if (en_passant_square == square - 1) AddMove(moves, encode_move(square, (square + 7), 7, 0, 0, 0, 1, 0));
			else if (en_passant_square == square + 1) AddMove(moves, encode_move(square, (square + 9), 7, 0, 0, 0, 1, 0));
		}
	}
}
static inline void b_knight_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & b_block)) {
		if (bitboard >> 6 & w_block) AddMove(moves, encode_move(square, (square - 6), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 6), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & b_block)) {
		if (bitboard >> 10 & w_block) AddMove(moves, encode_move(square, (square - 10), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 10), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & b_block)) {
		if (bitboard >> 15 & w_block) AddMove(moves, encode_move(square, (square - 15), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 15), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & b_block)) {
		if (bitboard >> 17 & w_block) AddMove(moves, encode_move(square, (square - 17), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 17), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & b_block)) {
		if (bitboard << 6 & w_block) AddMove(moves, encode_move(square, (square + 6), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 6), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & b_block)) {
		if (bitboard << 10 & w_block) AddMove(moves, encode_move(square, (square + 10), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 10), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & b_block)) {
		if (bitboard << 15 & w_block) AddMove(moves, encode_move(square, (square + 15), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 15), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & b_block)) {
		if (bitboard << 17 & w_block) AddMove(moves, encode_move(square, (square + 17), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 17), 8, 0, 0, 0, 0, 0));
	}
}
static inline void b_bishop_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}
}
static inline void b_rook_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 10, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 10, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 10, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 10, 0, 0, 0, 0, 0));
	}
}
static inline void b_queen_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 11, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (y * 8 + t_file), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, encode_move(square, (t_rank * 8 + x), 11, 0, 0, 0, 0, 0));
	}
}
static inline void b_king_moves(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const U64 bb[13]) {
	U64 bitboard = 1ULL << square;

	bool b_castle = get_utility_b_castle(bb[0]);
	bool b_king = get_utility_b_king(bb[0]);
	bool b_l_rook = get_utility_b_l_rook(bb[0]);
	bool b_r_rook = get_utility_b_r_rook(bb[0]);


	if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & b_block)) {
		if (bitboard >> 7 & w_block) AddMove(moves, encode_move(square, (square - 7), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 7), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 8) && !(bitboard >> 8 & b_block)) {
		if (bitboard >> 8 & w_block) AddMove(moves, encode_move(square, (square - 8), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 8), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & b_block)) {
		if (bitboard >> 9 & w_block) AddMove(moves, encode_move(square, (square - 9), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 9), 12, 0, 0, 0, 0, 0));
	}


	if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & b_block)) {
		if (bitboard >> 1 & w_block) AddMove(moves, encode_move(square, (square - 1), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square - 1), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & b_block)) {
		if (bitboard << 1 & w_block) AddMove(moves, encode_move(square, (square + 1), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 1), 12, 0, 0, 0, 0, 0));
	}


	if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & b_block)) {
		if (bitboard << 7 & w_block) AddMove(moves, encode_move(square, (square + 7), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 7), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 8) && !(bitboard << 8 & b_block)) {
		if (bitboard << 8 & w_block) AddMove(moves, encode_move(square, (square + 8), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 8), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & b_block)) {
		if (bitboard << 9 & w_block) AddMove(moves, encode_move(square, (square + 9), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, encode_move(square, (square + 9), 12, 0, 0, 0, 0, 0));
	}


	// Castle
	if (!b_castle && !b_king) {

		if (!(b_castle_short_space_mask & (w_block | b_block)) && !b_r_rook && !(bb[1] & b_castle_short_pawn_mask) && !(bb[2] & b_castle_short_knight_mask) && !(bb[6] & w_castle_short_king_mask)) {

			bool can_castle = true;

			for (int square = 4; square < 7; ++square) {

				int t_rank = square / 8;
				int t_file = square % 8;

				for (int x = t_rank + 1, y = t_file - 1; t_rank < 8 && t_file > -1; ++t_rank, --t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[3] | bb[5])) can_castle = false;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}

				for (int x = t_rank + 1; t_rank < 8; ++t_rank) {

					if (1ULL << (x * 8 + t_file) & w_block) break;
					else if (1ULL << (x * 8 + t_file) & bb[4]) can_castle = false;
					else if (1ULL << (x * 8 + t_file) & b_block) break;

				}

				for (int x = t_rank + 1, y = t_file + 1; t_rank < 8 && t_file < 8; ++t_rank, ++t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[3] | bb[5])) can_castle = false;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}
			}

			if (can_castle) AddMove(moves, encode_move(4, 6, 12, 0, 0, 0, 0, 1));
		}

		if (!(b_castle_long_space_mask & (w_block | b_block)) && !b_l_rook && !(bb[1] & b_castle_long_pawn_mask) && !(bb[2] & b_castle_long_knight_mask) && !(bb[6] & w_castle_long_king_mask)) {

			for (int square = 4; square > 0; --square) {

				int t_rank = square / 8;
				int t_file = square % 8;

				for (int x = t_rank + 1, y = t_file - 1; t_rank < 8 && t_file > -1; ++t_rank, --t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[9] | bb[11])) return;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}

				for (int x = t_rank + 1; t_rank < 8; ++t_rank) {

					if (1ULL << (x * 8 + t_file) & w_block) break;
					else if (1ULL << (x * 8 + t_file) & bb[10]) return;
					else if (1ULL << (x * 8 + t_file) & b_block) break;
				}

				for (int x = t_rank + 1, y = t_file + 1; t_rank < 8 && t_file < 8; ++t_rank, ++t_file) {

					if (1ULL << (x * 8 + y) & w_block) break;
					else if (1ULL << (x * 8 + y) & (bb[9] | bb[11])) return;
					else if (1ULL << (x * 8 + y) & b_block) break;
				}
			}

			AddMove(moves, encode_move(4, 2, 12, 0, 0, 0, 0, 1));
		}
	}
}


static inline void w_pawn_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square) {
	U64 bitboard = 1ULL << square;

	int rank = square / 8;


	if (rank == 1) {
		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) AddMove(moves, encode_move(square, (square - 7), 1, 1, 5, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) AddMove(moves, encode_move(square, (square - 9), 1, 1, 5, 0, 0, 0));
	}

	else {

		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) AddMove(moves, encode_move(square, (square - 7), 1, 1, 0, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) AddMove(moves, encode_move(square, (square - 9), 1, 1, 0, 0, 0, 0));

		// En Passant
		if (en_passant_square && rank == 2) {

			if (en_passant_square == square - 1) AddMove(moves, encode_move(square, (square - 9), 1, 0, 0, 0, 1, 0));
			else if (en_passant_square == square + 1) AddMove(moves, encode_move(square, (square - 7), 1, 0, 0, 0, 1, 0));
		}
	}
}
static inline void w_knight_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 6 & not_ab_file & b_block) AddMove(moves, encode_move(square, (square - 6), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 10 & not_gh_file & b_block) AddMove(moves, encode_move(square, (square - 10), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 15 & not_a_file & b_block) AddMove(moves, encode_move(square, (square - 15), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 17 & not_h_file & b_block) AddMove(moves, encode_move(square, (square - 17), 2, 1, 0, 0, 0, 0));

	if (bitboard << 6 & not_gh_file & b_block) AddMove(moves, encode_move(square, (square + 6), 2, 1, 0, 0, 0, 0));
	if (bitboard << 10 & not_ab_file & b_block) AddMove(moves, encode_move(square, (square + 10), 2, 1, 0, 0, 0, 0));
	if (bitboard << 15 & not_h_file & b_block) AddMove(moves, encode_move(square, (square + 15), 2, 1, 0, 0, 0, 0));
	if (bitboard << 17 & not_a_file & b_block) AddMove(moves, encode_move(square, (square + 17), 2, 1, 0, 0, 0, 0));
}
static inline void w_bishop_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

}
static inline void w_rook_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void w_queen_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void w_king_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 7 & not_a_file & b_block) AddMove(moves, encode_move(square, (square - 7), 6, 1, 0, 0, 0, 0));
	if (bitboard >> 8 & b_block) AddMove(moves, encode_move(square, (square - 8), 6, 1, 0, 0, 0, 0));
	if (bitboard >> 9 & not_h_file & b_block) AddMove(moves, encode_move(square, (square - 9), 6, 1, 0, 0, 0, 0));

	if (bitboard >> 1 & not_h_file & b_block) AddMove(moves, encode_move(square, (square - 1), 6, 1, 0, 0, 0, 0));
	if (bitboard << 1 & not_a_file & b_block) AddMove(moves, encode_move(square, (square + 1), 6, 1, 0, 0, 0, 0));

	if (bitboard << 7 & not_h_file & b_block) AddMove(moves, encode_move(square, (square + 7), 6, 1, 0, 0, 0, 0));
	if (bitboard << 8 & b_block) AddMove(moves, encode_move(square, (square + 8), 6, 1, 0, 0, 0, 0));
	if (bitboard << 9 & not_a_file & b_block) AddMove(moves, encode_move(square, (square + 9), 6, 1, 0, 0, 0, 0));
}

static inline void b_pawn_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100], const int en_passant_square) {
	U64 bitboard = 1ULL << square;

	int rank = square / 8;


	if (rank == 6) {
		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) AddMove(moves, encode_move(square, (square + 7), 7, 1, 11, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) AddMove(moves, encode_move(square, (square + 9), 7, 1, 11, 0, 0, 0));
	}

	else {

		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) AddMove(moves, encode_move(square, (square + 7), 7, 1, 0, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) AddMove(moves, encode_move(square, (square + 9), 7, 1, 0, 0, 0, 0));

		// En Passant
		if (en_passant_square && rank == 5) {

			if (en_passant_square == square - 1) AddMove(moves, encode_move(square, (square + 7), 7, 0, 0, 0, 1, 0));
			else if (en_passant_square == square + 1) AddMove(moves, encode_move(square, (square + 9), 7, 0, 0, 0, 1, 0));
		}
	}
}
static inline void b_knight_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 6 & not_ab_file & w_block) AddMove(moves, encode_move(square, (square - 6), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 10 & not_gh_file & w_block) AddMove(moves, encode_move(square, (square - 10), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 15 & not_a_file & w_block) AddMove(moves, encode_move(square, (square - 15), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 17 & not_h_file & w_block) AddMove(moves, encode_move(square, (square - 17), 8, 1, 0, 0, 0, 0));

	if (bitboard << 6 & not_gh_file & w_block) AddMove(moves, encode_move(square, (square + 6), 8, 1, 0, 0, 0, 0));
	if (bitboard << 10 & not_ab_file & w_block) AddMove(moves, encode_move(square, (square + 10), 8, 1, 0, 0, 0, 0));
	if (bitboard << 15 & not_h_file & w_block) AddMove(moves, encode_move(square, (square + 15), 8, 1, 0, 0, 0, 0));
	if (bitboard << 17 & not_a_file & w_block) AddMove(moves, encode_move(square, (square + 17), 8, 1, 0, 0, 0, 0));
}
static inline void b_bishop_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void b_rook_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void b_queen_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			AddMove(moves, encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			AddMove(moves, encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			AddMove(moves, encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void b_king_captures(const int square, const U64 w_block, const U64 b_block, U64 moves[100]) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 7 & not_a_file & w_block) AddMove(moves, encode_move(square, (square - 7), 12, 1, 0, 0, 0, 0));
	if (bitboard >> 8 & w_block) AddMove(moves, encode_move(square, (square - 8), 12, 1, 0, 0, 0, 0));
	if (bitboard >> 9 & not_h_file & w_block) AddMove(moves, encode_move(square, (square - 9), 12, 1, 0, 0, 0, 0));

	if (bitboard >> 1 & not_h_file & w_block) AddMove(moves, encode_move(square, (square - 1), 12, 1, 0, 0, 0, 0));
	if (bitboard << 1 & not_a_file & w_block) AddMove(moves, encode_move(square, (square + 1), 12, 1, 0, 0, 0, 0));

	if (bitboard << 7 & not_h_file & w_block) AddMove(moves, encode_move(square, (square + 7), 12, 1, 0, 0, 0, 0));
	if (bitboard << 8 & w_block) AddMove(moves, encode_move(square, (square + 8), 12, 1, 0, 0, 0, 0));
	if (bitboard << 9 & not_a_file & w_block) AddMove(moves, encode_move(square, (square + 9), 12, 1, 0, 0, 0, 0));
}