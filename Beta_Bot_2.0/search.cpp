#include "beta.h"
#include <iostream>

using namespace std;


double Quiescence(Board& b, int depth, double alpha, double beta, bool color) {

	if (depth == 0) {
		return b.eval;
	}

	double evaluation;
	double minEval = b.eval;
	double maxEval = b.eval;


	vector<Move> moves;
	GenerateMoves(b, moves, color, true);
	if (moves.size() == 0) {
		return b.eval;
	}





	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
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



double Minimax(Board& b, int depth, double alpha, double beta, bool color) {

	if (depth == 0) {
		return b.eval;
		//return Quiescence(b, 4, alpha, beta, player);
	}

	double evaluation;
	double minEval = 999;
	double maxEval = -999;


	vector<Move> moves;
	GenerateMoves(b, moves, color, false);

	



	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
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

		return maxEval += 0.01 * moves.size();
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
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

		return minEval -= 0.01 * moves.size();
	}
}



double firstLayerMinimax(Board& b, int depth, double alpha, double beta, bool color) {

	double evaluation;
	double minEval = 999;
	double maxEval = -999;


	vector<Move> moves;
	GenerateMoves(b, moves, color, false);



	if (color) {

		for (Move& move : moves) {

			MakeMove(b, move);
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
		}
		cout << "getin";
		return maxEval;
	}



	else {

		for (Move& move : moves) {

			MakeMove(b, move);
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
		}
		cout << "bbbbb_ getin";

		return minEval;
	}
}
