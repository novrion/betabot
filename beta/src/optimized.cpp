#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;


#define U64 unsigned long long

// Bit Manipulation
#define SET_BIT(bitboard, square) (bitboard |= (1ULL << square))
#define POP_BIT(bitboard, square) (bitboard &= ~(1ULL << square))

// Blockers
#define W_BLOCK(bb) (bb[1] | bb[2] | bb[3] | bb[4] | bb[5] | bb[6])
#define B_BLOCK(bb) (bb[7] | bb[8] | bb[9] | bb[10] | bb[11] | bb[12])

// Encode Move
#define ENCODE_MOVE(source, target, piece, capture, promotion, _2pawn, en_passant, castle) \
(source) | (target << 6) | (piece << 12) | (_2pawn << 16) | (en_passant << 17) | (castle << 18) | (promotion << 19) | (capture << 23) \

#define RESET_MOVE_CAPTURE(move) (move &= 18446744073701163007ULL)
//#define RESET_MOVE_CAPTURE(move) (move &= 8388607ULL)
#define SET_MOVE_CAPTURE(move, piece) (move |= piece << 23)

// Decode Move
#define GET_MOVE_SOURCE(move) (move & 63ULL)
#define GET_MOVE_TARGET(move) ((move & 4032ULL) >> 6)
#define GET_MOVE_PIECE(move) ((move & 61440ULL) >> 12)
#define GET_MOVE_2_PAWN(move) (move & 65536ULL)
#define GET_MOVE_EN_PASSANT(move) (move & 131072ULL)
#define GET_MOVE_CASTLE(move) (move & 262144ULL)
#define GET_MOVE_PROMOTION(move) ((move & 7864320ULL) >> 19)
#define GET_MOVE_CAPTURE(move) ((move & 125829120ULL) >> 23)

// Encode Utility
#define SWITCH_UTILITY_SIDE(utility) (utility ^= 1024ULL)

// Decode Utility
#define GET_UTILITY_EN_PASSANT(utility) (utility & 63ULL)
#define GET_UTILITY_W_SHORT_CASTLE(utility) (utility & 64ULL)
#define GET_UTILITY_W_LONG_CASTLE(utility) (utility & 128ULL)
#define GET_UTILITY_B_SHORT_CASTLE(utility) (utility & 256ULL)
#define GET_UTILITY_B_LONG_CASTLE(utility) (utility & 512ULL)
#define GET_UTILITY_SIDE(utility) (utility & 1024ULL)

// Hash Utility
#define GET_HASH_CASTLING(utility) ((utility & 960ULL) >> 6)
#define GET_HASH_DEPTH(hash) (hash & 4294967295ULL)
#define GET_HASH_EVAL(hash) (hash >> 32)
#define ENCODE_HASH(eval, depth) (((0ULL | eval) << 32) | depth)



// Good sort :)
/*sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return a < (>) b; }); */
/*int i = moves.size() - 1; i >= 0; --i*/

// https://github.com/tmacksf/TtCE/blob/main/Bitboard.hpp



/* -------------------------------------------------- BB --------------------------------------------------*/

const U64 kEnPassantMask = 960ULL;

const U64 kWShortCastleMask = 959ULL;
const U64 kWLongCastleMask = 895ULL;
const U64 kWBothCastleMask = 831ULL;

const U64 kBShortCastleMask = 767ULL;
const U64 kBLongCastleMask = 511ULL;
const U64 kBBothCastleMask = 255ULL;


struct Board {
	U64 bb[13];
	bool side;
};



// Initialization
inline void InitAll(Board& b, bool& kSide, double& max_search_time);
inline bool InitSide();
inline double InitMaxSearchTime();

// Hash
inline U64 Zobrist(Board& b, const bool kSide);
inline unsigned XorShift32(unsigned& x);
inline U64 XorShift64(unsigned& x);
inline void InitTransposition();

// Moves
inline void MakeMove(U64 bb[13], const U64 kMove, const bool kSide);
inline void GetMoveTargets(Board& b, U64 moves[100], const bool kSide);
inline bool InCheck(Board& b, const bool kSide);

// Bit Manipulation
inline int BitCount(U64 x);
inline int PopLsb(U64& b);

unsigned key = 9876789;
U64 piece_hash[13][64];
U64 castle_hash[16];
U64 en_passant_hash[64];
U64 side_hash;



// Moves
inline void MakeMove(U64 bb[13], const U64 kMove, const bool kSide) {

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

inline void GetMoveTargets(Board& b, U64 moves[100], const bool kSide) {

    if (kSide) {

        for (int i = 0; i < moves[99]; ++i) {
            
            if (!GET_MOVE_CAPTURE(moves[i])) continue;
            int target = GET_MOVE_TARGET(moves[i]);

            for (int j = 7; j < 13; ++j) {

                if (b.bb[j] & (1ULL << target)) {

                    RESET_MOVE_CAPTURE(moves[i]);
                    SET_MOVE_CAPTURE(moves[i], j);

                    break;
                }
            }
        }
    }

    else {

        for (int i = 0; i < moves[99]; ++i) {
            
            if (!GET_MOVE_CAPTURE(moves[i])) continue;
            int target = GET_MOVE_TARGET(moves[i]);

            for (int j = 1; j < 7; ++j) {

                if (b.bb[j] & (1ULL << target)) {

                    RESET_MOVE_CAPTURE(moves[i]);
                    SET_MOVE_CAPTURE(moves[i], j);

                    break;
                }
            }
        }
    }
}

inline bool InCheck(Board& b, const bool kSide) {

    const U64 kWBlock = W_BLOCK(b.bb);
    const U64 kBBlock = B_BLOCK(b.bb);

    const U64 kWBishopQueenBlock = b.bb[3] | b.bb[5];
    const U64 kWRookQueenBlock = b.bb[4] | b.bb[5];

    const U64 kBBishopQueenBlock = b.bb[9] | b.bb[11];
    const U64 kBRookQueenBlock = b.bb[10] | b.bb[11];


    if (kSide) {

        int square = __builtin_ctzll(b.bb[6]);

        const int t_rank = square / 8;
        const int t_file = square % 8;

        // Diagonal
        for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

            if (1ULL << (x * 8 + y) & kWBlock) break;
            else if (1ULL << (x * 8 + y) & kBBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kBBlock) break;
        }

        for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

            if (1ULL << (x * 8 + y) & kWBlock) break;
            else if (1ULL << (x * 8 + y) & kBBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kBBlock) break;
        }

        for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

            if (1ULL << (x * 8 + y) & kWBlock) break;
            else if (1ULL << (x * 8 + y) & kBBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kBBlock) break;
        }

        for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

            if (1ULL << (x * 8 + y) & kWBlock) break;
            else if (1ULL << (x * 8 + y) & kBBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kBBlock) break;
        }


        // Straight
        for (int y = t_rank + 1; y < 8; ++y) {

            if (1ULL << (y * 8 + t_file) & kWBlock) break;
            else if (1ULL << (y * 8 + t_file) & kBRookQueenBlock) return true;
            else if (1ULL << (y * 8 + t_file) & kBBlock) break;
        }

        for (int y = t_rank - 1; y > -1; y--) {

            if (1ULL << (y * 8 + t_file) & kWBlock) break;
            else if (1ULL << (y * 8 + t_file) & kBRookQueenBlock) return true;
            else if (1ULL << (y * 8 + t_file) & kBBlock) break;
        }

        for (int x = t_file + 1; x < 8; ++x) {

            if (1ULL << (t_rank * 8 + x) & kWBlock) break;
            else if (1ULL << (t_rank * 8 + x) & kBRookQueenBlock) return true;
            else if (1ULL << (t_rank * 8 + x) & kBBlock) break;
        }

        for (int x = t_file - 1; x > -1; x--) {

            if (1ULL << (t_rank * 8 + x) & kWBlock) break;
            else if (1ULL << (t_rank * 8 + x) & kBRookQueenBlock) return true;
            else if (1ULL << (t_rank * 8 + x) & kBBlock) break;
        }
    }

    else {

        int square = __builtin_ctzll(b.bb[12]);

        const int t_rank = square / 8;
        const int t_file = square % 8;

        // Diagonal
        for (int x = t_rank + 1, y = t_file + 1; x < 8 && y < 8; ++x, ++y) {

            if (1ULL << (x * 8 + y) & kBBlock) break;
            else if (1ULL << (x * 8 + y) & kWBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kWBlock) break;
        }

        for (int x = t_rank - 1, y = t_file + 1; x > -1 && y < 8; x--, ++y) {

            if (1ULL << (x * 8 + y) & kBBlock) break;
            else if (1ULL << (x * 8 + y) & kWBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kWBlock) break;
        }

        for (int x = t_rank + 1, y = t_file - 1; x < 8 && y > -1; ++x, y--) {

            if (1ULL << (x * 8 + y) & kBBlock) break;
            else if (1ULL << (x * 8 + y) & kWBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kWBlock) break;
        }

        for (int x = t_rank - 1, y = t_file - 1; x > -1 && y > -1; x--, y--) {

            if (1ULL << (x * 8 + y) & kBBlock) break;
            else if (1ULL << (x * 8 + y) & kWBishopQueenBlock) return true;
            else if (1ULL << (x * 8 + y) & kWBlock) break;
        }


        // Straight
        for (int y = t_rank + 1; y < 8; ++y) {

            if (1ULL << (y * 8 + t_file) & kBBlock) break;
            else if (1ULL << (y * 8 + t_file) & kWRookQueenBlock) return true;
            else if (1ULL << (y * 8 + t_file) & kWBlock) break;
        }

        for (int y = t_rank - 1; y > -1; y--) {

            if (1ULL << (y * 8 + t_file) & kBBlock) break;
            else if (1ULL << (y * 8 + t_file) & kWRookQueenBlock) return true;
            else if (1ULL << (y * 8 + t_file) & kWBlock) break;
        }

        for (int x = t_file + 1; x < 8; ++x) {

            if (1ULL << (t_rank * 8 + x) & kBBlock) break;
            else if (1ULL << (t_rank * 8 + x) & kWRookQueenBlock) return true;
            else if (1ULL << (t_rank * 8 + x) & kWBlock) break;
        }

        for (int x = t_file - 1; x > -1; x--) {

            if (1ULL << (t_rank * 8 + x) & kBBlock) break;
            else if (1ULL << (t_rank * 8 + x) & kWRookQueenBlock) return true;
            else if (1ULL << (t_rank * 8 + x) & kWBlock) break;
        }
    }

    return false;
}


// Bit Manipulation
inline int BitCount(U64 x) {

	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

	return ((x * 0x0101010101010101) >> 56);
}
inline int PopLsb(U64& b) {

	const int kS = __builtin_ctzll(b);
	b &= b - 1;

	return kS;
}


inline void InitAll(Board& b, bool& kSide, double& max_search_time) {

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

	InitTransposition();
}
inline bool InitSide() {

	char ch;

	std::cout << "Player Side W/B: ";
	std::cin >> ch;

	return ((ch == 'W' || ch == 'w') ? true : false);
}
inline double InitMaxSearchTime() {

	double max_search_time;

	std::cout << "Max Search Time (s): ";
	std::cin >> max_search_time;

	return max_search_time;
}



// Hashing
inline unsigned XorShift32(unsigned& x) {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

inline U64 XorShift64(unsigned& x) {
    	U64 ret = XorShift32(x);
	ret = ret << 32;
	ret |= XorShift32(x);
	return ret;
}

inline void InitTransposition() {

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 64; ++j) {
            piece_hash[i][j] = XorShift64(key);
        }
    }

    for (int i = 0; i < 16; ++i) {
        castle_hash[i] = XorShift64(key);
    }

    for (int i = 0; i < 64; ++i) {
        en_passant_hash[i] = XorShift64(key);
    }

    side_hash = XorShift64(key);
}


inline U64 Zobrist(Board& b, const bool kSide) {

    U64 ret = 0;

    U64 bitboard = b.bb[1];
    while (bitboard) ret ^= piece_hash[1][PopLsb(bitboard)];
    bitboard = b.bb[2];
    while (bitboard) ret ^= piece_hash[2][PopLsb(bitboard)];
    bitboard = b.bb[3];
    while (bitboard) ret ^= piece_hash[3][PopLsb(bitboard)];
    bitboard = b.bb[4];
    while (bitboard) ret ^= piece_hash[4][PopLsb(bitboard)];
    bitboard = b.bb[5];
    while (bitboard) ret ^= piece_hash[5][PopLsb(bitboard)];
    bitboard = b.bb[6];
    while (bitboard) ret ^= piece_hash[6][PopLsb(bitboard)];
    
    bitboard = b.bb[7];
    while (bitboard) ret ^= piece_hash[7][PopLsb(bitboard)];
    bitboard = b.bb[8];
    while (bitboard) ret ^= piece_hash[8][PopLsb(bitboard)];
    bitboard = b.bb[9];
    while (bitboard) ret ^= piece_hash[9][PopLsb(bitboard)];
    bitboard = b.bb[10];
    while (bitboard) ret ^= piece_hash[10][PopLsb(bitboard)];
    bitboard = b.bb[11];
    while (bitboard) ret ^= piece_hash[11][PopLsb(bitboard)];
    bitboard = b.bb[12];
    while (bitboard) ret ^= piece_hash[12][PopLsb(bitboard)];
 
    ret ^= castle_hash[GET_HASH_CASTLING(b.bb[0])];
    ret ^= kSide * (side_hash);
    ret ^= en_passant_hash[GET_UTILITY_EN_PASSANT(b.bb[0])];

    return ret;
}




/* -------------------------------------------------- Move Generation --------------------------------------------------*/

const U64 kNotAFile = 18374403900871474942ULL;
const U64 kNotHFile = 9187201950435737471ULL;
const U64 kNotABFile = 18229723555195321596ULL;
const U64 kNotGHFile = 4557430888798830399ULL;

const U64 kWCastleShortSpaceMask = 6917529027641081856ULL;
const U64 kWCastleLongSpaceMask = 1008806316530991104ULL;
const U64 kBCastleShortSpaceMask = 96ULL;
const U64 kBCastleLongSpaceMask = 14ULL;

const U64 kWCastleShortPawnMask = 69805794224242688ULL;
const U64 kWCastleShortKnightMask = 62197173760032768ULL;
const U64 kWCastleShortKingMask = 18014398509481984ULL;

const U64 kWCastleLongPawnMask = 17451448556060672ULL;
const U64 kWCastleLongKnightMask = 33563691949490176ULL;
const U64 kWCastleLongKingMask = 1688849860263936ULL;


const U64 kBCastleShortPawnMask = 63488ULL;
const U64 kBCastleShortKnightMask = 16309248ULL;
const U64 kBCastleShortKingMask = 16384ULL;

const U64 kBCastleLongPawnMask = 15872ULL;
const U64 kBCastleLongKnightMask = 4093696ULL;
const U64 kBCastleLongKingMask = 1536ULL;



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


	// Promotion
	if (rank == 1) {

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


	// Promotion
	if (rank == 6) {

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


inline void GenerateMoves(const U64 kBB[13], U64 moves[100], const bool kSide) {

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

inline void GenerateCaptures(const U64 kBB[13], U64 moves[100], const bool kSide) {

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



/* -------------------------------------------------- Evaluation --------------------------------------------------*/

const int kMaterialScore[13] = { 0, 1000, 3000, 3000, 5000, 9000, 100000, -1000, -3000, -3000, -5000, -9000, -100000 };
const int kPositionScore[13][64] = {

	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},










	{
	90,  90,  90,  90,  90,  90,  90,  90,
	30,  30,  30,  40,  40,  30,  30,  30,
	20,  20,  20,  30,  30,  30,  20,  20,
	10,  10,  10,  20,  20,  10,  10,  10,
	 5,   5,  10,  25,  25,   5,   5,   5,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5, -10,   0,   0,   0,   0, -10,  -5
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,   0, -10,   0,   0, -10,   0,   0
	},


	{
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  20,  20,   0,   0,   0
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,   0, -15,   0,  10,   0
	},










	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 5,   5,  10,  25,  25,   5,   5,   5,
	10,  10,  10,  20,  20,  10,  10,  10,
	20,  20,  20,  30,  30,  30,  20,  20,
	30,  30,  30,  40,  40,  30,  30,  30,
	90,  90,  90,  90,  90,  90,  90,  90
	},


	{
	-5, -10,   0,   0,   0,   0, -10,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5
	},


	{
	 0,   0, -10,   0,   0, -10,   0,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	 0,   0,   0,  20,  20,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	 0,   0,   5,   0, -15,   0,  10,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	}
};



inline int MaterialScore(const U64 kBB[13]) {

	int total = 0;

	for (int board = 1; board < 7; ++board) {
		total += kMaterialScore[board] * BitCount(kBB[board]);
		total += kMaterialScore[board + 6] * BitCount(kBB[board + 6]);
	}

	return total;
}

inline int PositionScore(const U64 kBB[13]) {

	int total = 0;
	U64 pieceBitboard;

	for (int i = 1; i < 7; i++) {

		// white pieces
		pieceBitboard = kBB[i];

		while (pieceBitboard) {
			int location = PopLsb(pieceBitboard);
			total += kPositionScore[i][location];
		}


		// black pieces
		pieceBitboard = kBB[i + 6];

		while (pieceBitboard) {
			int location = PopLsb(pieceBitboard);
			total -= kPositionScore[i + 6][location];
		}
	}

	return total;
}


inline int Evaluate(const U64 kBB[13]) {

	int evaluation = 0;

	evaluation += MaterialScore(kBB);
	evaluation += PositionScore(kBB);

	return evaluation;
}



/* -------------------------------------------------- Search --------------------------------------------------*/

const U64 kTimeFlag = 9223372036854775808ULL;
const int kR = 2;
const int kMVVLVA[13][13] = {
  0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,
  0,  105, 205, 305, 405, 505, 605,  105, 205, 305, 405, 505, 605,
  0,  104, 204, 304, 404, 504, 604,  104, 204, 304, 404, 504, 604,
  0,  103, 203, 303, 403, 503, 603,  103, 203, 303, 403, 503, 603,
  0,  102, 202, 302, 402, 502, 602,  102, 202, 302, 402, 502, 602,
  0,  101, 201, 301, 401, 501, 601,  101, 201, 301, 401, 501, 601,
  0,  100, 200, 300, 400, 500, 600,  100, 200, 300, 400, 500, 600,

  0,  105, 205, 305, 405, 505, 605,  105, 205, 305, 405, 505, 605,
  0,  104, 204, 304, 404, 504, 604,  104, 204, 304, 404, 504, 604,
  0,  103, 203, 303, 403, 503, 603,  103, 203, 303, 403, 503, 603,
  0,  102, 202, 302, 402, 502, 602,  102, 202, 302, 402, 502, 602,
  0,  101, 201, 301, 401, 501, 601,  101, 201, 301, 401, 501, 601,
  0,  100, 200, 300, 400, 500, 600,  100, 200, 300, 400, 500, 600
};



inline void IterativeDeepening(Board& b, const bool kSide, const double kMaxTime, int& evaluation_out, U64& move_out, const bool kEndGame, std::unordered_map<U64, U64>& hash);

inline std::pair<int, U64> LayerOneNegaMax(Board& b, const int kDepth, const bool kSide, const double kMaxTime, std::unordered_map<U64, U64>& hash);
inline int NegaMax(Board& b, const int kDepth, const bool kSide, int alpha, int beta, std::unordered_map<U64, U64>& hash);
inline int Quiescence(Board& b, const int kDepth, const bool kSide, int alpha, int beta);

bool end_game = false;



inline void IterativeDeepening(Board& b, const bool kSide, const double kMaxTime, int& evaluation_out, U64& move_out, const bool kEndGame, std::unordered_map<U64, U64>& hash) {

    end_game = kEndGame;

    pair<int, U64> search_data;

    for (int depth = 1; depth < 256; ++depth) {

        duration<double> time;
        time_point<high_resolution_clock> start_time = high_resolution_clock::now();

        search_data = LayerOneNegaMax(b, depth, kSide, kMaxTime, hash);

        time = high_resolution_clock::now() - start_time;


        if (!(search_data.second == kTimeFlag)) {

            evaluation_out = search_data.first;
            move_out = search_data.second;


            cout << depth << " ";

            cout << "[ ";

            cout << time.count();

            cout << " ]   ";

        }


        if (search_data.second == kTimeFlag || time.count() > 0.2 * kMaxTime) return;

        if (time.count() < kMaxTime / 100) ++depth;
    }
}

inline pair<int, U64> LayerOneNegaMax(Board& b, const int kDepth, const bool kSide, const double kMaxTime, std::unordered_map<U64, U64>& hash) {

    duration<double> time;
    time_point<high_resolution_clock> start_time = high_resolution_clock::now();

    int alpha = -999999;
    int beta = 999999;
    U64 best_move;
    U64 moves[100];
    moves[99] = 0;

    GenerateMoves(b.bb, moves, kSide);
    GetMoveTargets(b, moves, kSide);
	sort(moves, moves + moves[99], [](const U64 c, const U64 d) {return kMVVLVA[GET_MOVE_PIECE(c)][GET_MOVE_CAPTURE(c)] > kMVVLVA[GET_MOVE_PIECE(d)][GET_MOVE_CAPTURE(d)]; });


    Board b_copy;

    for (int i = 0; i < moves[99]; ++i) {

        if ((1ULL << GET_MOVE_TARGET(moves[i])) & b.bb[6] || (1ULL << GET_MOVE_TARGET(moves[i])) & b.bb[12]) return { 100000 + kDepth, moves[i] };

        b_copy = b;
        MakeMove(b_copy.bb, moves[i], kSide);

        int score = -NegaMax(b_copy, kDepth - 1, !kSide, -beta, -alpha, hash);

        if (score > alpha) {
            alpha = score;
            best_move = moves[i];
        }

        if ((time = high_resolution_clock::now() - start_time).count() > kMaxTime) return { 0, kTimeFlag };
    }

    return { alpha, best_move };
}

inline int NegaMax(Board& b, const int kDepth, const bool kSide, int alpha, int beta, std::unordered_map<U64, U64>& hash) {
	
	// Transposition Table
	U64 key = Zobrist(b, kSide);
	if (hash.find(key) != hash.end() && GET_HASH_DEPTH(hash[key]) >= kDepth) return GET_HASH_EVAL(hash[key]);

	if (!kDepth) return Quiescence(b, 4, kSide, alpha, beta);

    // Null Move Heuristic
    if (kDepth >= 3 && !end_game && !InCheck(b, kSide)) {

        Board b_copy = b;
        int eval = -NegaMax(b_copy, kDepth - 1 - kR, !kSide, -beta, -beta + 1, hash);
        if (eval >= beta) { 
		hash[key] = ENCODE_HASH(beta, kDepth);
		return beta;
	}
    }

    U64 moves[100];
    moves[99] = 0;

   	GenerateMoves(b.bb, moves, kSide);
   	GetMoveTargets(b, moves, kSide);
	sort(moves, moves + moves[99], [](const U64 c, const U64 d) {return kMVVLVA[GET_MOVE_PIECE(c)][GET_MOVE_CAPTURE(c)] > kMVVLVA[GET_MOVE_PIECE(d)][GET_MOVE_CAPTURE(d)]; });


    Board b_copy;

    for (int i = 0; i < moves[99]; ++i) {

        if ((1ULL << GET_MOVE_TARGET(moves[i])) & b.bb[6] || (1ULL << GET_MOVE_TARGET(moves[i])) & b.bb[12]) return (100000 + kDepth);

        b_copy = b;
        MakeMove(b_copy.bb, moves[i], kSide);

        int score = -NegaMax(b_copy, kDepth - 1, !kSide, -beta, -alpha, hash);

        if (score > alpha) {
            alpha = score;

            if (score >= beta) {
		hash[key] = ENCODE_HASH(beta, kDepth);
                return beta;
            }
        }
    }

	hash[key] = ENCODE_HASH(alpha, kDepth);
	return alpha;
}

inline int Quiescence(Board& b, const int kDepth, const bool kSide, int alpha, int beta) {

    if (kDepth == 0) return kSide ? Evaluate(b.bb) : -Evaluate(b.bb);

    int eval = kSide ? Evaluate(b.bb) : -Evaluate(b.bb);
    if (eval >= beta) return beta;
    if (eval > alpha) alpha = eval;

    U64 moves[100];
    moves[99] = 0;

    GenerateCaptures(b.bb, moves, kSide);
    GetMoveTargets(b, moves, kSide);
	sort(moves, moves + moves[99], [](const U64 c, const U64 d) {return kMVVLVA[GET_MOVE_PIECE(c)][GET_MOVE_CAPTURE(c)] > kMVVLVA[GET_MOVE_PIECE(d)][GET_MOVE_CAPTURE(d)]; });


    Board b_copy;

    for (int i = 0; i < moves[99]; ++i) {

        if ((1ULL << GET_MOVE_TARGET(moves[i])) & b.bb[6] || (1ULL << GET_MOVE_TARGET(moves[i])) & b.bb[12]) return (100000 + kDepth);

        b_copy = b;
        MakeMove(b_copy.bb, moves[i], kSide);

        int score = -Quiescence(b_copy, kDepth - 1, !kSide, -beta, -alpha);

        if (score > alpha) {
            alpha = score;

            if (score >= beta) {
                return beta;
            }
        }
    }

    return alpha;
}



/* -------------------------------------------------- UI --------------------------------------------------*/

const double kMaxSearchTime = 4.0;

const char piece[13] = { ' ', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k' };
const char character[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
const int reverse_int[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };



// Play Bot
void PlayBot();

void BotMove(Board& b, int& evaluation, U64& move, const bool kSide, const double kMaxSearchTime, std::unordered_map<U64, U64>& hash);
void UserMove(int& ply, Board& b, U64& move, const bool kSide, bool& back);
void SaveState(const int kPly, Board& b, const int kEval, const U64 move);
void LoadState(const int kPly, Board& b, int& evaluation, U64& move);


// User Interaction
std::pair<int, int> UserInputMove();
void InputFen(Board& b);

// Interface
void PrintBoard(const char kBoard[64], const int kSource, const int kTarget);
void PrintState(Board& b, const int kEval, const U64 kNextMove, const int kPly);

// Translation
U64 TranslateToMove(Board& b, const int kSource, const int kTarget, const bool kSide);
std::string MoveToNotation(const U64 kMove);
int StringToSquare(const std::string kStr);

// Verify Move
bool VerifyMove(Board& b, const U64 KMove, const bool kSide);

// FEN
void ParseFen(Board& b, std::string& fen);
void PrintFen(Board& b, const bool kSide);



map<char, int> file_index = {
	{'a', 0},
	{'b', 1},
	{'c', 2},
	{'d', 3},
	{'e', 4},
	{'f', 5},
	{'g', 6},
	{'h', 7}
};
map<char, int> bitboard_index = {
	{'P', 1},
	{'N', 2},
	{'B', 3},
	{'R', 4},
	{'Q', 5},
	{'K', 6},

	{'p', 7},
	{'n', 8},
	{'b', 9},
	{'r', 10},
	{'q', 11},
	{'k', 12}
};

// Saves
Board boards[400];
int evaluations[400] = {};
U64 moves[400] = {};
bool side[400];
bool player_turn[400];



void PlayBot() {

	// Initialize Board && Side
	Board b;
	bool player_side;
	double max_search_time;
	InitAll(b, player_side, max_search_time);

	// Initialize Transposition Table
	std::unordered_map<U64, U64> hash;

	InputFen(b);
	bool raw_side = GET_UTILITY_SIDE(b.bb[0]);


	// Initialize Saves
	if (raw_side) side[0] = true;
	else side[0] = false;

	if (player_side && side[0] || !player_side && !side[0]) player_turn[0] = true;
	else player_turn[0] = false;

	for (int i = 1; i < 400; ++i) {
		side[i] = !side[i - 1];
		player_turn[i] = !player_turn[i - 1];
	}

	SaveState(0, b, 0, 0);


	// Initialize Other Variables
	int ply = 0;
	int evaluation = 0;
	U64 move = 0;
	bool back = false;



	while (true) {
		
		back = false;

		if (player_turn[ply]) {
			UserMove(ply, b, move, side[ply], back);
		}

		else {
			BotMove(b, evaluation, move, side[ply], max_search_time, hash);
			PrintState(b, evaluation, move, ply);
		}

		if (back) { ply -= 2; LoadState(ply, b, evaluation, move); }
		else {
			++ply;
			SaveState(ply, b, evaluation, move);
		}
	}
}

void BotMove(Board& b, int& eval, U64& move, const bool kSide, const double kMaxSearchTime, std::unordered_map<U64, U64>& hash) {

	IterativeDeepening(b, kSide, kMaxSearchTime, eval, move, (BitCount(W_BLOCK(b.bb) | B_BLOCK(b.bb)) < 15), hash);
	MakeMove(b.bb, move, kSide);
}

void UserMove(int& ply, Board& b, U64& move, const bool kSide, bool& back) {

	while (true) {

		std::cout << "Write 'help' for the command list\n";

		std::string user_input;
		std::cin >> user_input;

		if (user_input == "help") {
			std::cout << "-------------------- Commands --------------------\n";
			std::cout << "help:       Display this message\n";
			std::cout << "l:          list playable moves\n";
			std::cout << "r:          Go back one move\n";
			std::cout << "Write two squares to play a move. (I.E: e2e4)\n";

			continue;
		}

		else if (user_input[0] == 'l' && user_input.size() == 1) {

			U64 moves[100];
			moves[99] = 0;
			GenerateMoves(b.bb, moves, kSide);
			GetMoveTargets(b, moves, kSide);

			std::cout << "---------- Playable Moves ----------\n";
			for (int i = 0; i < moves[99]; ++i) {
				std::cout << MoveToNotation(moves[i]) << "          ";
				if (i % 3 == 2) std::cout << '\n';
			}
			if (moves[99] % 3 ) std::cout << '\n';

			continue;
		}

		else if (user_input[0] == 'r' && user_input.size() == 1) {

			if (ply < 2) {
				std::cout << "Cannot go back further\n";
				continue;
			}

			else {
				back = true;
				break;
			}
		}

		else if (user_input.size() == 4
						&& file_index.find(user_input[0]) != file_index.end() && file_index.find(user_input[2]) != file_index.end()
						&& !(user_input[1] < 48) && !(user_input[3] < 48)
						&& !(user_input[1] > 57) && !(user_input[3] > 57)) {

			std::string source = "", target = "";
			source += user_input[0]; source += user_input[1];
			target += user_input[2]; target += user_input[3];

			move = TranslateToMove(b, StringToSquare(source), StringToSquare(target), kSide);
			if (VerifyMove(b, move, kSide)) {
				MakeMove(b.bb, move, kSide);
				break;
			}
		}

		std::cout << "Invalid Move\n";
	}

	return;
}

void SaveState(const int kPly, Board& b, const int kEval, const U64 kMove) {

	boards[kPly] = b;
	evaluations[kPly] = kEval;
	moves[kPly] = kMove;
}

void LoadState(const int kPly, Board& b, int& eval, U64& move) {

	b = boards[kPly];
	eval = evaluations[kPly];
	move = moves[kPly];
}


// Translation
U64 TranslateToMove(Board& b, const int kSource, const int kTarget, const bool kSide) {

	int piece = 0;
	int capture = 0;
	int promotion = 0;
	int _2pawn = 0;
	int en_passant = 0;
	int castle = 0;


	if (kSide) {

		// piece
		for (int i = 1; i < 7; ++i) {
			if (b.bb[i] & 1ULL << kSource) { piece = i; break; }
		}

		// capture
		for (int i = 7; i < 13; ++i) { if (b.bb[i] & 1ULL << kTarget) { capture = i; break; } }

		// promotion
		if (piece == 1 && kTarget / 8 == 0) promotion = 5;

		// 2 pawn
		else if (piece == 1 && kSource / 8 == 6 && kTarget / 8 == 4) _2pawn = 1;

		// en passant
		else if (piece == 1 && ((kSource % 8) != (kTarget % 8)) && !(B_BLOCK(b.bb) & 1ULL << kTarget)) en_passant = 1;

		// castle
		else if (piece == 6 && abs(kSource % 8 - kTarget % 8) == 2) castle = 1;
	}

	else {

		// piece
		for (int i = 7; i < 13; ++i) {
			if (b.bb[i] & 1ULL << kSource) { piece = i; break; }
		}

		// capture
		for (int i = 1; i < 7; ++i) { if (b.bb[i] & 1ULL << kTarget) { capture = i; break; } }


		// promotion
		if (piece == 7 && kTarget / 8 == 7) promotion = 11;

		// 2 pawn
		else if (piece == 7 && kSource / 8 == 1 && kTarget / 8 == 3) _2pawn = 1;

		// en passant
		else if (piece == 7 && ((kSource % 8) != (kTarget % 8)) && !(W_BLOCK(b.bb) & (1ULL << kTarget))) en_passant = 1;

		// castle
		else if (piece == 12 && abs(kSource % 8 - kTarget % 8) == 2) castle = 1;
	}


	return ENCODE_MOVE(kSource, kTarget, piece, capture, promotion, _2pawn, en_passant, castle);
}
std::string MoveToNotation(const U64 kMove) {

	map<int, char> notation_index = {
		{0, 'a'},
		{1, 'b'},
		{2, 'c'},
		{3, 'd'},
		{4, 'e'},
		{5, 'f'},
		{6, 'g'},
		{7, 'h'}
	};

	string notation;

	int from = GET_MOVE_SOURCE(kMove);
	int to = GET_MOVE_TARGET(kMove);


	notation += notation_index.at(from % 8);
	notation += to_string(8 - (from / 8 + 1) + 1);

	notation += " -> ";

	notation.push_back(notation_index.at(to % 8));
	notation += to_string(8 - (to / 8 + 1) + 1);

	return notation;
}
int StringToSquare(const string kStr) {

	map<char, int> square_index = {
		{'a', 0},
		{'b', 1},
		{'c', 2},
		{'d', 3},
		{'e', 4},
		{'f', 5},
		{'g', 6},
		{'h', 7}
	};

	int square = 0;

	square += square_index.at(kStr[0]);
	square += (8 - (kStr[1] - '0')) * 8;

	return square;
}


// User Interaction
void InputFen(Board& b) {

	string fen;
	cout << "FEN: ";
	fflush(stdin);
	for (int i = 0; i < 6; ++i) {
		string tmp;
		cin >> tmp;
		if (tmp == "x" || tmp == "X") return;
		fen += tmp;
		fen += " ";
	}
	//getline(cin, fen, '\n');


	for (int bitboard = 0; bitboard < 13; ++bitboard) {
		b.bb[bitboard] = 0ULL;
	}

	ParseFen(b, fen);
}


// Interface
void PrintBoard(const char kBoard[64], const int kSource, const int kTarget) {

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (!y) {

				cout << "  " << 8 - x << "  ";
			}

			int square = x * 8 + y;

			if (square == kSource || square == kTarget) {

				cout << "   ";

				if (!kBoard[square]) cout << " ";
				else cout << kBoard[square];

			}
			else if (kBoard[square]) cout << "   " << kBoard[square];
			else cout << "    ";
		}
		cout << "\n\n";
	}

	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";
}
void PrintState(Board& b, const int kEval, const U64 kNextMove, const int kPly) {

	map<int, char> piece_index = {
		{1, 'P'},
		{2, 'H'},
		{3, 'B'},
		{4, 'R'},
		{5, 'Q'},
		{6, 'K'},

		{7, 'p'},
		{8, 'h'},
		{9, 'b'},
		{10, 'r'},
		{11, 'q'},
		{12, 'k'}
	};

	char board[64] = "\0";
	//U64 temp;
	//int square;

	cout << "\nPly: " << kPly;
	cout << "\nMove: ";
	cout << MoveToNotation(kNextMove) << "\n";

	cout << "Evaluation: ";
	cout << ((double)kEval) / 1000 << "\n\n";


	// Fill Board
	for (int i = 1; i < 13; ++i) {
		for (int square = 0; square < 64; ++square) {
			if (1ULL << square & b.bb[i]) board[square] = piece_index.at(i);
		}

		/*temp = b.bb[i];

		while (temp) {
			square = countr_zero(temp);
			POP_BIT(temp, square);
			board[square] = piece_index.at(i);
		}*/
	}


	// Print Board
	PrintBoard(board, GET_MOVE_SOURCE(kNextMove), GET_MOVE_TARGET(kNextMove));


	// Print State
	cout << "\nFEN: ";
	PrintFen(b, player_turn[kPly + 1]);
	cout << "\n";

	// cout << "\nState: ";
	// cout << (b.side ? 'b' : 'w') << "/";
	// for (int i = 0; i < 13; ++i) cout << b.bb[i] << "/";
	// cout << "\n";
}


// Verify Move
bool VerifyMove(Board& b, const U64 kMove, const bool kSide) {

	U64 moves[100];
	moves[99] = 0;

	GenerateMoves(b.bb, moves, kSide);
	GetMoveTargets(b, moves, kSide);

	for (int i = 0; i < moves[99]; ++i) {
		if (moves[i] == kMove) return true;
	}

	return false;
}


// FEN
void ParseFen(Board& b, string& fen) {


	int stage = 0;
	string en_passant_square;

	int square = 0;
	for (int i = 0; i < 100; ++i) {

		if (fen[i] == ' ') ++stage;


		if (!stage) {

			if (fen[i] == '/') continue;
			else if (isdigit(fen[i])) square += fen[i] - '0';
			else {
				b.bb[bitboard_index[fen[i]]] |= 1ULL << square;
				++square;
			}
		}

		else if (stage == 1) {
			fen[++i] == 'w' ? b.bb[0] |= 1ULL << 10 : b.bb[0] &= ~(1ULL << 10);
		}

		else if (stage == 2) {

			if (fen[i] == 'K') b.bb[0] |= 1ULL << 6;
			else if (fen[i] == 'Q') b.bb[0] |= 1ULL << 7;
			else if (fen[i] == 'k') b.bb[0] |= 1ULL << 8;
			else if (fen[i] == 'q') b.bb[0] |= 1ULL << 9;
		}

		else if (stage == 3) {

			if (fen[i + 1] == '-') break;
			else {
				en_passant_square += fen[i + 1];
				en_passant_square += fen[i + 2];

				b.bb[0] |= StringToSquare(en_passant_square);
				break;
			}
		}
	}
}
void PrintFen(Board& b, const bool kSide) {

	string fen;

	for (int rank = 0; rank < 8; ++rank) {

		int count = 0;
		for (int file = 0; file < 8; ++file) {

			bool found = false;
			for (int bitboard = 1; bitboard < 13; ++bitboard) {
				if (b.bb[bitboard] & 1ULL << (rank * 8 + file)) {

					if (count) {
						fen += count + '0';
						count = 0;
					}

					fen += piece[bitboard];
					found = true;
				}
			}

			if (!found) ++count;
			if (file == 7 && count) fen += count + '0';
		}

		if (rank != 7) fen += '/';
	}


	fen += ' ';
	kSide ? fen += 'w' : fen += 'b';
	fen += ' ';


	if (GET_UTILITY_W_SHORT_CASTLE(b.bb[0])) fen += 'K';
	if (GET_UTILITY_W_LONG_CASTLE(b.bb[0])) fen += 'Q';
	if (GET_UTILITY_B_SHORT_CASTLE(b.bb[0])) fen += 'k';
	if (GET_UTILITY_B_LONG_CASTLE(b.bb[0])) fen += 'q';
	fen += ' ';


	string en_passant_notation;
	int en_passant_square = GET_UTILITY_EN_PASSANT(b.bb[0]);

	if (en_passant_square) {
		en_passant_notation += character[en_passant_square % 8];
		en_passant_notation += reverse_int[en_passant_square / 8] + '0';
		fen += en_passant_notation;
	}
	else fen += '-';


	// temp
	fen += " - -";


	cout << fen << "\n";
}






int main() {

	PlayBot();





	return 0;
}
