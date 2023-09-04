#include "beta.h"
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;


void PrintBoard(U64 bitboard) {

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (!y) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << "  " << 8 - x << "  ";
				SetConsoleTextAttribute(hConsole, 7);
			}

			int square = x * 8 + y;
			cout << "   " << (get_bit(bitboard, square) ? 1 : 0);
		}

		cout << "\n\n";
	}

	SetConsoleTextAttribute(hConsole, 11);
	cout << "\n        " << "A   B   C   D   E   F   G   H" << "\n";
	SetConsoleTextAttribute(hConsole, 7);

	cout << "\nBitboard: ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << bitboard << "\n\n\n";
	SetConsoleTextAttribute(hConsole, 7);
}