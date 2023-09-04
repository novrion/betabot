#include "beta.h"
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;



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
	return x.eval < y.eval;
}

void OrderMoves(Board& b, vector<Move>& moves) {

	//chrono::time_point<chrono::high_resolution_clock> timeStart = chrono::high_resolution_clock::now();
	for (Move& move : moves) {

		//move.eval = abs(b.board[move.fromX][move.fromY]) - abs(move.capture) * 1000 - abs(move.castle) * 100000 - positionMatrix[move.toX][move.toY] * 3000;
		move.eval = -abs(move.capture) * 100 - abs(move.castle) * 10 - positionMatrix[move.toX][move.toY];
	}

	sort(moves.begin(), moves.end(), comparator);

	//chrono::time_point<chrono::high_resolution_clock> timeStop = chrono::high_resolution_clock::now();
	//chrono::duration<double> time = timeStop - timeStart;

	//cout << time.count() << "\n";
}



int Quiescence(Board& b, int depth, int alpha, int beta, bool color) {

	if (depth == 0) {
		return b.eval;
	}

	int evaluation;
	int minEval = b.eval;
	int maxEval = b.eval;


	vector<Move> moves;
	GenerateMoves(b, moves, color, true);
	if (moves.size() == 0) {
		return b.eval;
	}
	OrderMoves(b, moves);



	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (b.eval > 50000) {
				UndoMove(b, move);
				return 1000000;
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
			if (b.eval < -50000) {
				UndoMove(b, move);
				return -100000;
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
	OrderMoves(b, moves);
	//cout << moves.size() << " ";




	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (b.eval > 50000) {
				UndoMove(b, move);
				return 1000000;
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

		/*if (depth == 1) {
			return maxEval += moves.size();
		}*/

		return maxEval;
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (b.eval < -50000) {
				UndoMove(b, move);
				return -1000000;
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

		/*if (depth == 1) {
			return minEval -= moves.size();
		}*/

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
	OrderMoves(b, moves);


	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (b.eval > 50000) {
				UndoMove(b, move);
				b.n_move = move;
				return 1000000;
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

		cout << "\n";

		return maxEval;
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
			if (b.eval < -50000) {
				UndoMove(b, move);
				b.n_move = move;
				return -1000000;
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

		cout << "\n";

		return minEval;
	}
}