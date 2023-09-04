#include "_interface.h"
using namespace std;


void __play_bot__(Board& b, const double max_time) {

	pair<int, U64> bot_move;

	if (!b.side) user_MakeMove(b);


	while (true) {

		bot_move = iterative_deepening(b, b.side, max_time);
		MakeMove(b.bb, bot_move.second, b.side);

		cout_state(b, bot_move.first, bot_move.second);

		/* debug */
		//cout << "\n\nTotal time: " << total_time.count() << "   Time Count: " << time_count << "\n\n";
		/* debug */


		user_MakeMove(b);
	}
}


// Translation
string translate_to_notation(const U64 move) {

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

	int from = get_move_source(move);
	int to = get_move_target(move);


	notation += notation_index.at(from % 8);
	notation += to_string(8 - (from / 8 + 1) + 1);

	notation += " -> ";

	notation.push_back(notation_index.at(to % 8));
	notation += to_string(8 - (to / 8 + 1) + 1);

	return notation;
}
int translate_to_square(const string input) {

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


// User Interaction
void user_MakeMove(Board& b) {

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



	if (!b.side) {

		for (int i = 1; i < 7; ++i) {
			if (b.bb[i] & 1ULL << from) piece = i;
		}

		if (_b_block(b.bb) & 1ULL << to) capture = 1;

		if (piece == 1) {

			if (from / 8 == 1) promotion = 1;

			else if (from / 8 == 6 && to / 8 == 4) _2pawn = 1;

			else if (from % 8 != to % 8 && !(_b_block(b.bb) & 1ULL << to)) {
				en_passant = 1;
			}
		}

		else if (piece == 6 && abs(from % 8 - to % 8 == 2)) castle = 1;
	}

	else {

		for (int i = 7; i < 13; ++i) {
			if (b.bb[i] & 1ULL << from) piece = i;
		}

		if (_w_block(b.bb) & 1ULL << to) capture = 1;

		if (piece == 7) {

			if (from / 8 == 6) promotion = 1;

			else if (from / 8 == 1 && to / 8 == 3) _2pawn = 1;

			else if (from % 8 != to % 8 && !(_w_block(b.bb) & 1ULL << to)) {
				en_passant = 1;
			}
		}

		else if (piece == 12 && abs(from % 8 - to % 8 == 2)) castle = 1;
	}

	U64 move = encode_move(from, to, piece, capture, promotion, _2pawn, en_passant, castle);
	MakeMove(b.bb, move, !b.side);
}


// Interface
void cout_board(const char board[64]) {

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (!y) {

				cout << "  " << 8 - x << "  ";
			}

			int square = x * 8 + y;

			if (board[square]) cout << "   " << board[square];
			else cout << "    ";
		}

		cout << "\n\n";
	}

	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";
}
void cout_state(Board& b, int evaluation, const U64 next_move) {

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


	cout << "\nMove: " << translate_to_notation(next_move) << "\n";
	cout << "Evaluation: " << ((double)evaluation) / 1000 << "\n\n";


	// Fill Board
	for (int i = 1; i < 13; ++i) {
		for (int square = 0; square < 64; ++square) {
			if (1ULL << square & b.bb[i]) board[square] = piece_index.at(i);
		}

		/*temp = b.bb[i];

		while (temp) {
			square = countr_zero(temp);
			pop_bit(temp, square);
			board[square] = piece_index.at(i);
		}*/
	}

	cout_board(board);

	cout << "\nState: ";
	cout << (b.side ? 'b' : 'w') << "/";
	for (int i = 0; i < 13; ++i) cout << b.bb[i] << "/";
}