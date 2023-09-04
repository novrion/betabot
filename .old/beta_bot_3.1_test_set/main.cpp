#include "beta.h"
using namespace std;
using namespace std::chrono;

int main() {

	Board b;
	int nodes = 0;
	int depth;


	cout << "depth: ";
	cin >> depth;

	duration<double> time;
	time_point<chrono::high_resolution_clock> start_time = high_resolution_clock::now();;


	nodes = minimax(b.b2, depth, 1);
	cout << nodes << "\n";

	time = high_resolution_clock::now() - start_time;
	cout << time.count() << "\n";

	cout << nodes / time.count();


	return 0;
}