#include "search.h"
using namespace std;
using namespace std::chrono;


pair<int, U64> iterative_deepening(U64 bb[13], bool side, const double max_time) {

	pair<int, U64> search_data;
	pair<int, U64> search_data_copy;

	for (int depth = 1; depth < 256; ++depth) {

		search_data = layer_one_minimax(bb, depth, side, max_time);
		if (search_data.second == time_flag) return search_data_copy;

		search_data_copy = search_data;

		cout << depth << " ";
	}

	return { 0, 0 };
}

static inline pair<int, U64> layer_one_minimax(U64 bb[13], int depth, bool side, const double max_time) {

	int count = 1;
	duration<double> time;
	time_point<high_resolution_clock> start_time = high_resolution_clock::now();

	int alpha = -999999;
	int beta = 999999;

	int evaluation;
	U64 best_move;

	vector<U64> moves = generate_moves(bb, side);


	//time_point<high_resolution_clock> start_time1 = high_resolution_clock::now();

	sort(moves.begin(), moves.end(), [](const U64 a, const U64 b) {return get_move_capture(a) > get_move_capture(b); });
	//sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return (a + 50000 * position[get_move_piece(a)][get_move_to(a)]) > (b + 50000 * position[get_move_piece(b)][get_move_to(b)]); });

	//cout << (time = high_resolution_clock::now() - start_time1).count() << "\n";

	if (side) {

		int maxEval = -999999;

		for (int i = 0; i < moves.size(); ++i) {

			make_move(bb, moves[i], 1);
			evaluation = minimax(bb, depth - 1, 0, alpha, beta);
			undo_move(bb, moves[i]);


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

		for (int i = 0; i < moves.size(); ++i) {

			make_move(bb, moves[i], 0);
			evaluation = minimax(bb, depth - 1, 1, alpha, beta);
			undo_move(bb, moves[i]);


			if (evaluation < minEval) {
				minEval = evaluation;
				best_move = moves[i];
			}
			if ((time = high_resolution_clock::now() - start_time).count() > max_time) return { 0, time_flag };
		}

		return { minEval, best_move };
	}
}

static inline int minimax(U64 bb[13], int depth, bool side, int alpha, int beta) {

	if (!depth) return quiescence(bb, 4, side, alpha, beta);

	int evaluation;

	duration<double> time;
	time_point<high_resolution_clock> start_time = high_resolution_clock::now();

	vector<U64> moves = generate_moves(bb, side);

	cout << (time = high_resolution_clock::now() - start_time).count() << "\n";

	sort(moves.begin(), moves.end(), [](const U64 a, const U64 b) {return get_move_capture(a) > get_move_capture(b); });
	//sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return (a + position[get_move_piece(a)][get_move_to(a)]) > (b + position[get_move_piece(a)][get_move_to(a)]); });
	//sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return (a + 50000 * position[get_move_piece(a)][get_move_to(a)]) > (b + 50000 * position[get_move_piece(b)][get_move_to(b)]); });



	if (side) {

		int maxEval = -999999;

		for (int i = 0; i < moves.size(); ++i) {

			make_move(bb, moves[i], 1);
			if (get_move_capture(moves[i]) == 12) {
				undo_move(bb, moves[i]);
				return 100000 + depth;
			}

			evaluation = minimax(bb, depth - 1, 0, alpha, beta);
			undo_move(bb, moves[i]);


			maxEval = max(maxEval, evaluation);


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		int minEval = 999999;

		for (int i = 0; i < moves.size(); ++i) {

			make_move(bb, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				undo_move(bb, moves[i]);
				return (-100000 - depth);
			}

			evaluation = minimax(bb, depth - 1, 1, alpha, beta);
			undo_move(bb, moves[i]);


			minEval = min(minEval, evaluation);


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return minEval;
	}
}

static inline int quiescence(U64 bb[13], int depth, bool side, int alpha, int beta) {

	if (!depth) return evaluation(bb);

	
	int maxEval = evaluation(bb);

	int evaluation;
	vector<U64> moves = generate_captures(bb, side);
	//sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return a > b; });
	//sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return (a + position[get_move_piece(a)][get_move_to(a)]) > (b + position[get_move_piece(a)][get_move_to(a)]); });
	//sort(moves.begin(), moves.end(), [](U64 a, U64 b) {return (a + 50000 * position[get_move_piece(a)][get_move_to(a)]) > (b + 50000 * position[get_move_piece(b)][get_move_to(b)]); });



	if (side) {

		for (int i = 0; i < moves.size(); ++i) {

			make_move(bb, moves[i], 1);
			if (get_move_capture(moves[i]) == 12) {
				undo_move(bb, moves[i]);
				return (100000 + depth);
			}

			evaluation = quiescence(bb, depth - 1, 0, alpha, beta);
			undo_move(bb, moves[i]);


			maxEval = max(maxEval, evaluation);


			// alpha-beta pruning
			alpha = max(alpha, evaluation);
			if (beta <= alpha) break;
		}

		return maxEval;
	}


	else {

		int minEval = maxEval;

		for (int i = 0; i < moves.size(); ++i) {

			make_move(bb, moves[i], 0);
			if (get_move_capture(moves[i]) == 6) {
				undo_move(bb, moves[i]);
				return (-100000 - depth);
			}

			evaluation = quiescence(bb, depth - 1, 1, alpha, beta);
			undo_move(bb, moves[i]);


			minEval = min(minEval, evaluation);


			// alpha-beta pruning
			beta = min(beta, evaluation);
			if (beta <= alpha) break;
		}

		return minEval;
	}
}