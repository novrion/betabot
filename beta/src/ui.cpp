#include "ui.h"

using namespace std;



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

	InputFen(b);
	bool raw_side = GET_UTILITY_SIDE(b.bb[0]);


	// Initialize Saves
	if (raw_side) side[1] = true;
	else side[1] = false;

	if (player_side && side[1] || !player_side && !side[1]) player_turn[1] = true;
	else player_turn[1] = false;

	for (int i = 2; i < 400; ++i) {
		side[i] = !side[i - 1];
		player_turn[i] = !player_turn[i - 1];
	}

	// Initialize Other Variables
	int ply = 1;
	int evaluation = 0;
	U64 move = 0;
	bool back = false;



	while (true) {

		if (back) PrintState(boards[ply - 1], evaluations[ply - 1], moves[ply - 1], ply - 1);
		back = false;


		if (!player_turn[ply]) {

			BotMove(b, evaluation, move, side[ply], max_search_time);
			SaveState(ply, b, evaluation, move);

			PrintState(b, evaluation, move, ply);
		}

		else {

			UserMove(ply, b, evaluation, move, side[ply], back);
			SaveState(ply, b, evaluation, move);

			system("cls");
		}


		if (back) ply -= 2;
		else ++ply;
	}
}

void BotMove(Board& b, int& eval, U64& move, const bool kSide, const double kMaxSearchTime) {

	IterativeDeepening(b, kSide, kMaxSearchTime, eval, move, (BitCount(W_BLOCK(b.bb) | B_BLOCK(b.bb)) < 15));
	MakeMove(b.bb, move, kSide);
}

void UserMove(int& ply, Board& b, int& eval, U64& move, const bool kSide, bool& back) {

	pair<int, int> input = UserInputMove();
	if (input.first == -1 && ply > 1) {
		LoadState(ply - 3, b, eval, move);

		back = true;
		return;
	}


	move = TranslateToMove(b, input.first, input.second, kSide);

	if (VerifyMove(b, move, kSide)) MakeMove(b.bb, move, kSide);
	else {
		cout << "Invalid Move.\n";
		UserMove(ply, b, eval, move, kSide, back);
	}
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
		if (B_BLOCK(b.bb) & 1ULL << kTarget) capture = 1;


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
		if (W_BLOCK(b.bb) & 1ULL << kTarget) capture = 1;


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
string MoveToNotation(const U64 kMove) {

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
pair<int, int> UserInputMove() {

	string from, to;

	cout << "\nFrom: ";
	cin >> from;
	if (from == "r") return { -1, -1 };

	cout << "To: ";
	cin >> to;

	cout << "\n";
	
	if (from.size() != 2 || to.size() != 2 || file_index.find(from[0]) == file_index.end() || file_index.find(to[0]) == file_index.end() || from[1] < 48 || from[1] > 57 || to[1] < 48 || to[1] > 57) return {-1, -1};
	return { StringToSquare(from), StringToSquare(to) };
}
void InputFen(Board& b) {

	string fen;
	cout << "FEN: ";
	fflush(stdin);
	getline(cin, fen);

	if (fen != "x") {

		for (int bitboard = 0; bitboard < 13; ++bitboard) {
			b.bb[bitboard] = 0ULL;
		}

		ParseFen(b, fen);
	}
}


// Interface
void PrintBoard(const char kBoard[64], const int kSource, const int kTarget) {

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (!y) {

				SetConsoleTextAttribute(hConsole, 11);
				cout << "  " << 8 - x << "  ";
				SetConsoleTextAttribute(hConsole, 15);
			}

			int square = x * 8 + y;

			if (square == kSource || square == kTarget) {

				cout << "   ";
				square == kSource ? SetConsoleTextAttribute(hConsole, 47) : SetConsoleTextAttribute(hConsole, 79);

				if (!kBoard[square]) cout << " ";
				else cout << kBoard[square];

				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (kBoard[square]) cout << "   " << kBoard[square];
			else cout << "    ";
		}
		cout << "\n\n";
	}

	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";
	SetConsoleTextAttribute(hConsole, 15);
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
	SetConsoleTextAttribute(hConsole, 10);
	cout << MoveToNotation(kNextMove) << "\n";
	SetConsoleTextAttribute(hConsole, 15);

	cout << "Evaluation: ";
	SetConsoleTextAttribute(hConsole, 14);
	cout << ((double)kEval) / 1000 << "\n\n";
	SetConsoleTextAttribute(hConsole, 15);


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

	cout << fen << "\n";
}