#include "beta.h"

using namespace std;



void Generate_PawnMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 1) {

		if (posY == 1 && !b.board[posX][posY + 1] && !b.board[posX][posY + 2]) {
			moves.push_back(Move(posX, posY, posX, posY + 2, 0.0));
		}

		if (!b.board[posX][posY + 1]) {
			moves.push_back(Move(posX, posY, posX, posY + 1, 0.0));
		}


		// Captures

		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board));
		}

		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board));
		}
	}

	else {

		if (posY == 6 && !b.board[posX][posY - 1] && !b.board[posX][posY - 2]) {
			moves.push_back(Move(posX, posY, posX, posY - 2, 0.0));
		}

		if (!b.board[posX][posY - 1]) {
			moves.push_back(Move(posX, posY, posX, posY - 1, 0.0));
		}


		// Captures

		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board));
		}

		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board));
		}
	}
}

void Generate_HorseMoves(Board& b, vector<Move>& moves, int posX, int posY) {
	
	if (b.board[posX][posY] == 3) {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 2, b.board));
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 2, b.board));
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 2, posY + 1, b.board));
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 2, posY + 1, b.board));
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 2, posY - 1, b.board));
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 2, posY - 1, b.board));
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 2, b.board));
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 2, b.board));
		}
	}

	else {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 2, b.board));
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 2, b.board));
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 2, posY + 1, b.board));
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 2, posY + 1, b.board));
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 2, posY - 1, b.board));
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 2, posY - 1, b.board));
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 2, b.board));
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 2, b.board));
		}
	}
}

void Generate_BishopMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 3.1) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}
			
			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
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
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_RookMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 5) {

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
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
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_QueenMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 9) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
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
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				moves.push_back(Move(posX, posY, x, y, 0.0));
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				moves.push_back(Move(posX, posY, posX, y, 0.0));
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				moves.push_back(Move(posX, posY, x, posY, 0.0));
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_KingMoves(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] = 100) {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX, posY + 1, b.board));
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board));
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board));
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY, b.board));
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY, b.board));
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX, posY - 1, b.board));
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board));
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] < 1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board));
		}
	}

	else {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX, posY + 1, b.board));
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board));
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board));
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY, b.board));
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY, b.board));
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX, posY - 1, b.board));
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board));
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > -1) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board));
		}
	}
}





void Generate_PawnCaptures(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 1) {

		if (b.board[posX + 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board));
		}

		if (b.board[posX - 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board));
		}
	}

	else {

		if (b.board[posX + 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board));
		}

		if (b.board[posX - 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board));
		}
	}
}

void Generate_HorseCaptures(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 3) {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 2, b.board));
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 2, b.board));
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX + 2, posY + 1, b.board));
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 2, posY + 1, b.board));
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] < 0) {
			moves.push_back(Move(posX, posY, posX + 2, posY - 1, b.board));
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 2, posY - 1, b.board));
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 2, b.board));
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 2, b.board));
		}
	}

	else {

		if (posX + 1 < 8 && posY + 2 < 8 && b.board[posX + 1][posY + 2] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 2, b.board));
		}

		if (posX - 1 > -1 && posY + 2 < 8 && b.board[posX - 1][posY + 2] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 2, b.board));
		}

		if (posX + 2 < 8 && posY + 1 < 8 && b.board[posX + 2][posY + 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 2, posY + 1, b.board));
		}

		if (posX - 2 > -1 && posY + 1 < 8 && b.board[posX - 2][posY + 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 2, posY + 1, b.board));
		}

		if (posX + 2 < 8 && posY - 1 > -1 && b.board[posX + 2][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 2, posY - 1, b.board));
		}

		if (posX - 2 > -1 && posY - 1 > -1 && b.board[posX - 2][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 2, posY - 1, b.board));
		}

		if (posX + 1 < 8 && posY - 2 > -1 && b.board[posX + 1][posY - 2] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 2, b.board));
		}

		if (posX - 1 > -1 && posY - 2 > -1 && b.board[posX - 1][posY - 2] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 2, b.board));
		}
	}
}

void Generate_BishopCaptures(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 3.1) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
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
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_RookCaptures(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 5) {

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
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
				continue;
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_QueenCaptures(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 9) {

		// Up Right
		for (int x = posX + 1, y = posY + 1; x < 8 && y < 8; x++, y++) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] < 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] < 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] < 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
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
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up Left
		for (int x = posX - 1, y = posY + 1; x > -1 && y < 8; x--, y++) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Right
		for (int x = posX + 1, y = posY - 1; x < 8 && y > -1; x++, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down Left
		for (int x = posX - 1, y = posY - 1; x > -1 && y > -1; x--, y--) {

			if (b.board[x][y] == 0) {
				continue;
			}

			else if (b.board[x][y] > 0) {
				moves.push_back(Move(posX, posY, x, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Up
		for (int y = posY + 1; y < 8; y++) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Down
		for (int y = posY - 1; y > -1; y--) {

			if (b.board[posX][y] == 0) {
				continue;
			}

			else if (b.board[posX][y] > 0) {
				moves.push_back(Move(posX, posY, posX, y, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Right
		for (int x = posX + 1; x < 8; x++) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}

		// Left
		for (int x = posX - 1; x > -1; x--) {

			if (b.board[x][posY] == 0) {
				continue;
			}

			else if (b.board[x][posY] > 0) {
				moves.push_back(Move(posX, posY, x, posY, b.board));
				break;
			}

			else {
				break;
			}
		}
	}
}

void Generate_KingCaptures(Board& b, vector<Move>& moves, int posX, int posY) {

	if (b.board[posX][posY] == 100) {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX, posY + 1, b.board));
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board));
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board));
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY, b.board));
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY, b.board));
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] < 0) {
			moves.push_back(Move(posX, posY, posX, posY - 1, b.board));
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] < 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board));
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] < 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board));
		}
	}

	else {

		// Up
		if (posY + 1 < 8 && b.board[posX][posY + 1] > 0) {
			moves.push_back(Move(posX, posY, posX, posY + 1, b.board));
		}

		// Up Right
		if (posX + 1 < 8 && posY + 1 < 8 && b.board[posX + 1][posY + 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY + 1, b.board));
		}

		// Up Left
		if (posX - 1 > -1 && posY + 1 < 8 && b.board[posX - 1][posY + 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY + 1, b.board));
		}

		// Right
		if (posX + 1 < 8 && b.board[posX + 1][posY] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY, b.board));
		}

		// Left
		if (posX - 1 > -1 && b.board[posX - 1][posY] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY, b.board));
		}

		// Down
		if (posY - 1 > -1 && b.board[posX][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX, posY - 1, b.board));
		}

		// Down Right
		if (posX + 1 < 8 && posY - 1 > -1 && b.board[posX + 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX + 1, posY - 1, b.board));
		}

		// Down Left
		if (posX - 1 > -1 && posY - 1 > -1 && b.board[posX - 1][posY - 1] > 0) {
			moves.push_back(Move(posX, posY, posX - 1, posY - 1, b.board));
		}
	}
}
