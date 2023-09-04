#include "moves.h"
using namespace std;
using namespace std::chrono;


static inline int pop_lsb(U64& b) {

	const int s = countr_zero(b);
	b &= b - 1;
	return s;
}


vector<U64> generate_moves(const U64 bb[13], bool side) {

	vector<U64> moves;

	U64 w_block = _w_block(bb);
	U64 b_block = _b_block(bb);


	if (side) {

		U64 pieceBitboard = bb[1];
		while (pieceBitboard) w_pawn_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[2];
		while (pieceBitboard) w_knight_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[3];
		while (pieceBitboard) w_bishop_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[4];
		while (pieceBitboard) w_rook_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[5];
		while (pieceBitboard) w_queen_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[6];
		while (pieceBitboard) w_king_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
	}
	
	else {

		U64 pieceBitboard = bb[7];
		while (pieceBitboard) b_pawn_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[8];
		while (pieceBitboard) b_knight_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[9];
		while (pieceBitboard) b_bishop_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[10];
		while (pieceBitboard) b_rook_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[11];
		while (pieceBitboard) b_queen_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
		pieceBitboard = bb[12];
		while (pieceBitboard) b_king_moves(pop_lsb(pieceBitboard), w_block, b_block, moves);
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


	return moves;
}
vector<U64> generate_captures(const U64 bb[13], bool side) {

	vector<U64> moves;

	U64 w_block = _w_block(bb);
	U64 b_block = _b_block(bb);

	if (side) {

		for (int square = 0; square < 64; ++square) {

			if (!(w_block & 1ULL << square)) continue;

			else if (bb[1] & 1ULL << square) w_pawn_captures(square, w_block, b_block, moves);
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

			else if (bb[7] & 1ULL << square) b_pawn_captures(square, w_block, b_block, moves);
			else if (bb[8] & 1ULL << square) b_knight_captures(square, w_block, b_block, moves);
			else if (bb[9] & 1ULL << square) b_bishop_captures(square, w_block, b_block, moves);
			else if (bb[10] & 1ULL << square) b_rook_captures(square, w_block, b_block, moves);
			else if (bb[11] & 1ULL << square) b_queen_captures(square, w_block, b_block, moves);
			else if (bb[12] & 1ULL << square) b_king_captures(square, w_block, b_block, moves);
		}
	}

	return moves;
}

// Promotion
// En Passant
// Castle
static inline void w_pawn_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (square / 8 == 1) {

		if (!((bitboard >> 8) & (w_block | b_block))) moves.emplace_back(encode_move(square, (square - 8), 1, 0, 5, 0, 0, 0));

		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.emplace_back(encode_move(square, (square - 7), 1, 1, 5, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.emplace_back(encode_move(square, (square - 9), 1, 1, 5, 0, 0, 0));
	}

	else {

		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.emplace_back(encode_move(square, (square - 7), 1, 1, 0, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.emplace_back(encode_move(square, (square - 9), 1, 1, 0, 0, 0, 0));

		if (!((bitboard >> 8) & (w_block | b_block))) {
			moves.emplace_back(encode_move(square, (square - 8), 1, 0, 0, 0, 0, 0));
			if (square / 8 == 6 && !((bitboard >> 16) & (w_block | b_block))) moves.emplace_back(encode_move(square, (square - 16), 1, 0, 0, 1, 0, 0));
		}
	}
}
static inline void w_knight_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & w_block)) {
		if (bitboard >> 6 & b_block) moves.emplace_back(encode_move(square, (square - 6), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 6), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & w_block)) {
		if (bitboard >> 10 & b_block) moves.emplace_back(encode_move(square, (square - 10), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 10), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & w_block)) {
		if (bitboard >> 15 & b_block) moves.emplace_back(encode_move(square, (square - 15), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 15), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & w_block)) {
		if (bitboard >> 17 & b_block) moves.emplace_back(encode_move(square, (square - 17), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 17), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & w_block)) {
		if (bitboard << 6 & b_block) moves.emplace_back(encode_move(square, (square + 6), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 6), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & w_block)) {
		if (bitboard << 10 & b_block) moves.emplace_back(encode_move(square, (square + 10), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 10), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & w_block)) {
		if (bitboard << 15 & b_block) moves.emplace_back(encode_move(square, (square + 15), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 15), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & w_block)) {
		if (bitboard << 17 & b_block) moves.emplace_back(encode_move(square, (square + 17), 2, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 17), 2, 0, 0, 0, 0, 0));
	}
}
static inline void w_bishop_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}
}
static inline void w_rook_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 4, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 4, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 4, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 4, 0, 0, 0, 0, 0));
	}
}
static inline void w_queen_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 5, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 5, 0, 0, 0, 0, 0));
	}
}
static inline void w_king_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & w_block)) {
		if (bitboard >> 7 & b_block) moves.emplace_back(encode_move(square, (square - 7), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 7), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 8) && !(bitboard >> 8 & w_block)) {
		if (bitboard >> 8 & b_block) moves.emplace_back(encode_move(square, (square - 8), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 8), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & w_block)) {
		if (bitboard >> 9 & b_block) moves.emplace_back(encode_move(square, (square - 9), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 9), 6, 0, 0, 0, 0, 0));
	}


	if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & w_block)) {
		if (bitboard >> 1 & b_block) moves.emplace_back(encode_move(square, (square - 1), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 1), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & w_block)) {
		if (bitboard << 1 & b_block) moves.emplace_back(encode_move(square, (square + 1), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 1), 6, 0, 0, 0, 0, 0));
	}


	if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & w_block)) {
		if (bitboard << 7 & b_block) moves.emplace_back(encode_move(square, (square + 7), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 7), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 8) && !(bitboard << 8 & w_block)) {
		if (bitboard << 8 & b_block) moves.emplace_back(encode_move(square, (square + 8), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 8), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & w_block)) {
		if (bitboard << 9 & b_block) moves.emplace_back(encode_move(square, (square + 9), 6, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 9), 6, 0, 0, 0, 0, 0));
	}
}

static inline void b_pawn_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {

	U64 bitboard = 1ULL << square;

	if (square / 8 == 6) {
		if (!((bitboard << 8) & (w_block | b_block))) moves.emplace_back(encode_move(square, (square + 8), 7, 0, 11, 0, 0, 0));

		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.emplace_back(encode_move(square, (square + 7), 7, 1, 11, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.emplace_back(encode_move(square, (square + 9), 7, 1, 11, 0, 0, 0));
	}

	else {

		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.emplace_back(encode_move(square, (square + 7), 7, 1, 0, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.emplace_back(encode_move(square, (square + 9), 7, 1, 0, 0, 0, 0));

		if (!((bitboard << 8) & (w_block | b_block))) {

			moves.emplace_back(encode_move(square, (square + 8), 7, 0, 0, 0, 0, 0));
			if (square / 8 == 1 && !((bitboard << 16) & (w_block | b_block))) moves.emplace_back(encode_move(square, (square + 16), 7, 0, 0, 1, 0, 0));
		}
	}
}
static inline void b_knight_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & b_block)) {
		if (bitboard >> 6 & w_block) moves.emplace_back(encode_move(square, (square - 6), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 6), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & b_block)) {
		if (bitboard >> 10 & w_block) moves.emplace_back(encode_move(square, (square - 10), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 10), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & b_block)) {
		if (bitboard >> 15 & w_block) moves.emplace_back(encode_move(square, (square - 15), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 15), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & b_block)) {
		if (bitboard >> 17 & w_block) moves.emplace_back(encode_move(square, (square - 17), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 17), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & b_block)) {
		if (bitboard << 6 & w_block) moves.emplace_back(encode_move(square, (square + 6), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 6), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & b_block)) {
		if (bitboard << 10 & w_block) moves.emplace_back(encode_move(square, (square + 10), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 10), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & b_block)) {
		if (bitboard << 15 & w_block) moves.emplace_back(encode_move(square, (square + 15), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 15), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & b_block)) {
		if (bitboard << 17 & w_block) moves.emplace_back(encode_move(square, (square + 17), 8, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 17), 8, 0, 0, 0, 0, 0));
	}
}
static inline void b_bishop_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}
}
static inline void b_rook_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 10, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 10, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 10, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 10, 0, 0, 0, 0, 0));
	}
}
static inline void b_queen_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 11, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (y * 8 + t_file), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
		moves.emplace_back(encode_move(square, (t_rank * 8 + x), 11, 0, 0, 0, 0, 0));
	}
}
static inline void b_king_moves(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & b_block)) {
		if (bitboard >> 7 & w_block) moves.emplace_back(encode_move(square, (square - 7), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 7), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 8) && !(bitboard >> 8 & b_block)) {
		if (bitboard >> 8 & w_block) moves.emplace_back(encode_move(square, (square - 8), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 8), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & b_block)) {
		if (bitboard >> 9 & w_block) moves.emplace_back(encode_move(square, (square - 9), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 9), 12, 0, 0, 0, 0, 0));
	}


	if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & b_block)) {
		if (bitboard >> 1 & w_block) moves.emplace_back(encode_move(square, (square - 1), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square - 1), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & b_block)) {
		if (bitboard << 1 & w_block) moves.emplace_back(encode_move(square, (square + 1), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 1), 12, 0, 0, 0, 0, 0));
	}


	if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & b_block)) {
		if (bitboard << 7 & w_block) moves.emplace_back(encode_move(square, (square + 7), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 7), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 8) && !(bitboard << 8 & b_block)) {
		if (bitboard << 8 & w_block) moves.emplace_back(encode_move(square, (square + 8), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 8), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & b_block)) {
		if (bitboard << 9 & w_block) moves.emplace_back(encode_move(square, (square + 9), 12, 1, 0, 0, 0, 0));
		else moves.emplace_back(encode_move(square, (square + 9), 12, 0, 0, 0, 0, 0));
	}
}


static inline void w_pawn_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (square / 8 == 1) {
		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.emplace_back(encode_move(square, (square - 7), 1, 1, 5, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.emplace_back(encode_move(square, (square - 9), 1, 1, 5, 0, 0, 0));
	}

	else {

		if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.emplace_back(encode_move(square, (square - 7), 1, 1, 0, 0, 0, 0));
		if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.emplace_back(encode_move(square, (square - 9), 1, 1, 0, 0, 0, 0));
	}
}
static inline void w_knight_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 6 & not_ab_file & b_block) moves.emplace_back(encode_move(square, (square - 6), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 10 & not_gh_file & b_block) moves.emplace_back(encode_move(square, (square - 10), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 15 & not_a_file & b_block) moves.emplace_back(encode_move(square, (square - 15), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 17 & not_h_file & b_block) moves.emplace_back(encode_move(square, (square - 17), 2, 1, 0, 0, 0, 0));

	if (bitboard << 6 & not_gh_file & b_block) moves.emplace_back(encode_move(square, (square + 6), 2, 1, 0, 0, 0, 0));
	if (bitboard << 10 & not_ab_file & b_block) moves.emplace_back(encode_move(square, (square + 10), 2, 1, 0, 0, 0, 0));
	if (bitboard << 15 & not_h_file & b_block) moves.emplace_back(encode_move(square, (square + 15), 2, 1, 0, 0, 0, 0));
	if (bitboard << 17 & not_a_file & b_block) moves.emplace_back(encode_move(square, (square + 17), 2, 1, 0, 0, 0, 0));
}
static inline void w_bishop_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

}
static inline void w_rook_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void w_queen_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & w_block) break;
		if (1ULL << (x * 8 + y) & b_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & w_block) break;
		if (1ULL << (y * 8 + t_file) & b_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & w_block) break;
		if (1ULL << (t_rank * 8 + x) & b_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void w_king_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 7 & not_a_file & b_block) moves.emplace_back(encode_move(square, (square - 7), 6, 1, 0, 0, 0, 0));
	if (bitboard >> 8 & b_block) moves.emplace_back(encode_move(square, (square - 8), 6, 1, 0, 0, 0, 0));
	if (bitboard >> 9 & not_h_file & b_block) moves.emplace_back(encode_move(square, (square - 9), 6, 1, 0, 0, 0, 0));

	if (bitboard >> 1 & not_h_file & b_block) moves.emplace_back(encode_move(square, (square - 1), 6, 1, 0, 0, 0, 0));
	if (bitboard << 1 & not_a_file & b_block) moves.emplace_back(encode_move(square, (square + 1), 6, 1, 0, 0, 0, 0));

	if (bitboard << 7 & not_h_file & b_block) moves.emplace_back(encode_move(square, (square + 7), 6, 1, 0, 0, 0, 0));
	if (bitboard << 8 & b_block) moves.emplace_back(encode_move(square, (square + 8), 6, 1, 0, 0, 0, 0));
	if (bitboard << 9 & not_a_file & b_block) moves.emplace_back(encode_move(square, (square + 9), 6, 1, 0, 0, 0, 0));
}

static inline void b_pawn_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (square / 8 == 6) {
		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.emplace_back(encode_move(square, (square + 7), 7, 1, 11, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.emplace_back(encode_move(square, (square + 9), 7, 1, 11, 0, 0, 0));
	}

	else {

		if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.emplace_back(encode_move(square, (square + 7), 7, 1, 0, 0, 0, 0));
		if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.emplace_back(encode_move(square, (square + 9), 7, 1, 0, 0, 0, 0));
	}
}
static inline void b_knight_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 6 & not_ab_file & w_block) moves.emplace_back(encode_move(square, (square - 6), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 10 & not_gh_file & w_block) moves.emplace_back(encode_move(square, (square - 10), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 15 & not_a_file & w_block) moves.emplace_back(encode_move(square, (square - 15), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 17 & not_h_file & w_block) moves.emplace_back(encode_move(square, (square - 17), 8, 1, 0, 0, 0, 0));

	if (bitboard << 6 & not_gh_file & w_block) moves.emplace_back(encode_move(square, (square + 6), 8, 1, 0, 0, 0, 0));
	if (bitboard << 10 & not_ab_file & w_block) moves.emplace_back(encode_move(square, (square + 10), 8, 1, 0, 0, 0, 0));
	if (bitboard << 15 & not_h_file & w_block) moves.emplace_back(encode_move(square, (square + 15), 8, 1, 0, 0, 0, 0));
	if (bitboard << 17 & not_a_file & w_block) moves.emplace_back(encode_move(square, (square + 17), 8, 1, 0, 0, 0, 0));
}
static inline void b_bishop_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void b_rook_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;
	

	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void b_queen_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	int t_rank = square / 8;
	int t_file = square % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & b_block) break;
		if (1ULL << (x * 8 + y) & w_block) {
			moves.emplace_back(encode_move(square,  (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & b_block) break;
		if (1ULL << (y * 8 + t_file) & w_block) {
			moves.emplace_back(encode_move(square, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & b_block) break;
		if (1ULL << (t_rank * 8 + x) & w_block) {
			moves.emplace_back(encode_move(square, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
	}
}
static inline void b_king_captures(int square, const U64 w_block, const U64 b_block, vector<U64>& moves) {
	U64 bitboard = 1ULL << square;

	if (bitboard >> 7 & not_a_file & w_block) moves.emplace_back(encode_move(square, (square - 7), 12, 1, 0, 0, 0, 0));
	if (bitboard >> 8 & w_block) moves.emplace_back(encode_move(square, (square - 8), 12, 1, 0, 0, 0, 0));
	if (bitboard >> 9 & not_h_file & w_block) moves.emplace_back(encode_move(square, (square - 9), 12, 1, 0, 0, 0, 0));

	if (bitboard >> 1 & not_h_file & w_block) moves.emplace_back(encode_move(square, (square - 1), 12, 1, 0, 0, 0, 0));
	if (bitboard << 1 & not_a_file & w_block) moves.emplace_back(encode_move(square, (square + 1), 12, 1, 0, 0, 0, 0));

	if (bitboard << 7 & not_h_file & w_block) moves.emplace_back(encode_move(square, (square + 7), 12, 1, 0, 0, 0, 0));
	if (bitboard << 8 & w_block) moves.emplace_back(encode_move(square, (square + 8), 12, 1, 0, 0, 0, 0));
	if (bitboard << 9 & not_a_file & w_block) moves.emplace_back(encode_move(square, (square + 9), 12, 1, 0, 0, 0, 0));
}