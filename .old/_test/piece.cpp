#include "beta.h"

const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;

U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];

U64 bishop_attacks[64];
U64 rook_attacks[64];



U64 mask_pawn_attacks(int color, int square) {

	U64 moves = 0ULL;
	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (color) {
		if (bitboard >> 7 & not_a_file) moves |= (bitboard >> 7);
		if (bitboard >> 9 & not_h_file) moves |= (bitboard >> 9);
	}

	else {
		if (bitboard << 7 & not_h_file) moves |= (bitboard << 7);
		if (bitboard << 9 & not_a_file) moves |= (bitboard << 9);
	}

	return moves;
}

U64 mask_knight_attacks(int square) {

	U64 moves = 0ULL;
	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (bitboard >> 6 & not_ab_file) moves |= (bitboard >> 6);
	if (bitboard >> 10 & not_gh_file) moves |= (bitboard >> 10);
	if (bitboard >> 15 & not_a_file) moves |= (bitboard >> 15);
	if (bitboard >> 17 & not_h_file) moves |= (bitboard >> 17);

	if (bitboard << 6 & not_gh_file) moves |= (bitboard << 6);
	if (bitboard << 10 & not_ab_file)moves |= (bitboard << 10);
	if (bitboard << 15 & not_h_file) moves |= (bitboard << 15);
	if (bitboard << 17 & not_a_file)moves |= (bitboard << 17);

	return moves;
}

U64 mask_king_attacks(int square) {

	U64 moves = 0ULL;
	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (bitboard >> 7 & not_a_file) moves |= (bitboard >> 7);
	if (bitboard >> 8) moves |= (bitboard >> 8);
	if (bitboard >> 9 & not_h_file) moves |= (bitboard >> 9);

	if (bitboard >> 1 & not_h_file) moves |= (bitboard >> 1);
	if (bitboard << 1 & not_a_file) moves |= (bitboard << 1);

	if (bitboard << 7 & not_h_file) moves |= (bitboard << 7);
	if (bitboard << 8) moves |= (bitboard << 8);
	if (bitboard << 9 & not_a_file) moves |= (bitboard << 9);

	return moves;
}

void init_leaper_attacks() {

	for (int pos = 0; pos < 64; pos++) {

		pawn_attacks[black][pos] = mask_pawn_attacks(black, pos);
		pawn_attacks[white][pos] = mask_pawn_attacks(white, pos);

		knight_attacks[pos] = mask_knight_attacks(pos);

		king_attacks[pos] = mask_king_attacks(pos);
	}
}


U64 mask_bishop_attacks(int square) {

	U64 moves = 0ULL;

	int t_rank = square / 8;
	int t_file = square % 8;

	for (int x = t_rank + 1, y = t_file + 1; x < 7 && y < 7; x++, y++) moves |= (1ULL << (x * 8 + y));
	for (int x = t_rank - 1, y = t_file + 1; x > 0 && y < 7; x--, y++) moves |= (1ULL << (x * 8 + y));
	for (int x = t_rank + 1, y = t_file - 1; x < 7 && y > 0; x++, y--) moves |= (1ULL << (x * 8 + y));
	for (int x = t_rank - 1, y = t_file - 1; x > 0 && y > 0; x--, y--) moves |= (1ULL << (x * 8 + y));

	return moves;
}

U64 mask_rook_attacks(int square) {

	U64 moves = 0ULL;

	int t_rank = square / 8;
	int t_file = square % 8;

	for (int y = t_rank + 1; y < 7; y++) moves |= (1ULL << (y * 8 + t_file));
	for (int y = t_rank - 1; y > 0; y--) moves |= (1ULL << (y * 8 + t_file));

	for (int x = t_file + 1; x < 7; x++) moves |= (1ULL << (t_rank * 8 + x));
	for (int x = t_file - 1; x > 0; x--) moves |= (1ULL << (t_rank * 8 + x));


	return moves;
}

void init_slider_attacks() {

	for (int pos = 0; pos < 64; pos++) {

		bishop_attacks[pos] = mask_bishop_attacks(pos);

		rook_attacks[pos] = mask_rook_attacks(pos);
		PrintBoard(rook_attacks[pos]);
	}
}


void init_moves() {

	init_leaper_attacks();
	init_slider_attacks();
}