#include "beta.h"
#include <chrono>

using namespace std;
using namespace std::chrono;



void Generate_PawnMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 1000) {

		// Captures
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 0) {
			//time_point<high_resolution_clock> start_time = high_resolution_clock::now();


			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board[posX + 1][posY + 1]));

			//time_point<high_resolution_clock> stop_time = high_resolution_clock::now();
			//	duration<double> time = stop_time - start_time;
				//cout << time.count() << "\n";
		}

		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board[posX - 1][posY + 1]));
		}


		if (posY + 1 < 8 && !b.board[posX][posY + 1]) {
			moves.push_back(Move(posX, posY, posX, posY + 1, 0));

			// Promotion
			if (posY + 1 == 7) {
				moves.push_back(Move(posX, posY, posX, 7, -9000, 1000, 0, 0));
			}


			if (posY == 1 && !b.board[posX][posY + 2]) {
				moves.push_back(Move(posX, posY, posX, posY + 2, 0));
			}
		}

		/*// En Passant
		if (b.enPassant.first != -1 && b.enPassant.second == 4 && posY == b.enPassant.second) {

			if (b.enPassant.first == posX + 1) {
				moves.push_back(Move(posX, posY, posX + 1, posY + 1, -1000, 0, 1000));
			}

			else if (b.enPassant.first == posX - 1) {
				moves.push_back(Move(posX, posY, posX - 1, posY + 1, -1000, 0, 1000));
			}
		}*/
	}

	else {

		// Captures
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board[posX + 1][posY - 1]));
		}

		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board[posX - 1][posY - 1]));
		}


		if (posY - 1 > -1 && !b.board[posX][posY - 1]) {
			moves.push_back(Move(posX, posY, posX, posY - 1, 0));

			// Promotion
			if (posY - 1 == 7) {
				moves.push_back(Move(posX, posY, posX, 0, 9000, -1000, 0, 0));
			}


			if (posY == 6 && !b.board[posX][posY - 2]) {
				moves.push_back(Move(posX, posY, posX, posY - 2, 0));
			}
		}

		/*// En Passant
		if (b.enPassant.first != -1 && b.enPassant.second == 3 && posY == b.enPassant.second) {

			if (b.enPassant.first == posX + 1) {
				moves.push_back(Move(posX, posY, posX + 1, posY - 1, -1000, 0, -1000));
			}

			else if (b.enPassant.first == posX - 1) {
				moves.push_back(Move(posX, posY, posX - 1, posY - 1, -1000, 0, -1000));
			}
		}*/
	}
}

void Generate_HorseMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	//time_point<high_resolution_clock> start_time = high_resolution_clock::now();

	if (b.board[posX][posY] == 3000) {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 2, b.board[posX + 1][posY + 2]));
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 2, b.board[posX - 1][posY + 2]));
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 2, posY + 1, b.board[posX + 2][posY + 1]));
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 2, posY + 1, b.board[posX - 2][posY + 1]));
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 2, posY - 1, b.board[posX + 2][posY - 1]));
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 2, posY - 1, b.board[posX - 2][posY - 1]));
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 2, b.board[posX + 1][posY - 2]));
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 2, b.board[posX - 1][posY - 2]));
		}
	}

	else {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 2, b.board[posX + 1][posY + 2]));
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 2, b.board[posX - 1][posY + 2]));
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 2, posY + 1, b.board[posX + 2][posY + 1]));
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 2, posY + 1, b.board[posX - 2][posY + 1]));
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 2, posY - 1, b.board[posX + 2][posY - 1]));
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 2, posY - 1, b.board[posX - 2][posY - 1]));
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 2, b.board[posX + 1][posY - 2]));
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 2, b.board[posX - 1][posY - 2]));
		}
	}

	//time_point<high_resolution_clock> stop_time = high_resolution_clock::now();
	//duration<double> time = stop_time - start_time;
	//cout << time.count() << "\n";
}

void Generate_BishopMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 3100) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_RookMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 5000) {

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_QueenMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 9000) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}
	}

	else {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board[x][y]));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board[posX][y]));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board[x][posY]));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_KingMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 100000) {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX, posY + 1, b.board[posX][posY + 1]));
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board[posX + 1][posY + 1]));
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board[posX - 1][posY + 1]));
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY, b.board[posX + 1][posY]));
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY, b.board[posX - 1][posY]));
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX, posY - 1, b.board[posX][posY - 1]));
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board[posX + 1][posY - 1]));
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board[posX - 1][posY - 1]));
		}


		// Castle
		// Fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (1) {

			// King, Rook & Space Between
			if (b.board[5][0] || b.board[6][0] || b.board[7][0] != 5000 || posX != 4 || posY != 0) {
				goto w_jump;
			}

			// Left
			for (int x = 3; x > -1; x--) {
				if (!b.board[x][0]) {
					continue;
				}
				else if (b.board[x][0] == -5000 || b.board[x][0] == -9000) {
					goto w_jump;
				}
				else {
					break;
				}
			}



			for (int i = 4; i < 7; i++) {

				// Up Right
				for (int x = i + 1, y = 1; x < 8 && y < 8; x++, y++) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == -3100 || b.board[x][y] == -9000) {
						goto w_jump;
					}
					else {
						break;
					}
				}

				// Up Left
				for (int x = i - 1, y = 1; x > -1 && y < 8; x--, y++) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == -3100 || b.board[x][y] == -9000) {
						goto w_jump;
					}
					else {
						break;
					}
				}

				// Up
				for (int y = 1; y < 8; y++) {

					if (!b.board[i][y]) {
						continue;
					}
					else if (b.board[i][y] == -5000 || b.board[i][y] == -9000) {
						goto w_jump;
					}
					else {
						break;
					}
				}
			}



			// Horse
			for (int x = 3; x < 8; x++) {
				for (int y = 1; y < 3; y++) {
					if (b.board[x][y] == -3000) {
						goto w_jump;
					}
				}
			}
			if (b.board[2][1] == -3000) {
				goto w_jump;
			}

			// Pawn
			for (int x = 3; x < 8; x++) {
				if (b.board[x][1] == -1000) {
					goto w_jump;
				}
			}

			// King
			if (b.board[6][1] == -100000) {
				goto w_jump;
			}

			moves.push_back(Move(4, 0, 6, 0, 0, 0, 0, 1));


		w_jump:

			// King, Rook & Space Between
			if (b.board[3][0] || b.board[2][0] || b.board[1][0] || b.board[0][0] != 5000 || posX != 4 || posY != 0) {
				return;
			}

			// Right
			for (int x = 5; x < 8; x++) {
				if (!b.board[x][0]) {
					continue;
				}
				else if (b.board[x][0] == -5000 || b.board[x][0] == -9000) {
					return;
				}
				else {
					break;
				}
			}

			for (int i = 4; i > 0; i--) {

				// Up Right
				for (int x = i + 1, y = 1; x < 8 && y < 8; x++, y++) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == -3100 || b.board[x][y] == -9000) {
						return;
					}
					else {
						break;
					}
				}

				// Up Left
				for (int x = i - 1, y = 1; x > -1 && y < 8; x--, y++) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == -3100 || b.board[x][y] == -9000) {
						return;
					}
					else {
						break;
					}
				}

				// Up
				for (int y = 1; y < 8; y++) {

					if (!b.board[i][y]) {
						continue;
					}
					else if (b.board[i][y] == -5000 || b.board[i][y] == -9000) {
						return;
					}
					else {
						break;
					}
				}
			}



			// Horse
			for (int x = 5; x > -1; x--) {
				for (int y = 1; y < 3; y++) {
					if (b.board[x][y] == -3000) {
						return;
					}
				}
			}
			if (b.board[6][1] == -3000) {
				return;
			}

			// Pawn
			for (int x = 5; x > -1; x--) {
				if (b.board[x][1] == -1000) {
					return;
				}
			}

			// King
			if (b.board[1][1] == -100000) {
				return;
			}

			moves.push_back(Move(4, 0, 2, 0, 0, 0, 0, 2));
		}
	}

	else {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX, posY + 1, b.board[posX][posY + 1]));
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board[posX + 1][posY + 1]));
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board[posX - 1][posY + 1]));
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY, b.board[posX + 1][posY]));
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY, b.board[posX - 1][posY]));
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX, posY - 1, b.board[posX][posY - 1]));
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board[posX + 1][posY - 1]));
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board[posX - 1][posY - 1]));
		}


		// Castle
		// Fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (1) {

			// King, Rook & Space Between
			if (b.board[5][7] || b.board[6][7] || b.board[7][7] != -5000 || posX != 4 || posY != 7) {
				goto b_jump;
			}

			// Left
			for (int x = 3; x > -1; x--) {
				if (!b.board[x][7]) {
					continue;
				}
				else if (b.board[x][7] == 5000 || b.board[x][7] == 9000) {
					goto b_jump;
				}
				else {
					break;
				}
			}



			for (int i = 4; i < 7; i++) {

				// Down Right
				for (int x = i + 1, y = 6; x < 8 && y > -1; x++, y--) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == 3100 || b.board[x][y] == 9000) {
						goto b_jump;
					}
					else {
						break;
					}
				}

				// Down Left
				for (int x = i - 1, y = 6; x > -1 && y > -1; x--, y--) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == 3100 || b.board[x][y] == 9000) {
						goto b_jump;
					}
					else {
						break;
					}
				}

				// Down
				for (int y = 6; y > -1; y--) {

					if (!b.board[i][y]) {
						continue;
					}
					else if (b.board[i][y] == 5000 || b.board[i][y] == 9000) {
						goto b_jump;
					}
					else {
						break;
					}
				}
			}



			// Horse
			for (int x = 3; x < 8; x++) {
				for (int y = 5; y < 7; y++) {
					if (b.board[x][y] == 3000) {
						goto b_jump;
					}
				}
			}
			if (b.board[2][6] == 3000) {
				goto b_jump;
			}

			// Pawn
			for (int x = 3; x < 8; x++) {
				if (b.board[x][6] == 1000) {
					goto b_jump;
				}
			}

			// King
			if (b.board[6][6] == 100000) {
				goto b_jump;
			}

			moves.push_back(Move(4, 7, 6, 7, 0, 0, 0, 3));


		b_jump:

			// King, Rook & Space Between
			if (b.board[3][7] || b.board[2][7] || b.board[1][7] || b.board[0][7] != -5000 || posX != 4 || posY != 7) {
				return;
			}

			// Right
			for (int x = 5; x < 8; x++) {
				if (!b.board[x][7]) {
					continue;
				}
				else if (b.board[x][7] == 5000 || b.board[x][7] == 9000) {
					return;
				}
				else {
					break;
				}
			}



			for (int i = 4; i > 0; i--) {

				// Down Right
				for (int x = i + 1, y = 6; x < 8 && y > -1; x++, y--) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == 3100 || b.board[x][y] == 9000) {
						return;
					}
					else {
						break;
					}
				}

				// Down Left
				for (int x = i - 1, y = 6; x > -1 && y > -1; x--, y--) {

					if (!b.board[x][y]) {
						continue;
					}
					else if (b.board[x][y] == 3100 || b.board[x][y] == 9000) {
						return;
					}
					else {
						break;
					}
				}

				// Down
				for (int y = 6; y > -1; y--) {

					if (!b.board[i][y]) {
						continue;
					}
					else if (b.board[i][y] == 5000 || b.board[i][y] == 9000) {
						return;
					}
					else {
						break;
					}
				}
			}



			// Horse
			for (int x = 5; x > -1; x--) {
				for (int y = 5; y < 7; y++) {
					if (b.board[x][y] == 3000) {
						return;
					}
				}
			}
			if (b.board[6][6] == 3000) {
				return;
			}

			// Pawn
			for (int x = 5; x > -1; x--) {
				if (b.board[x][6] == 1000) {
					return;
				}
			}

			// King
			if (b.board[1][6] == 100000) {
				return;
			}

			moves.push_back(Move(4, 7, 2, 7, 0, 0, 0, 4));
		}
	}
}