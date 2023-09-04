#include "search.h"
using namespace std;
using namespace std::chrono;


pair<int, U64> iterative_deepening(Board& b, bool side, const double max_time) {

	pair<int, U64> search_data;
	pair<int, U64> search_data_copy;

	for (int depth = 1; depth < 256; ++depth) {

		search_data = layer_one_minimax(b, depth, side, max_time);
		if (search_data.second == time_flag) return search_data_copy;

		search_data_copy = search_data;

		cout << depth << " ";
	}

	return { 0, 0 };
}

static inline pair<int, U64> layer_one_minimax(Board& b, int depth, bool side, const double max_time) {

	int count = 1;
	duration<double> time;
	time_point<high_resolution_clock> start_time = high_resolution_clock::now();

	int alpha = -999999;
	int beta = 999999;

	int evaluation;
	U64 best_move;

	U64 moves[100];
	moves[99] = 0;
	generate_moves(b.bb, moves, side);
	sort(moves, moves + moves[99], [](const U64 a, const U64 b) {return get_move_capture(a) > get_move_capture(b); });


	if (side) {

		int maxEval = -999999;

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			MakeMove(b_copy.bb, moves[i], 1);
			evaluation = minimax(b_copy, depth - 1, 0, alpha, beta);

			//b = b_copy;


			if (evaluation > maxEval) {
				maxEval = evaluation;
				best_move = moves[i];
			}
			if ((time = high_resolution_clock::now() - start_time).count() > max_time) return { 0, time_flag };
		}

		return { maxEval, best_move };
	}


	else {

		int minEval = 999999;

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			MakeMove(b_copy.bb, moves[i], 0);
			evaluation = minimax(b_copy, depth - 1, 1, alpha, beta);

			//b = b_copy;

			if (evaluation < minEval) {
				minEval = evaluation;
				best_move = moves[i];
			}
			if ((time = high_resolution_clock::now() - start_time).count() > max_time) return { 0, time_flag };
		}

		return { minEval, best_move };
	}
}

static inline int minimax(Board& b, int depth, bool side, int alpha, int beta) {

	if (!depth) return quiescence(b, 4, side, alpha, beta);

	int evaluation;

	U64 moves[100];
	moves[99] = 0;
	generate_moves(b.bb, moves, side);
	sort(moves, moves + moves[99], [](const U64 a, const U64 b) {return get_move_capture(a) > get_move_capture(b); });


	if (side) {

		int maxEval = -999999;

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			// massive BUG!!!!!!!!!!!!! should be MakeMove(b_copy.bb...

			MakeMove(b_copy.bb, moves[i], 1);
			if (get_move_capture(moves[i]) == 12) {
				return (100000 + depth);
			}

			evaluation = minimax(b_copy, depth - 1, 0, alpha, beta);

			// Literally dumbest shit ever just delete "b = b_copy;" Why the fuck?
			// Or ? Am I dumb? minimax(Board& b) It is by reference... ???

			//b = b_copy;

			maxEval = max(maxEval, evaluation);


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		int minEval = 999999;

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			MakeMove(b_copy.bb, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				return (-100000 - depth);
			}

			evaluation = minimax(b_copy, depth - 1, 1, alpha, beta);
			//b = b_copy;

			minEval = min(minEval, evaluation);


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return minEval;
	}
}

static inline int quiescence(Board& b, int depth, bool side, int alpha, int beta) {

	if (!depth) return Evaluate(b.bb);



	int evaluation;
	
	U64 moves[100];
	moves[99] = 0;
	generate_captures(b.bb, moves, b.side);


	if (side) {

		int maxEval = Evaluate(b.bb);

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			MakeMove(b_copy.bb, moves[i], 1);
			if (get_move_capture(moves[i]) == 12) {
				return (100000 + depth);
			}

			evaluation = quiescence(b_copy, depth - 1, 0, alpha, beta);
			//b = b_copy;

			maxEval = max(maxEval, evaluation);


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		int minEval = Evaluate(b.bb);

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			MakeMove(b_copy.bb, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				return (-100000 - depth);
			}

			evaluation = quiescence(b_copy, depth - 1, 1, alpha, beta);
			//b = b_copy;

			minEval = min(minEval, evaluation);


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return minEval;
	}
}