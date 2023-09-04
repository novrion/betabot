#include "board.h"

using namespace std;


void printBitBoard(u64 bitboard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int square = i * 8 + j;
            cout << ((bitboard & (1ULL << square)) ? 1 : 0) << " ";
        }
        cout << endl;
    }
    return;
}