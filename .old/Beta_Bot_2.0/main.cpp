#include "beta.h"

using namespace std;

// --- To Do ---
// 
// 1. Are pairs slow? Initializing with { } vs just using two values ? 
// 2. Only pass --int board[8][8]-- ?   Instead of --Board& b-- ? (GenerateMoves and other functions)
// 3. Struct Move with members vs having a large MakeMove() function ? Remember that when creating moves in piece.cpp, a constructor is used every time, which uses a lot of resources
// 4. Variables to keep last enPassant and if can castle.
// 5. Normal MakeMove eval for Quiescence? Probably good idea...

int main() {
	
	vector<Move> matchLine;

	Board b;
	b.Initialize();

	bool firstMove = false;
	int depth = InputDepth();
	//InputMatch(b);
	bool player = InputColor();
	int eval;

	//int numPieces;
	//bool flag1 = true;
	//bool flag2 = true;


	if (player) {
		Main_MakeMove(b, matchLine);
	}



	while (true) {

		// Logic ~ ~
		eval = firstLayerMinimax(b, depth, -999999, 999999, !player);
		matchLine.push_back(b.n_move);
		MakeMove(b, b.n_move);

		// Print ~ ~
		PrintMain(b.board, eval, b.n_move, matchLine);
		//cout << TranslateToNotation(matchLine[0]);

		//numPieces = GetPieces(b.board);
		//if (numPieces < 10 && flag1) {
			//flag1 = false;
			//depth += 1;
		//}
		//if (numPieces < 5 && flag2) {
			//flag2 = false;
			//depth += 1;
		//}

		// Input ~ ~
		Main_MakeMove(b, matchLine);
	}

	return 0;
}