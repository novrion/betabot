#include <iostream>
#include <map>

#include "Board.h"

using namespace std;



// The board? What happens to the board ???? Change function?
float Minimax(Board b, int depth, bool isWhitePlayer) {

	if (depth != b.depth) {
		b.MakeMove(b.nextMove.first, b.nextMove.second);
	}

	if (depth == 0) {
		return b.eval;
	}



	b.GetAllLegalMoves(isWhitePlayer);

	pair<pair<int, int>, pair<int, int>> storeMove;

	float evali;
	int maxEval = -99999;
	int minEval = 99999;





	if (isWhitePlayer) {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (auto move : b.boardPos[i][j].pieceLegalMoves) {

					b.nextMove = { move.first, move.second };

					evali = Minimax(b, depth - 1, false);

					if (evali > maxEval) {
						maxEval = evali;
						storeMove = move;
					}
				}
			}
		}

		if (depth == b.depth) {
			Board::bestMove = storeMove;
			return maxEval;
		}

		return maxEval;
	}










	else {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (auto move : b.boardPos[i][j].pieceLegalMoves) {

					b.nextMove = { move.first, move.second };

					evali = Minimax(b, depth - 1, true);

					if (evali < minEval) {
						minEval = evali;
						storeMove = move;
					}
				}
			}
		}

		if (depth == b.depth) {
			Board::bestMove = storeMove;
			return minEval;
		}

		return minEval;
	}
}