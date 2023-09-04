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

/*void OrderMoves(Board& b, vector<Move>& moves) {

	//chrono::time_point<chrono::high_resolution_clock> timeStart = chrono::high_resolution_clock::now();
	for (Move& move : moves) {

		//move.eval = abs(b.board[move.fromX][move.fromY]) - abs(move.capture) * 1000 - abs(move.castle) * 100000 - positionMatrix[move.toX][move.toY] * 3000;
		move.eval = -abs(move.capture) * 100 - abs(move.castle) * 10 - positionMatrix[move.toX][move.toY];
	}

	sort(moves.begin(), moves.end(), comparator);

	//chrono::time_point<chrono::high_resolution_clock> timeStop = chrono::high_resolution_clock::now();
	//chrono::duration<double> time = timeStop - timeStart;

	//cout << time.count() << "\n";
}*/

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



int Quiescence(Board& b, int depth, int alpha, int beta, bool color) {

	if (depth == 0) {

		duration<double> time;
		time_point<high_resolution_clock> start_time = high_resolution_clock::now();

		int a = Evaluation(b);

		cout << (time = high_resolution_clock::now() - start_time).count() << "\n";

		return a;

	}

	int evaluation;
	int minEval = Evaluation(b);
	int maxEval = minEval;


	vector<Move> moves;
	GenerateMoves(b, moves, color, true);
	if (moves.size() == 0) {
		return Evaluation(b);
	}
	sort(moves.begin(), moves.end(), comparator);



	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (move.capture < -50000) {
				UndoMove(b, move);
				return 700000 + depth -100;
			}

			evaluation = Quiescence(b, depth - 1, alpha, beta, false);
			UndoMove(b, move);


			if (evaluation > maxEval) {
				maxEval = evaluation;
			}

			// Alpha Beta Pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) {
				break;
			}
		}

		return maxEval;
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (move.capture > 50000) {
				UndoMove(b, move);
				return -700000 - depth + 100;
			}

			evaluation = Quiescence(b, depth - 1, alpha, beta, true);
			UndoMove(b, move);


			if (evaluation < minEval) {
				minEval = evaluation;
			}

			// Alpha Beta Pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) {
				break;
			}
		}

		return minEval;
	}
}


int Minimax(Board& b, int depth, int alpha, int beta, bool color) {

	if (depth == 0) {
		return Quiescence(b, 4, alpha, beta, color);
	}

	int evaluation;
	int minEval = 999999;
	int maxEval = -999999;


	vector<Move> moves;
	GenerateMoves(b, moves, color, false);
	sort(moves.begin(), moves.end(), comparator);



	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (move.capture < -50000) {
				UndoMove(b, move);
				return 700000 + depth;
			}

			evaluation = Minimax(b, depth - 1, alpha, beta, false);
			UndoMove(b, move);


			if (evaluation > maxEval) {
				maxEval = evaluation;
			}

			// Alpha Beta Pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) {
				break;
			}
		}

		return maxEval;
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (move.capture > 50000) {
				UndoMove(b, move);
				return -700000 - depth;
			}

			evaluation = Minimax(b, depth - 1, alpha, beta, true);
			UndoMove(b, move);


			if (evaluation < minEval) {
				minEval = evaluation;
			}

			// Alpha Beta Pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) {
				break;
			}
		}

		return minEval;
	}
}


int firstLayerMinimax(Board& b, int depth, int alpha, int beta, bool color) {

	int i = 0;

	int evaluation;
	int minEval = 999999;
	int maxEval = -999999;


	vector<Move> moves;
	GenerateMoves(b, moves, color, false);
	sort(moves.begin(), moves.end(), comparator);


	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (move.capture < -50000) {
				UndoMove(b, move);
				b.n_move = move;
				return 700000;
			}

			evaluation = Minimax(b, depth - 1, alpha, beta, false);
			UndoMove(b, move);


			if (evaluation > maxEval) {
				maxEval = evaluation;
				b.n_move = move;
			}

			// Alpha Beta Pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) {
				break;
			}

			cout << i++ << " ";
		}

		cout << "\n\n";

		return maxEval;
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (move.capture > 50000) {
				UndoMove(b, move);
				b.n_move = move;
				return -700000;
			}

			evaluation = Minimax(b, depth - 1, alpha, beta, true);
			UndoMove(b, move);


			if (evaluation < minEval) {
				minEval = evaluation;
				b.n_move = move;
			}

			// Alpha Beta Pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) {
				break;
			}

			cout << i++ << " ";
		}

		cout << "\n\n";

		return minEval;
	}
}