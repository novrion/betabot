#include "beta.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

// --- To Do ---
// 
// 1. Are pairs slow? Initializing with { } vs just using two values ? 
// 2. Only pass --int board[8][8]-- ?   Instead of --Board& b-- ? (GenerateMoves and other functions)
// 3. Struct Move with members vs having a large MakeMove() function ? Remember that when creating moves in piece.cpp, a constructor is used every time, which uses a lot of resources
// 4. Variables to keep last enPassant and if can castle.

int main() {

	Board b;
	b.Initialize();

	int nodes = 0;
	int depth;


	cout << "depth: ";
	cin >> depth;

	duration<double> time;
	time_point<chrono::high_resolution_clock> start_time = high_resolution_clock::now();


	nodes = Minimax(b, depth, 1);
	cout << nodes << "\n";

	time = high_resolution_clock::now() - start_time;
	cout << time.count() << "\n";

	cout << nodes / time.count() << "n/s";

	return 0;
}