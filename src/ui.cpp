#include "ui.h"


std::map<char, int> bitboard_index = {
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



// Tutorial
void PrintTutorial() {
	std::cout << "---------------------------------\n";
	std::cout << "Write 'help' for the command list\n";
	std::cout << "---------------------------------\n";
}


// Translation
std::string MoveToNotation(const U64 kMove) {
	std::map<int, char> notation_index = {
		{0, 'a'},
		{1, 'b'},
		{2, 'c'},
		{3, 'd'},
		{4, 'e'},
		{5, 'f'},
		{6, 'g'},
		{7, 'h'}
	};

	std::string notation;
	int from = GET_MOVE_SOURCE(kMove);
	int to = GET_MOVE_TARGET(kMove);


	notation += notation_index.at(from % 8);
	notation += std::to_string(8 - (from / 8 + 1) + 1);

	notation += " -> ";

	notation.push_back(notation_index.at(to % 8));
	notation += std::to_string(8 - (to / 8 + 1) + 1);

	return notation;
}
int StringToSquare(const std::string kStr) {
	std::map<char, int> square_index = {
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
	std::string fen;
	std::cout << "FEN: ";
	fflush(stdin);

	for (int i = 0; i < 6; ++i) {
		std::string tmp;
		std::cin >> tmp;
		if (tmp == "x" || tmp == "X") return;
		fen += tmp;
		fen += " ";
	}

	for (int bitboard = 0; bitboard < 13; ++bitboard) {
		b.bb[bitboard] = 0ULL;
	}

	ParseFen(b, fen);
}


// Interface
void clear_ui() {
        fflush(stdout);
        system("clear");
}

void PrintBoard(const char kBoard[64], const int kSource, const int kTarget) {
        std::cout << RESET << "     " << BOARD_BG << "                                   " << RESET << "\n";

        for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                        if (!y) {
                                std::cout << RESET << "  " << 8 - x << "  ";
                        }

                        int square = x * 8 + y;
                        if (square == kSource || square == kTarget) {
                                std::cout << "   ";

                                if (square == kSource) std::cout << RED_FG_BOARD_BG;
                                else std::cout << GREEN_FG_BOARD_BG;

                                if (!kBoard[square]) std::cout << ".";
                                else std::cout << kBoard[square];
                        }
                        else if (kBoard[square]) {
                                if (kBoard[square] < 'a') std::cout << WHITE_FG_BOARD_BG << "   " << kBoard[square];
                                else std::cout << BLACK_FG_BOARD_BG << "   " << kBoard[square];
                        }
                        else std::cout << BOARD_BG << "    ";
                }
                std::cout << BOARD_BG << "   " << RESET << "\n" << "     " << BOARD_BG << "                                   " << RESET << "\n";
        }

        std::cout << RESET;
        std::cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";

		fflush(stdout);
}

void PrintState(Board& b, const int kEval, const U64 kNextMove, const int kPly, bool player_turn[400]) {
	clear_ui();

	std::map<int, char> piece_index = {
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

	PrintFen(b, player_turn[kPly + 1]);
    std::cout << "Ply:        " << kPly   << "\n";
    std::cout << "Evaluation: ";
    std::cout << ((double)kEval) / 1000 << "\n";
    std::cout << BLUE_FG << MoveToNotation(kNextMove) << RESET << "\n\n";

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
	std::cout << "\n";
}


// FEN
void ParseFen(Board& b, std::string& fen) {
	int stage = 0;
	std::string en_passant_square;

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
	std::string fen;

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

	std::string en_passant_notation;
	int en_passant_square = GET_UTILITY_EN_PASSANT(b.bb[0]);

	if (en_passant_square) {
		en_passant_notation += character[en_passant_square % 8];
		en_passant_notation += reverse_int[en_passant_square / 8] + '0';
		fen += en_passant_notation;
	}
	else fen += '-';

	fen += " - -";

	std::cout << fen << "\n";
}
