#include "beta.h"
using namespace std;

int main() {

	Board b;
	int evaluation = 0;
	double max_time = 0.5;

	int turn = input_match(b);
	int colour = InputColor();

	if (turn != -1) {

		if (!turn && !colour || turn && colour) {

			evaluation = iterative_deepening(b, colour, max_time);
			make_move(b.b2, b.n_move, colour);

			cout_state(b, evaluation, b.n_move, colour);
		}
	}

	else if (colour) {

		evaluation = iterative_deepening(b, colour, max_time);
		make_move(b.b2, b.n_move, colour);

		cout_state(b, evaluation, b.n_move, colour);
	}



	while (true) {

		user_make_move(b, (colour ? 0 : 1));

		evaluation = iterative_deepening(b, colour, max_time);
		make_move(b.b2, b.n_move, colour);

		cout_state(b, evaluation, b.n_move, colour);
	}

	return 0;
}