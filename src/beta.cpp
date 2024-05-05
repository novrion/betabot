#include "beta.h"


std::map<char, int> file_index = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7}
};



void PlayBot() {
	clear_ui();

	// Saves 
	Board boards[400];
	int evaluations[400] = {};
	U64 moves[400] = {};
	bool side[400];
	bool player_turn[400];

	// Initialize Board && Side
	Board b;
	bool player_side;
	double max_search_time;
	InitAll(b, player_side, max_search_time);

	InputFen(b);
	bool raw_side = GET_UTILITY_SIDE(b.bb[0]);

	PrintTutorial();

	// Initialize Saves
	if (raw_side) side[0] = true;
	else side[0] = false;

	if (player_side && side[0] || !player_side && !side[0]) player_turn[0] = true;
	else player_turn[0] = false;

	for (int i = 1; i < 400; ++i) {
		side[i] = !side[i - 1];
		player_turn[i] = !player_turn[i - 1];
	}

	SaveState(boards, evaluations, moves, 0, b, 0, 0);

	// Initialize Other Variables
	int ply = 0;
	int evaluation = 0;
	U64 move = 0;
	bool back = false;


	while (true) {
		back = false;

		if (player_turn[ply]) {
			UserMove(ply, b, move, side[ply], back);
		} else {
			BotMove(b, evaluation, move, side[ply], max_search_time);
			PrintState(b, evaluation, move, ply, player_turn);
		}

		if (back) {
			ply -= 2;
			LoadState(boards, evaluations, moves, ply, b, evaluation, move);
			PrintState(b, evaluations[ply], moves[ply], ply, player_turn);
		} else {
			++ply;
			SaveState(boards, evaluations, moves, ply, b, evaluation, move);
		}
	}
}

inline void BotMove(Board& b, int& eval, U64& move, const bool kSide, const double kMaxSearchTime) {
	IterativeDeepening(b, kSide, kMaxSearchTime, eval, move, (BitCount(W_BLOCK(b.bb) | B_BLOCK(b.bb)) < 15));
	MakeMove(b.bb, move, kSide);
}

inline void UserMove(int& ply, Board& b, U64& move, const bool kSide, bool& back) {
	while (true) {
		std::cout << ": ";
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
			} else {
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

inline void SaveState(Board boards[400], int evaluations[400], U64 moves[400], const int kPly, Board& b, const int kEval, const U64 kMove) {
	boards[kPly] = b;
	evaluations[kPly] = kEval;
	moves[kPly] = kMove;
}

inline void LoadState(Board boards[400], int evaluations[400], U64 moves[400], const int kPly, Board& b, int& eval, U64& move) {
	b = boards[kPly];
	eval = evaluations[kPly];
	move = moves[kPly];
}


inline bool VerifyMove(Board& b, const U64 kMove, const bool kSide) {
	U64 moves[100];
	moves[99] = 0;

	GenerateMoves(b.bb, moves, kSide);
	GetMoveTargets(b, moves, kSide);

	for (int i = 0; i < moves[99]; ++i) {
		if (moves[i] == kMove) return true;
	}

	return false;
}


inline U64 TranslateToMove(Board& b, const int kSource, const int kTarget, const bool kSide) {
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
