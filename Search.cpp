#include <iostream>
#include <map>

#include "Board.h"

using namespace std;



double Minimax(Board b, int depth, double alpha, double beta, bool isWhitePlayer) {

	if (depth != b.depth) {
		b.MakeMove(b.nextMove.first, b.nextMove.second);
	}

	if (depth == 0) {
		return b.eval;
	}



	b.GetAllLegalMoves(isWhitePlayer);

	pair<pair<int, int>, pair<int, int>> storeMove;

	double evali;
	double maxEval = -99999;
	double minEval = 99999;





	if (isWhitePlayer) {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (auto move : b.boardPos[i][j].pieceLegalMoves) {

					//
				   // if (depth > 1) {
					//  cout << "d:" << depth << "   Move: " << TranslateToNotation(move) << "  i64: ";
					//  for (int a = 0; a < 8; a++) {
					 //   for (int c = 0; c < 8; c++) {
					 //     cout << b.boardPos[a][c].Type << " ";
					//    }
					//  }
					//  cout << endl;
				   // }

					//

					b.nextMove = move;

					evali = Minimax(b, depth - 1, alpha, beta, false);

					//
				  //  if (depth > 1) {
				  //    cout << "   Eval: " << evali << endl;
				  //  }
					//

					if (evali > maxEval) {
						maxEval = evali;
						storeMove = move;
					}

					// Alpha-Beta Pruning
					alpha = max(alpha, evali);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}

		if (depth == b.depth) {
			Board::bestMove = storeMove;
		}

		return maxEval;
	}





	else {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (auto move : b.boardPos[i][j].pieceLegalMoves) {

					//
				   // if (depth > 1) {
					//  cout << "d:" << depth << "   Move: " << TranslateToNotation(move) << "  i64: ";
					//  for (int a = 0; a < 8; a++) {
					//    for (int c = 0; c < 8; c++) {
					//      cout << b.boardPos[a][c].Type << " ";
				   //     }
				   //   }
				  //    cout << endl;
				  //  }

					//

					b.nextMove = move;

					evali = Minimax(b, depth - 1, alpha, beta, true);

					//
					//if (depth > 1) {
				  //   cout << "   Eval: " << evali << endl;
				   // }
					//


					if (evali < minEval) {
						minEval = evali;
						storeMove = move;
					}

					// Alpha-Beta Pruning
					beta = min(beta, evali);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}

		if (depth == b.depth) {
			Board::bestMove = storeMove;
		}

		return minEval;
	}
}