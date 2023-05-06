#include <vector>
#include "beta.h"

using namespace std;



void Board::Initialize() {

	// Eval & En Passant
	this->eval = 0;
	this->enPassant = { -1, 0 };



	// Space
	for (int x = 0; x < 8; x++) {
		for (int y = 2; y < 6; y++) {
			this->board[x][y] = 0;
		}
	}

	// Pawn
	for (int x = 0; x < 8; x++) {
		this->board[x][1] = 1;
		this->board[x][6] = -1;
	}

	// Horse
	this->board[1][0] = 3;
	this->board[6][0] = 3;

	this->board[1][7] = -3;
	this->board[6][7] = -3;


	// Bishop
	this->board[2][0] = 3.1;
	this->board[5][0] = 3.1;

	this->board[2][7] = -3.1;
	this->board[5][7] = -3.1;


	// Rook
	this->board[0][0] = 5;
	this->board[7][0] = 5;

	this->board[0][7] = -5;
	this->board[7][7] = -5;


	// Queen
	this->board[3][0] = 9;

	this->board[3][7] = -9;


	// King
	this->board[4][0] = 100;

	this->board[4][7] = -100;
}



void GenerateMoves(Board& b, vector<Move>& moves, bool player, bool onlyCapture) {

	if (!onlyCapture) {

		if (player) {

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {

					if (b.board[x][y] == 0) {
						continue;
					}

					else if (b.board[x][y] == 1) {
						Generate_PawnMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 3) {
						Generate_HorseMoves(b, moves, x, y);

					}

					else if (b.board[x][y] == 3.1) {
						Generate_BishopMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 5) {
						Generate_RookMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 9) {
						Generate_QueenMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 100) {
						Generate_KingMoves(b, moves, x, y);
					}
				}
			}
		}

		else {

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {

					if (b.board[x][y] == 0) {
						continue;
					}

					else if (b.board[x][y] == -1) {
						Generate_PawnMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -3) {
						Generate_HorseMoves(b, moves, x, y);

					}

					else if (b.board[x][y] == -3.1) {
						Generate_BishopMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -5) {
						Generate_RookMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -9) {
						Generate_QueenMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -100) {
						Generate_KingMoves(b, moves, x, y);
					}
				}
			}
		}
	}



	else {

		if (player) {

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {

					if (b.board[x][y] == 0) {
						continue;
					}

					else if (b.board[x][y] == 1) {
						Generate_PawnCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 3) {
						Generate_HorseCaptures(b, moves, x, y);

					}

					else if (b.board[x][y] == 3.1) {
						Generate_BishopCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 5) {
						Generate_RookCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 9) {
						Generate_QueenCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 100) {
						Generate_KingCaptures(b, moves, x, y);
					}
				}
			}
		}

		else {

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {

					if (b.board[x][y] == 0) {
						continue;
					}

					else if (b.board[x][y] == -1) {
						Generate_PawnCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -3) {
						Generate_HorseCaptures(b, moves, x, y);

					}

					else if (b.board[x][y] == -3.1) {
						Generate_BishopCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -5) {
						Generate_RookCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -9) {
						Generate_QueenCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -100) {
						Generate_KingCaptures(b, moves, x, y);
					}
				}
			}
		}
	}
}



void MakeMove(Board& b, Move& move) {

	// Eval
	b.eval -= move.capture;

	// Board
	b.board[move.toX][move.toY] = b.board[move.fromX][move.fromY];
	b.board[move.fromX][move.fromY] = 0;
}

void UndoMove(Board& b, Move& move) {

	// Eval
	b.eval += move.capture;

	// Board
	b.board[move.fromX][move.fromY] = b.board[move.toX][move.toY];
	b.board[move.toX][move.toY] = move.capture;
}
