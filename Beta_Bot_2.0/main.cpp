#include "beta.h"
#include <iostream>
using namespace std;

// --- To Do ---
// 
// 1. Are pairs slow? Initializing with { } vs just using two values ? 
// 2. Only pass --int board[8][8]-- ?   Instead of --Board& b-- ? (GenerateMoves and other functions)
// 3. Struct Move with members vs having a large MakeMove() function ? Remember that when creating moves in piece.cpp, a constructor is used every time, which uses a lot of resources

int main() {

	bool firstMove = false;
	bool player = InputColor();
	int depth = InputDepth();
	double eval;


	Board b;
	b.Initialize();

	if (player) {
		Main_MakeMove(b);
	}



	while (true) {

		// Logic ~ ~
		eval = firstLayerMinimax(b, depth, -999, 999, !player);
		MakeMove(b, b.n_move);

		// Print ~ ~
		PrintMain(b.board, eval, b.n_move);

		// Input ~ ~
		Main_MakeMove(b);
	}

	return 0;
}
