#include "beta.h"
using namespace std;
using namespace std::chrono;

int position_matrix[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 3, 2, 1, 0,
	0, 2, 4, 4, 4, 4, 2, 0,
	0, 3, 4, 5, 5, 4, 3, 0,
	0, 3, 4, 5, 5, 4, 3, 0,
	0, 2, 4, 4, 4, 4, 2, 0,
	0, 1, 2, 3, 3, 2, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

int Evaluation(U64 b2[13]) {

	int evaluation = 0;

	evaluation += 1000 * popcount(b2[1]);
	evaluation += 3000 * popcount(b2[2]);
	evaluation += 3000 * popcount(b2[3]);
	evaluation += 5000 * popcount(b2[4]);
	evaluation += 9000 * popcount(b2[5]);
	evaluation += 100000 * popcount(b2[6]);

	evaluation -= 1000 * popcount(b2[7]);
	evaluation -= 3000 * popcount(b2[8]);
	evaluation -= 3000 * popcount(b2[9]);
	evaluation -= 5000 * popcount(b2[10]);
	evaluation -= 9000 * popcount(b2[11]);
	evaluation -= 100000 * popcount(b2[12]);

	return evaluation;
}

pair<int, vector<U64>> quiescence(U64 b2[13], int depth, int alpha, int beta, int colour) {

	vector<U64> line;
	if (!depth) return { Evaluation(b2), line };

	pair<int, vector<U64>> input;


	int minEval = Evaluation(b2);
	int maxEval = minEval;

	int evaluation;

	set<U64> moves;
	gen_captures(b2, colour, moves);
	set<U64>::reverse_iterator rit;


	if (colour) {

		for (rit = moves.rbegin(); rit != moves.rend(); rit++) {

			make_move(b2, *rit, colour);

			//
			input = quiescence(b2, depth - 1, alpha, beta, 0);
			evaluation = input.first;
			//

			undo_move(b2, *rit, colour);


			if (evaluation > maxEval) {
				maxEval = evaluation;

				line = input.second;
				line.push_back(*rit);
			}

			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return { maxEval, line };
	}


	else {

		for (rit = moves.rbegin(); rit != moves.rend(); rit++) {

			make_move(b2, *rit, colour);

			//
			input = quiescence(b2, depth - 1, alpha, beta, 1);
			evaluation = input.first;
			//
			undo_move(b2, *rit, colour);

			if (evaluation < minEval) {
				minEval = evaluation;

				line = input.second;
				line.push_back(*rit);
			}

			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return { minEval, line };
	}
}

pair<int, vector<U64>> minimax(U64 b2[13], int depth, int alpha, int beta, int colour) {

	vector<U64> line;
	if (!depth) return quiescence(b2, 4, alpha, beta, colour);


	pair<int, vector<U64>> input;


	int minEval = 999999;
	int maxEval = -999999;

	int evaluation;

	set<U64> moves;
	gen_moves(b2, colour, moves);
	set<U64>::reverse_iterator rit;


	if (colour) {

		for (rit = moves.rbegin(); rit != moves.rend(); rit++) {

			make_move(b2, *rit, colour);

			//
			input = minimax(b2, depth - 1, alpha, beta, 0);
			evaluation = input.first;
			//
			undo_move(b2, *rit, colour);


			if (evaluation > maxEval) {
				maxEval = evaluation;

				line = input.second;
				line.push_back(*rit);
			}

			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return { maxEval, line };
	}


	else {

		for (rit = moves.rbegin(); rit != moves.rend(); rit++) {

			make_move(b2, *rit, colour);

			//
			input = minimax(b2, depth - 1, alpha, beta, 1);
			evaluation = input.first;
			//
			undo_move(b2, *rit, colour);

			if (evaluation < minEval) {
				minEval = evaluation;

				line = input.second;
				line.push_back(*rit);
			}

			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return { minEval, line };
	}
}

int first_layer_minimax(Board& b, int depth, int colour) {

	vector<U64> line;
	pair<int, vector<U64>> input;



	int alpha = -9999999;
	int beta = 9999999;

	int minEval = 999999;
	int maxEval = -999999;

	int evaluation;

	set<U64> moves;
	gen_moves(b.b2, colour, moves);
	set<U64>::reverse_iterator rit;


	if (colour) {

		for (rit = moves.rbegin(); rit != moves.rend(); rit++) {
			cout << translate_to_notation(*rit) << "\n";

			make_move(b.b2, *rit, colour);

			//
			input = minimax(b.b2, depth - 1, alpha, beta, 0);
			evaluation = input.first;
			//
			undo_move(b.b2, *rit, colour);


			if (evaluation > maxEval) {
				maxEval = evaluation;
				b.n_move = *rit;

				line = input.second;
				line.push_back(*rit);
			}

			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		////
		cout << "line:\n";
		for (U64 move : line) {
			cout << translate_to_notation(move) << "\n";
		}
		cout << "\n";
		////

		return maxEval;
	}


	else {

		for (rit = moves.rbegin(); rit != moves.rend(); rit++) {
			cout << translate_to_notation(*rit) << "\n";

			make_move(b.b2, *rit, colour);

			//
			input = minimax(b.b2, depth - 1, alpha, beta, 1);
			evaluation = input.first;
			//
			undo_move(b.b2, *rit, colour);


			if (evaluation < minEval) {
				minEval = evaluation;
				b.n_move = *rit;

				line = input.second;
				line.push_back(*rit);
			}

			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		////
		cout << "line:\n";
		for (U64 move : line) {
			cout << translate_to_notation(move) << "\n";
		}
		cout << "\n";
		////

		return minEval;
	}
}

int iterative_deepening(Board& b, int colour, double max_time) {

	time_point<chrono::high_resolution_clock> start_time;
	duration<double> time;

	int evaluation = 0;
	int depth = 1;


	while (true) {

		cout << depth << " ";
		start_time = high_resolution_clock::now();

		evaluation = first_layer_minimax(b, depth, colour);

		if ((time = high_resolution_clock::now() - start_time).count() > max_time) {
			cout << "\n";
			return evaluation;
		}

		depth++;
	}
}