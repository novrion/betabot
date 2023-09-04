#include "beta.h"
using namespace std;
using namespace std::chrono;

int main() {

	Board b;
	U64 nodes = 0;
	int depth;


	cout << "depth: ";
	cin >> depth;

	duration<double> time;
	time_point<chrono::high_resolution_clock> start_time = high_resolution_clock::now();


	nodes = minimax(b, depth, 1);
	cout << nodes << "\n";

	time = high_resolution_clock::now() - start_time;
	cout << time.count() << "s\n";

	cout << nodes / time.count() << "n/s";

	return 0;
}