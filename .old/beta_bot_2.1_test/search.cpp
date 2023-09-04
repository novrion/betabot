#include "beta.h"
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;



const int positionMatrix[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 2, 3, 3, 2, 1, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 3, 4, 5, 5, 4, 3, 0},
	{0, 3, 4, 5, 5, 4, 3, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 1, 2, 3, 3, 2, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

bool comparator(Move& x, Move& y) {
	return (-abs(x.capture) * 100 - abs(x.castle) * 10 - positionMatrix[x.toX][x.toY]) < (-abs(y.capture) * 100 - abs(y.castle) * 10 - positionMatrix[y.toX][y.toY]);
}

int Evaluation(Board& b) {

	//time_point<high_resolution_clock> start_time = high_resolution_clock::now();



	int eval = b.w_castle + b.b_castle;

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			if (!b.board[x][y]) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				eval += b.board[x][y] + positionMatrix[x][y];
			}

			else {
				eval += b.board[x][y] - positionMatrix[x][y];
			}
		}
	}

	//time_point<high_resolution_clock> stop_time = high_resolution_clock::now();
	//duration<double> time = stop_time - start_time;
	//cout << time.count() << "\n";

	return eval;
}



int Minimax(Board& b, int depth, bool color) {

	if (depth == 0) {
		//int x = Evaluation(b);
		return 1;
	}
		

	int evaluation = 0;

	vector<Move> moves;
	GenerateMoves(b, moves, color, false);
	//sort(moves.begin(), moves.end(), comparator);


	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			evaluation += Minimax(b, depth - 1, false);
			UndoMove(b, move);
		}

		return evaluation;
	}


	else {

		for (Move& move : moves) {

			MakeMove(b, move);
			evaluation += Minimax(b, depth - 1, true);
			UndoMove(b, move);
		}

		return evaluation;
	}
}