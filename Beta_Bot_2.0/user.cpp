#include <iostream>
#include <map>
#include <string>
#include "beta.h"

using namespace std;



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
Move TranslateToMove(string notation, double board[8][8]) {

	int fromX = indexValue.at(notation[0]);
	int fromY = notation[1] - 1 - '0';

	int toX = indexValue.at(notation[4]);
	int toY = notation[5] - 1 - '0';

	return Move(fromX, fromY, toX, toY, board[toX][toY]);
}

string TranslateToNotation(Move& move) {

	if (move.fromX == -1) {
		return "None";
	}

	string notation;

	notation.push_back(notationValue.at(move.fromX));
	notation += to_string(move.fromY + 1);

	notation.push_back('-');
	notation.push_back('>');

	notation.push_back(notationValue.at(move.toX));
	notation += to_string(move.toY + 1);

	return notation;
}



// Input ~ ~
void Main_MakeMove(Board& b) {

	string input;

	// Input
	cout << "Input: ";
	cin >> input;

	Move move = TranslateToMove(input, b.board);
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



// Output ~ ~
void PrintBoard(double board[8][8]) {

	map<double, char> pieceValue = {
		{0, ' '},

		{1, 'P'},
		{3, 'H'},
		{3.1, 'B'},
		{5, 'R'},
		{9, 'Q'},
		{100, 'K'},

		{-1, 'p'},
		{-3, 'h'},
		{-3.1, 'b'},
		{-5, 'r'},
		{-9, 'q'},
		{-100, 'k'}
	};

	cout << "-------------------------------------------------" << "\n";

	for (int x = 7; -1 < x; x--) {
		cout << "|     |     |     |     |     |     |     |     |" << "\n";
		cout << "|  ";

		for (int y = 0; y < 8; y++) {
			//cout << pieceValue.at(board[y][x]) << "  |  ";
			cout << board[y][x] << "  |  ";
		}

		cout << "\n" << "|     |     |     |     |     |     |     |     |" << "\n";
		cout << "-------------------------------------------------" << "\n";
	}

	cout << "\n\n";
}

void PrintMain(double board[8][8], double eval, Move& move) {

	cout << "Eval: " << eval << "\n";
	cout << "Move: " << TranslateToNotation(move) << "\n";
	PrintBoard(board);

	cout << "\n\n\n";
}
