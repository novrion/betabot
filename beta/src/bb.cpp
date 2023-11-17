#include "bb.h"



void MakeMove(U64 bb[13], const U64 kMove, const bool kSide) {

	int source = GET_MOVE_SOURCE(kMove);
	int target = GET_MOVE_TARGET(kMove);
	int piece = GET_MOVE_PIECE(kMove);

	int double_pawn = GET_MOVE_2_PAWN(kMove);
	int en_passant = GET_MOVE_EN_PASSANT(kMove);
	int castle = GET_MOVE_CASTLE(kMove);

	int promotion = GET_MOVE_PROMOTION(kMove);
	int capture = GET_MOVE_CAPTURE(kMove);


	// Reset En Passant Square
	bb[0] &= kEnPassantMask;

	// Update Rook Moved Flag
	if (piece == 4) {

		if (source == 56) bb[0] &= kWLongCastleMask;
		else if (source == 63) bb[0] &= kWShortCastleMask;
	}
	else if (piece == 10) {

		if (source == 0) bb[0] &= kBLongCastleMask;
		else if (source == 7) bb[0] &= kBShortCastleMask;
	}

	// Update King Moved Flag
	if (piece == 6) bb[0] &= kWBothCastleMask;
	else if (piece == 12) bb[0] &= kBBothCastleMask;


	if (capture) {

		POP_BIT(bb[piece], source);

		if (promotion) SET_BIT(bb[promotion], target);
		else SET_BIT(bb[piece], target);

		POP_BIT(bb[capture], target);
	}

	else if (castle) {

		if (target == 58) {

			POP_BIT(bb[6], 60);
			SET_BIT(bb[6], 58);

			POP_BIT(bb[4], 56);
			SET_BIT(bb[4], 59);
		}

		else if (target == 62) {

			POP_BIT(bb[6], 60);
			SET_BIT(bb[6], 62);

			POP_BIT(bb[4], 63);
			SET_BIT(bb[4], 61);
		}


		else if (target == 2) {

			POP_BIT(bb[12], 4);
			SET_BIT(bb[12], 2);

			POP_BIT(bb[10], 0);
			SET_BIT(bb[10], 3);
		}

		else {

			POP_BIT(bb[12], 4);
			SET_BIT(bb[12], 6);

			POP_BIT(bb[10], 7);
			SET_BIT(bb[10], 5);
		}
	}

	else if (promotion) {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[promotion], target);
	}

	else if (en_passant) {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);

		if (kSide) POP_BIT(bb[7], target + 8);
		else POP_BIT(bb[1], target - 8);
	}

	else if (double_pawn) {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);

		bb[0] |= target;
	}

	else {

		POP_BIT(bb[piece], source);
		SET_BIT(bb[piece], target);
	}
}


// Bit Manipulation
int BitCount(U64 x) {

	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

	return ((x * 0x0101010101010101) >> 56);
}
int PopLsb(U64& b) {

	const int kS = __builtin_ctzll(b);
	b &= b - 1;

	return kS;
}


void InitAll(Board& b, bool& kSide, double& max_search_time) {

	// (utility)
	b.bb[0] = 960ULL;
	b.bb[0] |= 1ULL << 10;

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


	b.side = InitSide();
	kSide = b.side;

	max_search_time = InitMaxSearchTime();
}
bool InitSide() {

	char ch;

	std::cout << "Player Side W/B: ";
	std::cin >> ch;

	return ((ch == 'W' || ch == 'w') ? true : false);
}
double InitMaxSearchTime() {

	double max_search_time;

	std::cout << "Max Search Time (s): ";
	std::cin >> max_search_time;

	return max_search_time;
}