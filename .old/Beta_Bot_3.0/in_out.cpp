#include "beta.h"
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


// Translation
string translate_to_notation(U64 move) {

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

	int from = get_move_from(move);
	int to = get_move_to(move);


	notation += notation_index.at(from % 8);
	notation += to_string(8 - (from / 8 + 1) + 1);

	notation += " -> ";

	notation.push_back(notation_index.at(to % 8));
	notation += to_string(8 - (to / 8 + 1) + 1);

	return notation;
}

int translate_to_square(string input) {

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

	square += square_index.at(input[0]);
	square += (8 - (input[1] - '0')) * 8;

	return square;
}


// Input
int input_match(Board& b) {

	string input;
	int index = 0;
	int start_index = 2;
	U64 bitboard = 0ULL;

	cout << "Match: ";
	cin >> input;

	for (int i = 2; i < input.size(); i++) {

		if (input[i] == '/') {

			bitboard = stoull(input.substr(start_index, i - start_index));
			b.b2[index] = bitboard;

			index++;
			start_index = i + 1;
		}
	}

	if (input[0] == 'x') return -1;
	return (input[0] == 'w' ? 1 : 0);
}

int InputColor() {

	char color;

	cout << "Color W / B: ";
	cin >> color;
	cout << "\n";

	return (color == 'W' || color == 'w') ? 1 : 0;
}

void user_make_move(Board& b, int colour) {

	string input_from;
	string input_to;

	int from = 0;
	int to = 0;
	int piece = 0;
	int capture = 0;
	int promotion = 0;
	int _2pawn = 0;
	int en_passant = 0;
	int castle = 0;


	cout << "\n\n\nFrom: ";
	cin >> input_from;
	cout << "To: ";
	cin >> input_to;
	cout << "\n";

	from = translate_to_square(input_from);
	to = translate_to_square(input_to);



	if (colour) {

		for (int i = 1; i < 7; i++) {
			if (b.b2[i] & 1ULL << from) piece = i;
		}

		if (_b_block(b.b2) & 1ULL << to) capture = 1;

		if (piece == 1) {

			if (from / 8 == 1) promotion = 1;

			else if (from / 8 == 6 && to / 8 == 4) _2pawn = 1;

			else if (from % 8 != to % 8 && !(_b_block(b.b2) & 1ULL << to)) {
				en_passant = 1;
			}
		}

		else if (piece == 6 && abs(from % 8 - to % 8 == 2)) castle = 1;
	}

	else {

		for (int i = 7; i < 13; i++) {
			if (b.b2[i] & 1ULL << from) piece = i;
		}

		if (_w_block(b.b2) & 1ULL << to) capture = 1;

		if (piece == 7) {

			if (from / 8 == 6) promotion = 1;

			else if (from / 8 == 1 && to / 8 == 3) _2pawn = 1;

			else if (from % 8 != to % 8 && !(_w_block(b.b2) & 1ULL << to)) {
				en_passant = 1;
			}
		}

		else if (piece == 12 && abs(from % 8 - to % 8 == 2)) castle = 1;
	}

	U64 move = encode_move(b.b2, from, to, piece, capture, promotion, _2pawn, en_passant, castle);
	make_move(b.b2, move, colour);
}


// Cout
void _p_cout_board(U64 bitboard) {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (!y) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << "  " << 8 - x << "  ";
				SetConsoleTextAttribute(hConsole, 7);
			}

			int square = x * 8 + y;
			cout << "   " << (get_bit(bitboard, square) ? 1 : 0);
		}

		cout << "\n\n";
	}

	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";
	SetConsoleTextAttribute(hConsole, 7);

	cout << "\nBitboard: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << bitboard << "\n\n\n";
	SetConsoleTextAttribute(hConsole, 7);
}

void cout_board(char board[64]) {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (!y) {

				SetConsoleTextAttribute(hConsole, 11);
				cout << "  " << 8 - x << "  ";
				SetConsoleTextAttribute(hConsole, 7);
			}

			int square = x * 8 + y;

			if (board[square]) cout << "   " << board[square];
			else cout << "    ";
		}

		cout << "\n\n";
	}

	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";
	SetConsoleTextAttribute(hConsole, 7);
}

void cout_state(Board& b, int evaluation, U64 n_move, int colour) {

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
	U64 temp;
	int square;


	cout << "Move: " << translate_to_notation(n_move) << "\n";
	cout << "Evaluation: " << ((double)evaluation) / 1000 << "\n\n";


	// Fill Board
	for (int i = 1; i < 13; i++) {

		temp = b.b2[i];

		while (temp) {
			square = countr_zero(temp);
			pop_bit(temp, square);
			board[square] = piece_index.at(i);
		}
	}

	cout_board(board);

	cout << "\nState: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << (colour ? 'b' : 'w') << "/";
	for (int i = 0; i < 13; i++) cout << b.b2[i] << "/";
	SetConsoleTextAttribute(hConsole, 7);
}