#include "beta.h"

using namespace std;

// --- To Do ---
// 
// 1. Are pairs slow? Initializing with { } vs just using two values ? 
// 2. Only pass --int board[8][8]-- ?   Instead of --Board& b-- ? (GenerateMoves and other functions)
// 3. Struct Move with members vs having a large MakeMove() function ? Remember that when creating moves in piece.cpp, a constructor is used every time, which uses a lot of resources
// 4. Variables to keep last enPassant and if can castle.

int main() {

	vector<Move> matchLine;

	Board b;
	b.Initialize();

	int color = InputMatch(b, matchLine);
	int depth = InputDepth();
	bool player = InputColor();

	bool firstMove = false;
	int eval;

	int numPieces;
	bool flag1 = true;
	bool flag2 = true;
	bool flag3 = true;


	if (player && color >= 0) {
		Main_MakeMove(b, matchLine);
	}
	else if (!player && color) {
		Main_MakeMove(b, matchLine);
	}





	while (true) {

		// Logic ~ ~
		eval = firstLayerMinimax(b, depth, -999999, 999999, !player);
		matchLine.push_back(b.n_move);
		MakeMove(b, b.n_move);

		

		numPieces = GetPieces(b.board);
		if (numPieces < 15 && flag1) {
			flag1 = false;
			depth += 1;
		}
		if (numPieces < 10 && flag2) {
			flag2 = false;
			depth += 1;
		}
		if (numPieces < 7 && flag3) {
			flag3 = false;
			depth += 3;
		}


		// Print ~ ~
		PrintMain(b.board, eval, b.n_move, matchLine);


		// Input ~ ~
		Main_MakeMove(b, matchLine);
	}

	return 0;
}