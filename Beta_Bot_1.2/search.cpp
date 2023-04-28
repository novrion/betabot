#include <iostream>
#include <map>
#include <vector>

#include "Board.h"

using namespace std;



pair<double, vector<Move>> Minimax(Board& b, int depth, double alpha, double beta, bool isWhitePlayer);
pair<double, vector<Move>> Quiescence(Board& b, int depth, double alpha, double beta, bool isWhitePlayer);





pair<double, vector<Move>> Minimax(Board& b, int depth, double alpha, double beta, bool isWhitePlayer) {

	if (depth == 0) {
		if (isWhitePlayer) {
			return Quiescence(b, 4, alpha, beta, true);
		}
		return Quiescence(b, 4, alpha, beta, false);
	}
	

	vector<Move> moves = b.GenerateMoves(isWhitePlayer);


	Move bestMove;
	pair<double, vector<Move>> minimaxData;
	pair<double, vector<Move>> bestMoveLine;

	double evali;
	double maxEval = -99999;
	double minEval = 99999;





	if (isWhitePlayer) {

		for (Move &move : moves) {

			b.MakeMove(move);
			minimaxData = Minimax(b, depth - 1, alpha, beta, false);
			evali = minimaxData.first;
			b.UndoMove(move);



			if (evali > maxEval) {
				maxEval = evali;
				bestMove = move;
				bestMoveLine = minimaxData;
			}

			// Alpha-Beta Pruning
			alpha = max(alpha, evali);
			if (beta <= alpha) {
				break;
			}
		}



		bestMoveLine.second.push_back(bestMove);

		return bestMoveLine;
	}





	else {

		for (Move &move : moves) {

			b.MakeMove(move);
			minimaxData = Minimax(b, depth - 1, alpha, beta, true);
			evali = minimaxData.first;
			b.UndoMove(move);



			if (evali < minEval) {
				minEval = evali;
				bestMove = move;
				bestMoveLine = minimaxData;
			}

			// Alpha-Beta Pruning
			beta = min(beta, evali);
			if (beta <= alpha) {
				break;
			}
		}



		bestMoveLine.second.push_back(bestMove);

		return bestMoveLine;
	}
}





// So stupid LMAO. Literally double the code but half of it is the same hihi.
pair<double, vector<Move>> Quiescence(Board& b, int depth, double alpha, double beta, bool isWhitePlayer) {

	vector<Move> emptyVec;

	if (depth == 0) {
		return { b.eval, emptyVec };
	}


	bool isMove = false;

	vector<Move> moves = b.GenerateCaptures(isWhitePlayer);
	if (moves.size() > 0) {
		isMove = true;
	}


	Move bestMove;
	pair<double, vector<Move>> quiescenceData;
	pair<double, vector<Move>> bestMoveLine;

	double evali;
	double maxEval = -99999;
	double minEval = 99999;





	if (isWhitePlayer) {

		for (Move &move : moves) {

			b.MakeMove(move);
			quiescenceData = Quiescence(b, depth - 1, alpha, beta, false);
			evali = quiescenceData.first;
			b.UndoMove(move);



			if (evali > maxEval) {
				maxEval = evali;
				bestMove = move;
				bestMoveLine = quiescenceData;
			}

			// Alpha-Beta Pruning
			alpha = max(alpha, evali);
			if (beta <= alpha) {
				break;
			}
		}



		if (!isMove) {
			return { b.eval, emptyVec };
		}


		bestMoveLine.second.push_back(bestMove);

		return bestMoveLine;
	}





	else {

		for (Move &move : moves) {

			b.MakeMove(move);
			quiescenceData = Quiescence(b, depth - 1, alpha, beta, true);
			evali = quiescenceData.first;
			b.UndoMove(move);



			if (evali < minEval) {
				minEval = evali;
				bestMove = move;
				bestMoveLine = quiescenceData;
			}

			// Alpha-Beta Pruning
			beta = min(beta, evali);
			if (beta <= alpha) {
				break;
			}
		}



		if (!isMove) {
			return { b.eval, emptyVec };
		}


		bestMoveLine.second.push_back(bestMove);

		return bestMoveLine;
	}
}
