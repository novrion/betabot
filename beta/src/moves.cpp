#include "moves.h"



void GenerateMoves(const U64 kBB[13], U64 moves[100], const bool kSide) {

	const U64 kWBlock = W_BLOCK(kBB);
	const U64 kBBlock = B_BLOCK(kBB);


	if (kSide) {

		U64 piece_bitboard = kBB[1];
		while (piece_bitboard) WPawnMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves, GET_UTILITY_EN_PASSANT(kBB[0]));
		piece_bitboard = kBB[2];
		while (piece_bitboard) WKnightMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[3];
		while (piece_bitboard) WBishopMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[4];
		while (piece_bitboard) WRookMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[5];
		while (piece_bitboard) WQueenMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[6];
		while (piece_bitboard) WKingMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves, kBB);
	}

	else {

		U64 piece_bitboard = kBB[7];
		while (piece_bitboard) BPawnMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves, GET_UTILITY_EN_PASSANT(kBB[0]));
		piece_bitboard = kBB[8];
		while (piece_bitboard) BKnightMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[9];
		while (piece_bitboard) BBishopMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[10];
		while (piece_bitboard) BRookMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[11];
		while (piece_bitboard) BQueenMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves);
		piece_bitboard = kBB[12];
		while (piece_bitboard) BKingMoves(PopLsb(piece_bitboard), kWBlock, kBBlock, moves, kBB);
	}
}

void GenerateCaptures(const U64 kBB[13], U64 moves[100], const bool kSide) {

	U64 kWBlock = W_BLOCK(kBB);
	U64 kBBlock = B_BLOCK(kBB);


	if (kSide) {

		U64 pieceBitboard = kBB[1];
		while (pieceBitboard) WPawnCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves, GET_UTILITY_EN_PASSANT(kBB[0]));
		pieceBitboard = kBB[2];
		while (pieceBitboard) WKnightCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[3];
		while (pieceBitboard) WBishopCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[4];
		while (pieceBitboard) WRookCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[5];
		while (pieceBitboard) WQueenCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[6];
		while (pieceBitboard) WKingCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
	}

	else {

		U64 pieceBitboard = kBB[7];
		while (pieceBitboard) BPawnCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves, GET_UTILITY_EN_PASSANT(kBB[0]));
		pieceBitboard = kBB[8];
		while (pieceBitboard) BKnightCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[9];
		while (pieceBitboard) BBishopCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[10];
		while (pieceBitboard) BRookCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[11];
		while (pieceBitboard) BQueenCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
		pieceBitboard = kBB[12];
		while (pieceBitboard) BKingCaptures(PopLsb(pieceBitboard), kWBlock, kBBlock, moves);
	}
}


inline void AddMove(U64 moves[100], const U64 kMove) {
	moves[moves[99]++] = kMove;
}

inline bool CastleDiagonalInCheck(const U64 kBB[13], const U64 kWBlock, const U64 kBBlock, const int kSquare, const bool kSide) {

	const int t_rank = kSquare / 8;
	const int t_file = kSquare % 8;


	if (kSide) {

		for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; --x, --y) {

			if (!(1ULL << (x * 8 + y) & (kWBlock | kBBlock))) continue;
			else if (1ULL << (x * 8 + y) & (kBB[9] | kBB[11])) return false;
			else break;
		}

		for (int x = t_rank - 1; x > -1; --x) {

			if (!(1ULL << (x * 8 + t_file) & (kWBlock | kBBlock))) continue;
			else if (1ULL << (x * 8 + t_file) & (kBB[10] | kBB[11])) return false;
			else break;
		}

		for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; --x, ++y) {

			if (!(1ULL << (x * 8 + y) & (kWBlock | kBBlock))) continue;
			else if (1ULL << (x * 8 + y) & (kBB[9] | kBB[11])) return false;
			else break;
		}
	}

	else {

		for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, --y) {

			if (!(1ULL << (x * 8 + y) & (kWBlock | kBBlock))) continue;
			else if (1ULL << (x * 8 + y) & (kBB[3] | kBB[5])) return false;
			else break;
		}

		for (int x = t_rank + 1; x < 8; ++x) {

			if (!(1ULL << (x * 8 + t_file) & (kWBlock | kBBlock))) continue;
			else if (1ULL << (x * 8 + t_file) & (kBB[4] | kBB[5])) return false;
			else break;
		}

		for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

			if (!(1ULL << (x * 8 + y) & (kWBlock | kBBlock))) continue;
			else if (1ULL << (x * 8 + y) & (kBB[3] | kBB[5])) return false;
			else break;
		}
	}

	return true;
}


inline void WPawnMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare) {

	U64 bitboard = 1ULL << kSquare;

	int rank = kSquare / 8;


	// Promotion
	if (rank == 1) {

		if (!((bitboard >> 8) & (kWBlock | kBBlock))) {
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 1, 0, 2, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 1, 0, 3, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 1, 0, 4, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 1, 0, 5, 0, 0, 0));
		}

		if ((bitboard >> 7 & kNotAFile) && (bitboard >> 7 & kBBlock)) {
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 2, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 3, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 4, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 5, 0, 0, 0));
		}

		if ((bitboard >> 9 & kNotHFile) && (bitboard >> 9 & kBBlock)) {
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 2, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 3, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 4, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 5, 0, 0, 0));
		}
	}

	else {

		if ((bitboard >> 7 & kNotAFile) && (bitboard >> 7 & kBBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 0, 0, 0, 0));
		if ((bitboard >> 9 & kNotHFile) && (bitboard >> 9 & kBBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 0, 0, 0, 0));

		if (!((bitboard >> 8) & (kWBlock | kBBlock))) {

			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 1, 0, 0, 0, 0, 0));

			// Double Pawn Move
			if (rank == 6 && !((bitboard >> 16) & (kWBlock | kBBlock))) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 16), 1, 0, 0, 1, 0, 0));
		}

		// En Passant
		if (kEnPassantSquare && rank == 3) {

			if (kEnPassantSquare == kSquare - 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 0, 0, 0, 1, 0));
			else if (kEnPassantSquare == kSquare + 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 0, 0, 0, 1, 0));
		}
	}
}
inline void WKnightMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;


	if ((bitboard >> 6 & kNotABFile) && !(bitboard >> 6 & kWBlock)) {
		if (bitboard >> 6 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 6), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 6), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 10 & kNotGHFile) && !(bitboard >> 10 & kWBlock)) {
		if (bitboard >> 10 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 10), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 10), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 15 & kNotAFile) && !(bitboard >> 15 & kWBlock)) {
		if (bitboard >> 15 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 15), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 15), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 17 & kNotHFile) && !(bitboard >> 17 & kWBlock)) {
		if (bitboard >> 17 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 17), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 17), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 6 & kNotGHFile) && !(bitboard << 6 & kWBlock)) {
		if (bitboard << 6 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 6), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 6), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 10 & kNotABFile) && !(bitboard << 10 & kWBlock)) {
		if (bitboard << 10 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 10), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 10), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 15 & kNotHFile) && !(bitboard << 15 & kWBlock)) {
		if (bitboard << 15 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 15), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 15), 2, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 17 & kNotAFile) && !(bitboard << 17 & kWBlock)) {
		if (bitboard << 17 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 17), 2, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 17), 2, 0, 0, 0, 0, 0));
	}
}
inline void WBishopMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 0, 0, 0, 0, 0));
	}
}
inline void WRookMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 4, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 4, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 4, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 4, 0, 0, 0, 0, 0));
	}
}
inline void WQueenMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 0, 0, 0, 0, 0));
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 5, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 5, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 5, 0, 0, 0, 0, 0));
	}
}
inline void WKingMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const U64 kBB[13]) {

	U64 bitboard = 1ULL << kSquare;

	if ((bitboard >> 7 & kNotAFile) && !(bitboard >> 7 & kWBlock)) {
		if (bitboard >> 7 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 8) && !(bitboard >> 8 & kWBlock)) {
		if (bitboard >> 8 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 9 & kNotHFile) && !(bitboard >> 9 & kWBlock)) {
		if (bitboard >> 9 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 6, 0, 0, 0, 0, 0));
	}


	if ((bitboard >> 1 & kNotHFile) && !(bitboard >> 1 & kWBlock)) {
		if (bitboard >> 1 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 1), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 1), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 1 & kNotAFile) && !(bitboard << 1 & kWBlock)) {
		if (bitboard << 1 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 1), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 1), 6, 0, 0, 0, 0, 0));
	}


	if ((bitboard << 7 & kNotHFile) && !(bitboard << 7 & kWBlock)) {
		if (bitboard << 7 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 8) && !(bitboard << 8 & kWBlock)) {
		if (bitboard << 8 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 6, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 9 & kNotAFile) && !(bitboard << 9 & kWBlock)) {
		if (bitboard << 9 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 6, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 6, 0, 0, 0, 0, 0));
	}


	// Castle
	if (GET_UTILITY_W_LONG_CASTLE(kBB[0]) && (kBB[4] & (1ULL << 56)) && !(kWCastleLongSpaceMask & (kWBlock | kBBlock)) && !(kBB[7] & kWCastleLongPawnMask) && !(kBB[8] & kWCastleLongKnightMask) && !(kBB[12] & kWCastleLongKingMask)) {
		if (CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 60, true) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 59, true) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 58, true) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 57, true)) {
			AddMove(moves, ENCODE_MOVE(60, 58, 6, 0, 0, 0, 0, 1));
		}
	}

	if (GET_UTILITY_W_SHORT_CASTLE(kBB[0]) && (kBB[4] & (1ULL << 63)) && !(kWCastleShortSpaceMask & (kWBlock | kBBlock)) && !(kBB[7] & kWCastleShortPawnMask) && !(kBB[8] & kWCastleShortKnightMask) && !(kBB[12] & kWCastleShortKingMask)) {
		if (CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 60, true) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 61, true) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 62, true)) {
			AddMove(moves, ENCODE_MOVE(60, 62, 6, 0, 0, 0, 0, 1));
		}
	}
}

inline void BPawnMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare) {

	U64 bitboard = 1ULL << kSquare;

	int rank = kSquare / 8;


	// Promotion
	if (rank == 6) {

		if (!((bitboard << 8) & (kWBlock | kBBlock))) {
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 7, 0, 8, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 7, 0, 9, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 7, 0, 10, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 7, 0, 11, 0, 0, 0));
		}

		if ((bitboard << 7 & kNotHFile) && (bitboard << 7 & kWBlock)) {
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 8, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 9, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 10, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 11, 0, 0, 0));
		}

		if ((bitboard << 9 & kNotAFile) && (bitboard << 9 & kWBlock)) {
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 8, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 9, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 10, 0, 0, 0));
			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 11, 0, 0, 0));
		}
	}

	else {

		if ((bitboard << 7 & kNotHFile) && (bitboard << 7 & kWBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 0, 0, 0, 0));
		if ((bitboard << 9 & kNotAFile) && (bitboard << 9 & kWBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 0, 0, 0, 0));

		if (!((bitboard << 8) & (kWBlock | kBBlock))) {

			AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 7, 0, 0, 0, 0, 0));

			// Double Pawn Move
			if (rank == 1 && !((bitboard << 16) & (kWBlock | kBBlock))) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 16), 7, 0, 0, 1, 0, 0));
		}

		// En Passant
		if (kEnPassantSquare && rank == 4) {

			if (kEnPassantSquare == kSquare - 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 0, 0, 0, 1, 0));
			else if (kEnPassantSquare == kSquare + 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 0, 0, 0, 1, 0));
		}
	}
}
inline void BKnightMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	if ((bitboard >> 6 & kNotABFile) && !(bitboard >> 6 & kBBlock)) {
		if (bitboard >> 6 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 6), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 6), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 10 & kNotGHFile) && !(bitboard >> 10 & kBBlock)) {
		if (bitboard >> 10 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 10), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 10), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 15 & kNotAFile) && !(bitboard >> 15 & kBBlock)) {
		if (bitboard >> 15 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 15), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 15), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 17 & kNotHFile) && !(bitboard >> 17 & kBBlock)) {
		if (bitboard >> 17 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 17), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 17), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 6 & kNotGHFile) && !(bitboard << 6 & kBBlock)) {
		if (bitboard << 6 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 6), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 6), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 10 & kNotABFile) && !(bitboard << 10 & kBBlock)) {
		if (bitboard << 10 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 10), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 10), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 15 & kNotHFile) && !(bitboard << 15 & kBBlock)) {
		if (bitboard << 15 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 15), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 15), 8, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 17 & kNotAFile) && !(bitboard << 17 & kBBlock)) {
		if (bitboard << 17 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 17), 8, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 17), 8, 0, 0, 0, 0, 0));
	}
}
inline void BBishopMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 0, 0, 0, 0, 0));
	}
}
inline void BRookMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 10, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 10, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 10, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 10, 0, 0, 0, 0, 0));
	}
}
inline void BQueenMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 0, 0, 0, 0, 0));
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 11, 0, 0, 0, 0, 0));
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 11, 0, 0, 0, 0, 0));
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
		AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 11, 0, 0, 0, 0, 0));
	}
}
inline void BKingMoves(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const U64 kBB[13]) {

	U64 bitboard = 1ULL << kSquare;

	if ((bitboard >> 7 & kNotAFile) && !(bitboard >> 7 & kBBlock)) {
		if (bitboard >> 7 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 8) && !(bitboard >> 8 & kBBlock)) {
		if (bitboard >> 8 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard >> 9 & kNotHFile) && !(bitboard >> 9 & kBBlock)) {
		if (bitboard >> 9 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 12, 0, 0, 0, 0, 0));
	}


	if ((bitboard >> 1 & kNotHFile) && !(bitboard >> 1 & kBBlock)) {
		if (bitboard >> 1 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 1), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 1), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 1 & kNotAFile) && !(bitboard << 1 & kBBlock)) {
		if (bitboard << 1 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 1), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 1), 12, 0, 0, 0, 0, 0));
	}


	if ((bitboard << 7 & kNotHFile) && !(bitboard << 7 & kBBlock)) {
		if (bitboard << 7 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 8) && !(bitboard << 8 & kBBlock)) {
		if (bitboard << 8 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 12, 0, 0, 0, 0, 0));
	}

	if ((bitboard << 9 & kNotAFile) && !(bitboard << 9 & kBBlock)) {
		if (bitboard << 9 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 12, 1, 0, 0, 0, 0));
		else AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 12, 0, 0, 0, 0, 0));
	}


	// Castle
	if (GET_UTILITY_B_LONG_CASTLE(kBB[0]) && (kBB[10] & 1ULL) && !(kBCastleLongSpaceMask & (kWBlock | kBBlock)) && !(kBB[1] & kBCastleLongPawnMask) && !(kBB[2] & kBCastleLongKnightMask) && !(kBB[6] & kBCastleLongKingMask)) {
		if (CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 4, false) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 3, false) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 2, false) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 1, false)) {
			AddMove(moves, ENCODE_MOVE(4, 2, 12, 0, 0, 0, 0, 1));
		}
	}

	if (GET_UTILITY_B_SHORT_CASTLE(kBB[0]) && (kBB[10] & (1ULL << 7)) && !(kBCastleShortSpaceMask & (kWBlock | kBBlock)) && !(kBB[1] & kBCastleShortPawnMask) && !(kBB[2] & kBCastleShortKnightMask) && !(kBB[6] & kBCastleShortKingMask)) {
		if (CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 4, false) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 5, false) && CastleDiagonalInCheck(kBB, kWBlock, kBBlock, 6, false)) {
			AddMove(moves, ENCODE_MOVE(4, 6, 12, 0, 0, 0, 0, 1));
		}
	}
}


inline void WPawnCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare) {

	U64 bitboard = 1ULL << kSquare;

	int rank = kSquare / 8;


	if (rank == 1) {
		if ((bitboard >> 7 & kNotAFile) && (bitboard >> 7 & kBBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 5, 0, 0, 0));
		if ((bitboard >> 9 & kNotHFile) && (bitboard >> 9 & kBBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 5, 0, 0, 0));
	}

	else {

		if ((bitboard >> 7 & kNotAFile) && (bitboard >> 7 & kBBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 1, 0, 0, 0, 0));
		if ((bitboard >> 9 & kNotHFile) && (bitboard >> 9 & kBBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 1, 0, 0, 0, 0));

		// En Passant
		if (kEnPassantSquare && rank == 3) {

			if (kEnPassantSquare == kSquare - 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 1, 0, 0, 0, 1, 0));
			else if (kEnPassantSquare == kSquare + 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 1, 0, 0, 0, 1, 0));
		}
	}
}
inline void WKnightCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	if (bitboard >> 6 & kNotABFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 6), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 10 & kNotGHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 10), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 15 & kNotAFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 15), 2, 1, 0, 0, 0, 0));
	if (bitboard >> 17 & kNotHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 17), 2, 1, 0, 0, 0, 0));

	if (bitboard << 6 & kNotGHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 6), 2, 1, 0, 0, 0, 0));
	if (bitboard << 10 & kNotABFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 10), 2, 1, 0, 0, 0, 0));
	if (bitboard << 15 & kNotHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 15), 2, 1, 0, 0, 0, 0));
	if (bitboard << 17 & kNotAFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 17), 2, 1, 0, 0, 0, 0));
}
inline void WBishopCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 3, 1, 0, 0, 0, 0));
			break;
		}
	}

}
inline void WRookCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 4, 1, 0, 0, 0, 0));
			break;
		}
	}
}
inline void WQueenCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kWBlock) break;
		if (1ULL << (x * 8 + y) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 5, 1, 0, 0, 0, 0));
			break;
		}
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kWBlock) break;
		if (1ULL << (y * 8 + t_file) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kWBlock) break;
		if (1ULL << (t_rank * 8 + x) & kBBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 5, 1, 0, 0, 0, 0));
			break;
		}
	}
}
inline void WKingCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	if (bitboard >> 7 & kNotAFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 6, 1, 0, 0, 0, 0));
	if (bitboard >> 8 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 6, 1, 0, 0, 0, 0));
	if (bitboard >> 9 & kNotHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 6, 1, 0, 0, 0, 0));

	if (bitboard >> 1 & kNotHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 1), 6, 1, 0, 0, 0, 0));
	if (bitboard << 1 & kNotAFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 1), 6, 1, 0, 0, 0, 0));

	if (bitboard << 7 & kNotHFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 6, 1, 0, 0, 0, 0));
	if (bitboard << 8 & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 6, 1, 0, 0, 0, 0));
	if (bitboard << 9 & kNotAFile & kBBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 6, 1, 0, 0, 0, 0));
}

inline void BPawnCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100], const int kEnPassantSquare) {

	U64 bitboard = 1ULL << kSquare;

	int rank = kSquare / 8;


	if (rank == 6) {
		if ((bitboard << 7 & kNotHFile) && (bitboard << 7 & kWBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 11, 0, 0, 0));
		if ((bitboard << 9 & kNotAFile) && (bitboard << 9 & kWBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 11, 0, 0, 0));
	}

	else {

		if ((bitboard << 7 & kNotHFile) && (bitboard << 7 & kWBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 1, 0, 0, 0, 0));
		if ((bitboard << 9 & kNotAFile) && (bitboard << 9 & kWBlock)) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 1, 0, 0, 0, 0));

		// En Passant
		if (kEnPassantSquare && rank == 4) {

			if (kEnPassantSquare == kSquare - 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 7, 0, 0, 0, 1, 0));
			else if (kEnPassantSquare == kSquare + 1) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 7, 0, 0, 0, 1, 0));
		}
	}
}
inline void BKnightCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	if (bitboard >> 6 & kNotABFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 6), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 10 & kNotGHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 10), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 15 & kNotAFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 15), 8, 1, 0, 0, 0, 0));
	if (bitboard >> 17 & kNotHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 17), 8, 1, 0, 0, 0, 0));

	if (bitboard << 6 & kNotGHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 6), 8, 1, 0, 0, 0, 0));
	if (bitboard << 10 & kNotABFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 10), 8, 1, 0, 0, 0, 0));
	if (bitboard << 15 & kNotHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 15), 8, 1, 0, 0, 0, 0));
	if (bitboard << 17 & kNotAFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 17), 8, 1, 0, 0, 0, 0));
}
inline void BBishopCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 9, 1, 0, 0, 0, 0));
			break;
		}
	}
}
inline void BRookCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 10, 1, 0, 0, 0, 0));
			break;
		}
	}
}
inline void BQueenCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	int t_rank = kSquare / 8;
	int t_file = kSquare % 8;


	// bishop
	for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

		if (1ULL << (x * 8 + y) & kBBlock) break;
		if (1ULL << (x * 8 + y) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (x * 8 + y), 11, 1, 0, 0, 0, 0));
			break;
		}
	}


	// rook
	for (int y = t_rank + 1; y < 8; ++y) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int y = t_rank - 1; y > -1; y--) {

		if (1ULL << (y * 8 + t_file) & kBBlock) break;
		if (1ULL << (y * 8 + t_file) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (y * 8 + t_file), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file + 1; x < 8; ++x) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
	}

	for (int x = t_file - 1; x > -1; x--) {

		if (1ULL << (t_rank * 8 + x) & kBBlock) break;
		if (1ULL << (t_rank * 8 + x) & kWBlock) {
			AddMove(moves, ENCODE_MOVE(kSquare, (t_rank * 8 + x), 11, 1, 0, 0, 0, 0));
			break;
		}
	}
}
inline void BKingCaptures(const int kSquare, const U64 kWBlock, const U64 kBBlock, U64 moves[100]) {

	U64 bitboard = 1ULL << kSquare;

	if (bitboard >> 7 & kNotAFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 7), 12, 1, 0, 0, 0, 0));
	if (bitboard >> 8 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 8), 12, 1, 0, 0, 0, 0));
	if (bitboard >> 9 & kNotHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 9), 12, 1, 0, 0, 0, 0));

	if (bitboard >> 1 & kNotHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare - 1), 12, 1, 0, 0, 0, 0));
	if (bitboard << 1 & kNotAFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 1), 12, 1, 0, 0, 0, 0));

	if (bitboard << 7 & kNotHFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 7), 12, 1, 0, 0, 0, 0));
	if (bitboard << 8 & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 8), 12, 1, 0, 0, 0, 0));
	if (bitboard << 9 & kNotAFile & kWBlock) AddMove(moves, ENCODE_MOVE(kSquare, (kSquare + 9), 12, 1, 0, 0, 0, 0));
}