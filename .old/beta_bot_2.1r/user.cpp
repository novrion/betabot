#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include "beta.h"

using namespace std;



HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;

map<int, char> notationValue = {
  {0, 'a'},
  {1, 'b'},
  {2, 'c'},
  {3, 'd'},
  {4, 'e'},
  {5, 'f'},
  {6, 'g'},
  {7, 'h'}
};

map<char, int> indexValue = {
  {'a', 0},
  {'b', 1},
  {'c', 2},
  {'d', 3},
  {'e', 4},
  {'f', 5},
  {'g', 6},
  {'h', 7}
};



// Translation ~ ~
Move TranslateToMove(string notation, int board[8][8]) {

	int fromX = indexValue.at(notation[0]);
	int fromY = notation[1] - 1 - '0';

	int toX = indexValue.at(notation[4]);
	int toY = notation[5] - 1 - '0';

	Move move = Move(fromX, fromY, toX, toY, board[toX][toY]);
	if (board[fromX][fromY] == 100000) {
		if (toX == fromX + 2) {
			move.castle = 1;
		}

		else if (toX == fromX - 2) {
			move.castle = 2;
		}
	}
	else if (board[fromX][fromY] == -100000) {
		if (toX == fromX + 2) {
			move.castle = 3;
		}

		else if (toX == fromX - 2) {
			move.castle = 4;
		}
	}

	return move;
}
Move Prim_TranslateToMove(string notation, int board[8][8]) {

	int fromX = indexValue.at(notation[0]);
	int fromY = notation[1] - 1 - '0';

	int toX = indexValue.at(notation[2]);
	int toY = notation[3] - 1 - '0';

	Move move = Move(fromX, fromY, toX, toY, board[toX][toY]);
	if (board[fromX][fromY] == 100000) {
		if (toX == fromX + 2) {
			move.castle = 1;
		}

		else if (toX == fromX - 2) {
			move.castle = 2;
		}
	}
	else if (board[fromX][fromY] == -100000) {
		if (toX == fromX + 2) {
			move.castle = 3;
		}

		else if (toX == fromX - 2) {
			move.castle = 4;
		}
	}

	return move;
}

string TranslateToNotation(Move& move) {

	if (move.fromX == -1) {
		return "None";
	}

	string notation;

	notation.push_back(notationValue.at(move.fromX));
	notation += to_string(move.fromY + 1);

	notation.push_back(' ');
	notation.push_back('-');
	notation.push_back('>');
	notation.push_back(' ');


	notation.push_back(notationValue.at(move.toX));
	notation += to_string(move.toY + 1);

	return notation;
}
string Prim_TranslateToNotation(Move& move) {

	if (move.fromX == -1) {
		return "None";
	}

	string notation;

	notation.push_back(notationValue.at(move.fromX));
	notation += to_string(move.fromY + 1);

	notation.push_back(notationValue.at(move.toX));
	notation += to_string(move.toY + 1);

	return notation;
}



// Logic ~ ~
int GetPieces(int board[8][8]) {

	int num = 0;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (board[x][y]) {
				num++;
			}
		}
	}

	return num;
}



// Input ~ ~
void Main_MakeMove(Board& b, vector<Move>& matchLine) {

	string in_1;
	string in_2;

	// Input
	cout << "From: ";
	cin >> in_1;
	cout << "To: ";
	cin >> in_2;

	in_1.push_back(in_2[0]);
	in_1.push_back(in_2[1]);

	Move move = Prim_TranslateToMove(in_1, b.board);
	matchLine.push_back(move);
	MakeMove(b, move);
}

bool InputColor() {

	char color;

	cout << "Color W / B: ";
	cin >> color;
	cout << "\n";

	return color == 'W';
}

int InputDepth() {

	int depth;

	cout << "Depth: ";
	cin >> depth;
	cout << "\n";

	return depth;
}

int InputMatch(Board& b, vector<Move>& matchLine) {

	string input;
	Move move;

	cout << "Match: ";
	cin >> input;
	cout << "\n";

	if (input == "x") {
		return 0;
	}

	for (int x = 0; x < input.size(); x += 5) {

		string notation;

		notation.push_back(input[x]);
		notation.push_back(input[x + 1]);
		notation.push_back(input[x + 2]);
		notation.push_back(input[x + 3]);

		move = Prim_TranslateToMove(notation, b.board);
		matchLine.push_back(move);

		MakeMove(b, move);
	}

	PrintBoard(b.board, move.fromX, move.fromY, move.toX, move.toY);


	if (input.size() % 2 == 0) {
		return 1;
	}
	return -1;
}



// Output ~ ~
void PrintBoard(int board[8][8], int fromX, int fromY, int toX, int toY) {

	SetConsoleTextAttribute(hConsole, 8);
	map<int, char> pieceValue = {
		{0, ' '},

		{1000, 'P'},
		{3000, 'H'},
		{3100, 'B'},
		{5000, 'R'},
		{9000, 'Q'},
		{100000, 'K'},

		{-1000, 'p'},
		{-3000, 'h'},
		{-3100, 'b'},
		{-5000, 'r'},
		{-9000, 'q'},
		{-100000, 'k'}
	};


	cout << "-------------------------------------------------" << "\n";

	for (int x = 7; -1 < x; x--) {
		cout << "|     |     |     |     |     |     |     |     |" << "\n";
		cout << "|  ";

		for (int y = 0; y < 8; y++) {

			if (board[y][x] > 0) {
				if (y == fromX && x == fromY) {
					SetConsoleTextAttribute(hConsole, 47);
				}
				else if (y == toX && x == toY) {
					SetConsoleTextAttribute(hConsole, 79);
				}
				else {
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
			else if (board[y][x] < 0) {
				if (y == fromX && x == fromY) {
					SetConsoleTextAttribute(hConsole, 44);
				}
				else if (y == toX && x == toY) {
					SetConsoleTextAttribute(hConsole, 76);
				}
				else {
					SetConsoleTextAttribute(hConsole, 12);
				}
			}
			else {
				if (y == fromX && x == fromY) {
					SetConsoleTextAttribute(hConsole, 40);
				}
				else if (y == toX && x == toY) {
					SetConsoleTextAttribute(hConsole, 72);
				}
				else {
					SetConsoleTextAttribute(hConsole, 8);
				}
			}

			cout << pieceValue.at(board[y][x]);
			SetConsoleTextAttribute(hConsole, 8);
			cout << "  |  ";
		}

		cout << "\n" << "|     |     |     |     |     |     |     |     |" << "\n";
		cout << "-------------------------------------------------" << "\n";
	}

	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\n";
}

void PrintMatch(vector<Move>& matchLine) {

	int c = 0;

	for (Move& move : matchLine) {

		if (c++ % 2 == 0) {
			SetConsoleTextAttribute(hConsole, 15);
		}
		else {
			SetConsoleTextAttribute(hConsole, 8);
		}

		cout << Prim_TranslateToNotation(move) << "/";


	}

	SetConsoleTextAttribute(hConsole, 7);

	cout << "\n\n";
}

void PrintMain(int board[8][8], int eval, Move& move, vector<Move>& matchLine) {

	cout << "Eval: " << (double)eval / (double)1000 << "\n";
	cout << "Move: " << TranslateToNotation(move) << "\n";
	PrintBoard(board, move.fromX, move.fromY, move.toX, move.toY);
	PrintMatch(matchLine);

	cout << "\n\n\n";
}