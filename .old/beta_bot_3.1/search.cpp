#include "beta.h"
using namespace std;
using namespace std::chrono;



int quiescence(U64 b2[13], int depth, int alpha, int beta, int colour) {

	if (!depth) return Evaluation(b2);


	int minEval = Evaluation(b2);
	int maxEval = minEval;

	int evaluation;

	vector<U64> moves;
	gen_captures(b2, colour, moves);
	sort(moves.begin(), moves.end());


	if (colour) {

		for (int i = moves.size() - 1; i > -1; --i) {

			make_move(b2, moves[i], 1);
			if (get_move_capture(moves[i]) == 12) {
				undo_move(b2, moves[i], 1);
				return (100000 + depth);
			}

			evaluation = quiescence(b2, depth - 1, alpha, beta, 0);
			undo_move(b2, moves[i], 1);


			if (evaluation > maxEval) maxEval = evaluation;


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		for (int i = moves.size() - 1; i > -1; --i) {

			make_move(b2, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				undo_move(b2, moves[i], 0);
				return (-100000 - depth);
			}

			evaluation = quiescence(b2, depth - 1, alpha, beta, 1);
			undo_move(b2, moves[i], 0);


			if (evaluation < minEval) minEval = evaluation;


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return minEval;
	}
}

int minimax(U64 b2[13], int depth, int alpha, int beta, int colour) {

	if (!depth) return quiescence(b2, 4, alpha, beta, colour);


	int minEval = 999999;
	int maxEval = -999999;
	int evaluation;

	vector<U64> moves;
	gen_moves(b2, colour, moves);
	sort(moves.begin(), moves.end());


	if (colour) {

		for (int i = moves.size() - 1; i > -1; --i) {

			duration<double> time;
			time_point<high_resolution_clock> start_time = high_resolution_clock::now();

			make_move(b2, moves[i], 1);

			cout << (time = high_resolution_clock::now() - start_time).count() << "\n";


			if (get_move_capture(moves[i]) == 12) {
				undo_move(b2, moves[i], 1);
				return (100000 + depth);
			}

			evaluation = minimax(b2, depth - 1, alpha, beta, 0);
			undo_move(b2, moves[i], 1);


			if (evaluation > maxEval) maxEval = evaluation;


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		for (int i = moves.size() - 1; i > -1; --i) {

			make_move(b2, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				undo_move(b2, moves[i], 0);
				return (-100000 - depth);
			}

			evaluation = minimax(b2, depth - 1, alpha, beta, 1);
			undo_move(b2, moves[i], 0);


			if (evaluation < minEval) minEval = evaluation;


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return minEval;
	}
}

pair<int, bool> first_layer_minimax(Board& b, int depth, int colour, int max_time) {

	time_point<chrono::high_resolution_clock> start_time = high_resolution_clock::now();
	duration<double> time;
	bool is_max_time = false;
	U64 b_move = b.n_move;

	int alpha = -999999;
	int beta = 999999;

	int minEval = 999999;
	int maxEval = -999999;
	int evaluation;

	vector<U64> moves;
	gen_moves(b.b2, colour, moves);
	sort(moves.begin(), moves.end());

	int count = 1;
	if (colour) {

		for (int i = moves.size() - 1; i > -1; --i) {

			cout << count++ << " ";

			make_move(b.b2, moves[i], 1);
			if (get_move_capture(moves[i]) == 12) {
				undo_move(b.b2, moves[i], 1);
				return { (100000 + depth), 1 };
			}

			evaluation = minimax(b.b2, depth - 1, alpha, beta, 0);
			undo_move(b.b2, moves[i], 1);



			if (evaluation > maxEval) {
				maxEval = evaluation;
				b.n_move = moves[i];
			}


			if ((time = high_resolution_clock::now() - start_time).count() > max_time) {
				b.n_move = b_move;
				return { maxEval , 1 };
			}


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		cout << "}\n";
		return { maxEval, 0 };
	}


	else {

		for (int i = moves.size() - 1; i > -1; --i) {

			cout << count++ << " ";

			make_move(b.b2, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				undo_move(b.b2, moves[i], 0);
				return { (-100000 - depth), 1 };
			}

			evaluation = minimax(b.b2, depth - 1, alpha, beta, 1);
			undo_move(b.b2, moves[i], 0);



			if (evaluation < minEval) {
				minEval = evaluation;
				b.n_move = moves[i];
			}


			if ((time = high_resolution_clock::now() - start_time).count() > max_time) {
				b.n_move = b_move;
				return { minEval, 1 };
			}


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		cout << "}\n";
		return { minEval, 0 };
	}
}

int iterative_deepening(Board& b, int colour, double max_time) {

	pair<int, bool> evaluation = { 0, false };
	int evaluation_copy = 0;
	int depth = 1;


	while (true) {

		cout << depth << " { ";

		evaluation = first_layer_minimax(b, depth, colour, max_time);
		if (evaluation.second) {
			cout << "\n";
			return evaluation_copy;
		}

		evaluation_copy = evaluation.first;
		depth++;
	}
}