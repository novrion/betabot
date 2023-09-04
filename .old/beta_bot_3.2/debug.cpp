#include "debug.h"
using namespace std;


void debug_cout_board(const U64 bitboard) {

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (!y) {
				cout << "  " << 8 - x << "  ";
			}

			int square = x * 8 + y;
			cout << "   " << (get_bit(bitboard, square) ? 1 : 0);
		}

		cout << "\n\n";
	}

	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";

	cout << "\nBitboard: ";
	cout << bitboard << "\n\n\n";
}