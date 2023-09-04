#include <vector>
#include <algorithm>

#include "Board.h"

using namespace std;


/*

----- Evaluation Parameters -----

(Castle) King protection eval: MakeMove()
Center pawn eval: MakeMove()
Mobility: Calculated in Piece.cpp and added to maxEval/minEval in Minimax() and Quiescence()

OrderMoves() orders according to these parameters but does not update eval
MakeMove() updates eval

----- Bug -----
?? Mobility parameter does not update on last node. Small loss of eval data. ?? <----------------------------------

*/




pair<double, vector<Move>> Minimax(Board& b, int depth, double alpha, double beta, bool isWhitePlayer);
pair<double, vector<Move>> Quiescence(Board& b, int depth, double alpha, double beta, bool isWhitePlayer);





pair<double, vector<Move>> Minimax(Board& b, int depth, double alpha, double beta, bool isWhitePlayer) {

	if (depth == 0) {
		if (isWhitePlayer) {
			return Quiescence(b, 4, alpha, beta, true);
		}
		return Quiescence(b, 4, alpha, beta, false);
	}
	

	// Make by reference !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pair<int, vector<Move>> moves = b.GenerateMoves(isWhitePlayer);
	int mobility = moves.first;

	Move bestMove;
	pair<double, vector<Move>> minimaxData;
	pair<double, vector<Move>> bestMoveLine;

	double evali;
	double maxEval = -99999;
	double minEval = 99999;





	if (isWhitePlayer) {

		for (Move &move : moves.second) {

			// King Capture
			if (move.isCapture < -9) {
				bestMoveLine.first = 999;
				bestMoveLine.second.push_back(move);
				return bestMoveLine;
			}

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
		bestMoveLine.first += 0.001 * mobility;

		return bestMoveLine;
	}





	else {

		for (Move &move : moves.second) {

			// King Capture
			if (move.isCapture > 9) {
				bestMoveLine.first = -999;
				bestMoveLine.second.push_back(move);
				return bestMoveLine;
			}

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
		bestMoveLine.first -= 0.001 * mobility;

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

	pair<int, vector<Move>> moves = b.GenerateCaptures(isWhitePlayer);
	if (moves.second.size() > 0) {
		isMove = true;
	}
	int mobility = moves.first;


	Move bestMove;
	pair<double, vector<Move>> quiescenceData;
	pair<double, vector<Move>> bestMoveLine = { b.eval, emptyVec };

	double evali;
	double maxEval = b.eval;
	double minEval = b.eval;





	if (isWhitePlayer) {

		for (Move &move : moves.second) {

			// King Capture
			if (move.isCapture < -9) {
				bestMoveLine.first = 999;
				bestMoveLine.second.push_back(move);
				return bestMoveLine;
			}

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

		for (Move &move : moves.second) {

			// King Capture
			if (move.isCapture > 9) {
				bestMoveLine.first = -999;
				bestMoveLine.second.push_back(move);
				return bestMoveLine;
			}

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







// Custom sort operator
bool comparator(Move& lhs, Move& rhs) {
	return lhs.isCapture < rhs.isCapture;
}


void OrderMoves(Board& b, pair<int, vector<Move>>& moves) {
	vector<Move> finalVec;

	sort(moves.second.begin(), moves.second.end(), &comparator);
}