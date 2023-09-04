#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <map>
#include <bit>

using namespace std;
using namespace std::chrono;


// Macro
#define U64 unsigned long long
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)
//#define pop_bit(bitboard, square) (bitboard ^= (1ULL << square))

#define _w_block(x) (x[1] | x[2] | x[3] | x[4] | x[5] | x[6])
#define _b_block(x) (x[7] | x[8] | x[9] | x[10] | x[11] | x[12])


// Encode
#define encode_move(source, target, piece, capture, promotion, _2pawn, en_passant, castle) \
(source) | (target << 6) | (piece << 12) | (_2pawn << 16) | (en_passant << 17) | (castle << 18) | (promotion << 19) | (capture << 23) \


// Decode
#define get_move_from(move) (move & 63ULL)
#define get_move_to(move) ((move & 4032ULL) >> 6)
#define get_move_piece(move) ((move & 61440ULL) >> 12)

#define get_move_2_pawn(move) (move & 65536ULL)
#define get_move_en_passant(move) (move & 131072ULL)
#define get_move_castle(move) (move & 262144ULL)

#define get_move_promotion(move) ((move & 7864320ULL) >> 19)
#define get_move_capture(move) ((move & 125829120ULL) >> 23)


// Board
struct Board {

	Board() {

		// (white)	Pawn, Horse, Bishop, Rook, Queen, King
		b2[1] = 71776119061217280ULL;
		b2[2] = 4755801206503243776ULL;
		b2[3] = 2594073385365405696ULL;
		b2[4] = 9295429630892703744ULL;
		b2[5] = 576460752303423488ULL;
		b2[6] = 1152921504606846976ULL;

		// (black)	Pawn, Horse, Bishop, Rook, Queen, King
		b2[7] = 65280ULL;
		b2[8] = 66ULL;
		b2[9] = 36ULL;
		b2[10] = 129ULL;
		b2[11] = 8ULL;
		b2[12] = 16ULL;

		// (utility)
		b2[0] = 0ULL;

		// next move
		n_move = 0ULL;
	}

	U64 b2[13];
	U64 n_move;
};


// Generate Moves
void gen_moves(U64 b2[13], int colour, std::vector<U64>& moves);

void pawn_moves(int square, int colour, U64 w_block, U64 b_block, std::vector<U64>& moves);
void knight_moves(int square, int colour, U64 w_block, U64 b_block, std::vector<U64>& moves);
void king_moves(int square, int colour, U64 w_block, U64 b_block, std::vector<U64>& moves);
void bishop_moves(int square, int colour, U64 w_block, U64 b_block, std::vector<U64>& moves);
void rook_moves(int square, int colour, U64 w_block, U64 b_block, std::vector<U64>& moves);
void queen_moves(int square, int colour, U64 w_block, U64 b_block, std::vector<U64>& moves);


// Make Move
void make_move(U64 b2[13], U64& move, int colour);
void undo_move(U64 b2[13], U64& move, int colour);


// Search
int minimax(U64 b2[13], int depth, int colour);
using namespace std;
using namespace std::chrono;




const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;


void pawn_moves(int square, int colour, U64 w_block, U64 b_block, vector<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if (square / 8 == 1) {
			if (!((bitboard >> 8) & w_block & b_block)) moves.push_back(encode_move(square, square - 8, 1, 0, 0, 5, 0, 0));

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.push_back(encode_move(square, square - 7, 1, 1, 6, 0, 0, 0));
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.push_back(encode_move(square, square - 9, 1, 1, 6, 0, 0, 0));
		}

		else {

			if ((bitboard >> 7 & not_a_file) && (bitboard >> 7 & b_block)) moves.push_back(encode_move(square, square - 7, 1, 1, 0, 0, 0, 0));
			if ((bitboard >> 9 & not_h_file) && (bitboard >> 9 & b_block)) moves.push_back(encode_move(square, square - 9, 1, 1, 0, 0, 0, 0));

			if (!((bitboard >> 8) & w_block) && !((bitboard >> 8) & b_block)) {

				moves.push_back(encode_move(square, square - 8, 1, 0, 0, 0, 0, 0));
				if (square / 8 == 6 && !((bitboard >> 16) & w_block) && !((bitboard >> 16) & b_block)) moves.push_back(encode_move(square, square - 16, 1, 0, 0, 1, 0, 0));
			}
		}
	}

	else {

		if (square / 8 == 6) {
			if (!((bitboard << 8) & w_block & b_block)) moves.push_back(encode_move(square, square + 8, 7, 0, 11, 0, 0, 0));

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.push_back(encode_move(square, square + 7, 7, 1, 11, 0, 0, 0));
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.push_back(encode_move(square, square + 9, 7, 1, 11, 0, 0, 0));
		}

		else {

			if ((bitboard << 7 & not_h_file) && (bitboard << 7 & w_block)) moves.push_back(encode_move(square, square + 7, 7, 1, 0, 0, 0, 0));
			if ((bitboard << 9 & not_a_file) && (bitboard << 9 & w_block)) moves.push_back(encode_move(square, square + 9, 7, 1, 0, 0, 0, 0));

			if (!((bitboard << 8) & w_block) && !((bitboard << 8) & b_block)) {

				moves.push_back(encode_move(square, square + 8, 7, 0, 0, 0, 0, 0));
				if (square / 8 == 1 && !((bitboard << 16) & w_block) && !((bitboard << 16) & b_block)) moves.push_back(encode_move(square, square + 16, 7, 0, 0, 1, 0, 0));
			}
		}
	}
}

void knight_moves(int square, int colour, U64 w_block, U64 b_block, vector<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & w_block)) {
			if (bitboard >> 6 & b_block) moves.push_back(encode_move(square, square - 6, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 6, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & w_block)) {
			if (bitboard >> 10 & b_block) moves.push_back(encode_move(square, square - 10, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 10, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & w_block)) {
			if (bitboard >> 15 & b_block) moves.push_back(encode_move(square, square - 15, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 15, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & w_block)) {
			if (bitboard >> 17 & b_block) moves.push_back(encode_move(square, square - 17, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 17, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & w_block)) {
			if (bitboard << 6 & b_block) moves.push_back(encode_move(square, square + 6, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 6, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & w_block)) {
			if (bitboard << 10 & b_block) moves.push_back(encode_move(square, square + 10, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 10, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & w_block)) {
			if (bitboard << 15 & b_block) moves.push_back(encode_move(square, square + 15, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 15, 2, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & w_block)) {
			if (bitboard << 17 & b_block) moves.push_back(encode_move(square, square + 17, 2, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 17, 2, 0, 0, 0, 0, 0));
		}
	}

	else {

		if ((bitboard >> 6 & not_ab_file) && !(bitboard >> 6 & b_block)) {
			if (bitboard >> 6 & w_block) moves.push_back(encode_move(square, square - 6, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 6, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 10 & not_gh_file) && !(bitboard >> 10 & b_block)) {
			if (bitboard >> 10 & w_block) moves.push_back(encode_move(square, square - 10, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 10, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 15 & not_a_file) && !(bitboard >> 15 & b_block)) {
			if (bitboard >> 15 & w_block) moves.push_back(encode_move(square, square - 15, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 15, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 17 & not_h_file) && !(bitboard >> 17 & b_block)) {
			if (bitboard >> 17 & w_block) moves.push_back(encode_move(square, square - 17, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 17, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 6 & not_gh_file) && !(bitboard << 6 & b_block)) {
			if (bitboard << 6 & w_block) moves.push_back(encode_move(square, square + 6, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 6, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 10 & not_ab_file) && !(bitboard << 10 & b_block)) {
			if (bitboard << 10 & w_block) moves.push_back(encode_move(square, square + 10, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 10, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 15 & not_h_file) && !(bitboard << 15 & b_block)) {
			if (bitboard << 15 & w_block) moves.push_back(encode_move(square, square + 15, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 15, 8, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 17 & not_a_file) && !(bitboard << 17 & b_block)) {
			if (bitboard << 17 & w_block) moves.push_back(encode_move(square, square + 17, 8, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 17, 8, 0, 0, 0, 0, 0));
		}
	}
}

void king_moves(int square, int colour, U64 w_block, U64 b_block, vector<U64>& moves) {

	U64 bitboard = 0ULL;
	set_bit(bitboard, square);

	if (colour) {

		if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & w_block)) {
			if (bitboard >> 7 & b_block) moves.push_back(encode_move(square, square - 7, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 7, 6, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 8) && !(bitboard >> 8 & w_block)) {
			if (bitboard >> 8 & b_block) moves.push_back(encode_move(square, square - 8, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 8, 6, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & w_block)) {
			if (bitboard >> 9 & b_block) moves.push_back(encode_move(square, square - 9, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 9, 6, 0, 0, 0, 0, 0));
		}


		if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & w_block)) {
			if (bitboard >> 1 & b_block) moves.push_back(encode_move(square, square - 1, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 1, 6, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & w_block)) {
			if (bitboard << 1 & b_block) moves.push_back(encode_move(square, square + 1, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 1, 6, 0, 0, 0, 0, 0));
		}


		if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & w_block)) {
			if (bitboard << 7 & b_block) moves.push_back(encode_move(square, square + 7, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 7, 6, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 8) && !(bitboard << 8 & w_block)) {
			if (bitboard << 8 & b_block) moves.push_back(encode_move(square, square + 8, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 8, 6, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & w_block)) {
			if (bitboard << 9 & b_block) moves.push_back(encode_move(square, square + 9, 6, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 9, 6, 0, 0, 0, 0, 0));
		}
	}

	else {

		if ((bitboard >> 7 & not_a_file) && !(bitboard >> 7 & b_block)) {
			if (bitboard >> 7 & w_block) moves.push_back(encode_move(square, square - 7, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 7, 12, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 8) && !(bitboard >> 8 & b_block)) {
			if (bitboard >> 8 & w_block) moves.push_back(encode_move(square, square - 8, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 8, 12, 0, 0, 0, 0, 0));
		}

		if ((bitboard >> 9 & not_h_file) && !(bitboard >> 9 & b_block)) {
			if (bitboard >> 9 & w_block) moves.push_back(encode_move(square, square - 9, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 9, 12, 0, 0, 0, 0, 0));
		}


		if ((bitboard >> 1 & not_h_file) && !(bitboard >> 1 & b_block)) {
			if (bitboard >> 1 & w_block) moves.push_back(encode_move(square, square - 1, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square - 1, 12, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 1 & not_a_file) && !(bitboard << 1 & b_block)) {
			if (bitboard << 1 & w_block) moves.push_back(encode_move(square, square + 1, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 1, 12, 0, 0, 0, 0, 0));
		}


		if ((bitboard << 7 & not_h_file) && !(bitboard << 7 & b_block)) {
			if (bitboard << 7 & w_block) moves.push_back(encode_move(square, square + 7, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 7, 12, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 8) && !(bitboard << 8 & b_block)) {
			if (bitboard << 8 & w_block) moves.push_back(encode_move(square, square + 8, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 8, 12, 0, 0, 0, 0, 0));
		}

		if ((bitboard << 9 & not_a_file) && !(bitboard << 9 & b_block)) {
			if (bitboard << 9 & w_block) moves.push_back(encode_move(square, square + 9, 12, 1, 0, 0, 0, 0));
			else moves.push_back(encode_move(square, square + 9, 12, 0, 0, 0, 0, 0));
		}
	}
}


void bishop_moves(int square, int colour, U64 w_block, U64 b_block, vector<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 3, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 3, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 3, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 3, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 3, 0, 0, 0, 0, 0));
		}
	}

	else {

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 9, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 9, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 9, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 9, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 9, 0, 0, 0, 0, 0));
		}
	}
}

void rook_moves(int square, int colour, U64 w_block, U64 b_block, vector<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 4, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 4, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 4, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 4, 0, 0, 0, 0, 0));
		}
	}

	else {

		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 10, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 10, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 10, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 10, 0, 0, 0, 0, 0));
		}
	}
}

void queen_moves(int square, int colour, U64 w_block, U64 b_block, vector<U64>& moves) {

	int t_rank = square / 8;
	int t_file = square % 8;

	if (colour) {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 5, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 5, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 5, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & w_block) break;
			if (1ULL << (x * 8 + y) & b_block) {
				moves.push_back(encode_move(square, x * 8 + y, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 5, 0, 0, 0, 0, 0));
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 5, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & w_block) break;
			if (1ULL << (y * 8 + t_file) & b_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 5, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 5, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & w_block) break;
			if (1ULL << (t_rank * 8 + x) & b_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 5, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 5, 0, 0, 0, 0, 0));
		}
	}

	else {

		// bishop
		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; x++, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 11, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, y++) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 11, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; x++, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 11, 0, 0, 0, 0, 0));
		}

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

			if (1ULL << (x * 8 + y) & b_block) break;
			if (1ULL << (x * 8 + y) & w_block) {
				moves.push_back(encode_move(square, x * 8 + y, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, x * 8 + y, 11, 0, 0, 0, 0, 0));
		}


		// rook
		for (int y = t_rank + 1; y < 8; y++) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 11, 0, 0, 0, 0, 0));
		}

		for (int y = t_rank - 1; y > -1; y--) {

			if (1ULL << (y * 8 + t_file) & b_block) break;
			if (1ULL << (y * 8 + t_file) & w_block) {
				moves.push_back(encode_move(square, y * 8 + t_file, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, y * 8 + t_file, 11, 0, 0, 0, 0, 0));
		}

		for (int x = t_file + 1; x < 8; x++) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 11, 0, 0, 0, 0, 0));
		}

		for (int x = t_file - 1; x > -1; x--) {

			if (1ULL << (t_rank * 8 + x) & b_block) break;
			if (1ULL << (t_rank * 8 + x) & w_block) {
				moves.push_back(encode_move(square, t_rank * 8 + x, 11, 1, 0, 0, 0, 0));
				break;
			}
			moves.push_back(encode_move(square, t_rank * 8 + x, 11, 0, 0, 0, 0, 0));
		}
	}
}













































const U64 capture_mask = 8388607ULL;



void gen_moves(U64 b2[13], int colour, vector<U64>& moves) {

	/*duration<double> time;
	time_point<chrono::high_resolution_clock> start_time;
	start_time = high_resolution_clock::now();*/

	U64 w_block = _w_block(b2);
	U64 b_block = _b_block(b2);

	if (colour) {

		for (int square = 0; square < 64; square++) {

			if (b2[1] & 1ULL << square) {
				pawn_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[2] & 1ULL << square) {
				knight_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[3] & 1ULL << square) {
				bishop_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[4] & 1ULL << square) {
				rook_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[5] & 1ULL << square) {
				queen_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[6] & 1ULL << square) {
				king_moves(square, colour, w_block, b_block, moves);
			}
		}
	}

	else {

		for (int square = 0; square < 64; square++) {

			if (b2[7] & 1ULL << square) {
				pawn_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[8] & 1ULL << square) {
				knight_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[9] & 1ULL << square) {
				bishop_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[10] & 1ULL << square) {
				rook_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[11] & 1ULL << square) {
				queen_moves(square, colour, w_block, b_block, moves);
			}

			if (b2[12] & 1ULL << square) {
				king_moves(square, colour, w_block, b_block, moves);
			}
		}
	}

	//time = high_resolution_clock::now() - start_time;
	//cout << time.count() << "\n";
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
			for (int i = 7; i < 13; i++) {
				if (1ULL << target & b2[i]) {
					pop_bit(b2[i], target);
					move &= capture_mask;
					move |= (i << 23);
					break;
				}
			}
		}

		else {
			for (int i = 1; i < 7; i++) {
				if (1ULL << target & b2[i]) {
					pop_bit(b2[i], target);
					move &= capture_mask;
					move |= (i << 23);
					break;
				}
			}
		}
	}
}

void undo_move(U64 b2[13], U64& move, int colour) {

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















int minimax(U64 b2[13], int depth, int colour) {

	if (!depth) return 1;

	int evaluation = 0;

	vector<U64> moves;
	gen_moves(b2, colour, moves);
	//sort(moves.begin(), moves.end());


	if (colour) {

		for (int i = moves.size() - 1; i > -1; i--) {

			make_move(b2, moves[i], colour);
			evaluation += minimax(b2, depth - 1, 0);
			undo_move(b2, moves[i], colour);
		}

		return evaluation;
	}


	else {

		for (int i = moves.size() - 1; i > -1; i--) {

			make_move(b2, moves[i], colour);
			evaluation += minimax(b2, depth - 1, 1);
			undo_move(b2, moves[i], colour);
		}

		return evaluation;
	}
}








int main() {

	Board b;
	int nodes = 0;
	int depth;


	cout << "depth: ";
	cin >> depth;

	duration<double> time;
	time_point<chrono::high_resolution_clock> start_time = high_resolution_clock::now();


	nodes = minimax(b.b2, depth, 1);
	cout << "nodes: " << nodes << "\n";

	time = high_resolution_clock::now() - start_time;
	cout << time.count() << "\n";

	cout << nodes / time.count() << " nodes/s";

	return 0;
}