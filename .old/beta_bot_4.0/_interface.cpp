#include "_interface.h"
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
		{'k', 12},
};



// Play Bot
void __play_bot__(Board& b, const double max_time) {

	pair<int, u64> bot_move;

	if (!b.side) input_move(b);


	while (true) {

		//bot_move = iterative_deepening(b, b.side, max_time);
		//MakeMove(b.bb, bot_move.second, b.side);

		print_state(b, bot_move.second, bot_move.first);

		input_move(b);
	}
}


// Initialization
void _init_board(Board& b) {

	input_fen(b);
	if (!b.bb[1]) {

		// (utility)
		b.bb[0] = 0ULL;

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
	}


	b.side = input_side();
}





// Input
bool input_side() {

	char color;

	cout << "Color W / B: ";
	cin >> color;

	cout << "\n";
	return (color == 'W' || color == 'w') ? true : false;
}
void input_fen(Board& b) {

	string fen;

	for (int bitboard = 0; bitboard < 13; ++bitboard) {
		b.bb[bitboard] = 0ULL;
	}

	cout << "FEN: ";
	getline(cin, fen);

	parseFen(b, fen);
}
void input_move(Board& b) {

	string source_string;
	string target_string;

	cout << "Source: ";
	cin >> source_string;

	cout << "\nTarget: ";
	cin >> target_string;

	//MakeMove(b.bb, translate_to_move(b.bb, !b.side, source_string, target_string), !b.side);
}


// Print
void print_board(u64 bb[13], const int source_square, const int target_square) {

	bool is_squares = (source_square == -1 ? false : true);

	char board[64] = "\0";
	for (int bitboard = P; bitboard <= k; ++bitboard) {
		for (int square = 0; square < 64; ++square) {
			if (bb[bitboard] & 1ULL << square) board[square] = piece[bitboard];
		}
	}


	cout << "-----------------------------------------\n\n";
	for (int rank = 0; rank < 8; ++rank) {

		SetConsoleTextAttribute(hConsole, 11);
		cout << "  " << reverse_int[rank] << "  ";
		SetConsoleTextAttribute(hConsole, 7);


		for (int file = 0; file < 8; ++file) {

			if (is_squares && rank * 8 + file == source_square) {

				cout << "   ";
				SetConsoleTextAttribute(hConsole, 10);
				cout << board[rank * 8 + file];
				SetConsoleTextAttribute(hConsole, 7);
			}

			else if (is_squares && rank * 8 + file == target_square) {

				cout << "   ";
				SetConsoleTextAttribute(hConsole, 12);
				cout << board[rank * 8 + file];
				SetConsoleTextAttribute(hConsole, 7);
			}

			else if (board[rank * 8 + file]) cout << "   " << board[rank * 8 + file];
			else cout << "    ";
		}
		cout << "\n\n";
	}

	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n        A   B   C   D   E   F   G   H\n\n";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "-----------------------------------------\n";
}
void print_state(Board& b, const u64 move, const int evaluation) {

	cout << "Move: " << translate_to_notation(move) << "\n";
	cout << "Evaluation: " << (double)evaluation / 1000 << "\n";
	print_board(b.bb, get_move_source(move), get_move_target(move));
}


// Translation
string translate_to_notation(const u64 move) {

	string notation;

	int from = get_move_source(move);
	int to = get_move_target(move);


	notation += character[from % 8];
	notation += reverse_int[from / 8];

	notation += " -> ";

	notation += character[to % 8];
	notation += reverse_int[to / 8];

	return notation;
}
int translate_to_square(const string& square_string) {

	int square = 0;

	square += file_index[square_string[0]];
	square += reverse_int[square_string[1] - '0'] * 8;

	return square;
}
u64 translate_to_move(u64 bb[13], bool side, const string& source_string, const string& target_string) {

	int source = translate_to_square(source_string);
	int target = translate_to_square(target_string);

	int capture = 0;
	int piece = 15;

	int _2pawn = 0;
	int en_passant = 0;
	int promotion = 0;

	int castle = 0;


	// Capture
	if (side) {
		for (int bitboard = p; bitboard <= k; ++bitboard) {
			if (bb[bitboard] & 1ULL << target) {
				capture = 1;
				break;
			}
		}
	}
	else {
		for (int bitboard = P; bitboard <= K; ++bitboard) {
			if (bb[bitboard] & 1ULL << target) {
				capture = 1;
				break;
			}
		}
	}

	// Piece
	for (int bitboard = P; bitboard <= k; ++bitboard) {
		if (bb[bitboard] & 1ULL << source) {
			piece = bitboard;
			break;
		}
	}

	// Pawn
	if (piece == P || piece == p) {

		// Double Pawn Move
		if (abs(target - source) == 16) _2pawn = 1;

		// En Passant
		else if (!capture && abs(target - source) != 8) {
			en_passant = 1;
			capture = 1;
		}

		// Promotion
		else if (target / 8 == 0 || target / 8 == 7) promotion = 1;
	}

	// Castle
	else if (piece == K || piece == k) {
		if (source / 8 == target / 8 && abs(target - source) == 2) castle = 1;
	}


	return encode_move(source, target, piece, capture, promotion, _2pawn, en_passant, castle);
}


// FEN
void parseFen(Board& b, string& fen) {


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
			fen[++i] == 'w' ? b.bb[0] |= 1ULL << 10 : 0;
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

				b.bb[0] |= translate_to_square(en_passant_square);
				break;
			}
		}
	}
}
void printFen(Board& b) {

	string fen;

	for (int rank = 0; rank < 8; ++rank) {

		int count = 0;
		for (int file = 0; file < 8; ++file) {

			bool found = false;
			for (int bitboard = P; bitboard <= k; ++bitboard) {
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
	get_utility_turn(b.bb[0]) ? fen += 'w' : fen += 'b';
	fen += ' ';


	if (get_utility_K(b.bb[0])) fen += 'K';
	if (get_utility_Q(b.bb[0])) fen += 'Q';
	if (get_utility_k(b.bb[0])) fen += 'k';
	if (get_utility_q(b.bb[0])) fen += 'q';
	fen += ' ';


	string en_passant_notation;
	int en_passant_square = get_utility_en_passant(b.bb[0]);

	if (en_passant_square) {
		en_passant_notation += character[en_passant_square % 8];
		en_passant_notation += reverse_int[en_passant_square / 8] + '0';
		fen += en_passant_notation;
	}
	else fen += '-';

	cout << fen << "\n";
}