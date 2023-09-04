#include <vector>
#include "beta.h"
#include <iostream>
#include <chrono>

using namespace std;



void Board::Initialize() {

	// Eval & En Passant
	this->eval = 0;
	this->enPassant = { -1, 0 };

	//pieceIndex = 0;



	// Space
	for (int x = 0; x < 8; x++) {
		for (int y = 2; y < 6; y++) {
			this->board[x][y] = 0;
		}
	}

	// Pawn
	for (int x = 0; x < 8; x++) {
		this->board[x][1] = 1000;
		this->board[x][6] = -1000;
	}

	// Horse
	this->board[1][0] = 3000;
	this->board[6][0] = 3000;

	this->board[1][7] = -3000;
	this->board[6][7] = -3000;


	// Bishop
	this->board[2][0] = 3100;
	this->board[5][0] = 3100;

	this->board[2][7] = -3100;
	this->board[5][7] = -3100;


	// Rook
	this->board[0][0] = 5000;
	this->board[7][0] = 5000;

	this->board[0][7] = -5000;
	this->board[7][7] = -5000;


	// Queen
	this->board[3][0] = 9000;

	this->board[3][7] = -9000;


	// King
	this->board[4][0] = 100000;

	this->board[4][7] = -100000;
}



void GenerateMoves(Board& b, vector<Move>& moves, bool player, bool onlyCapture) {

	//chrono::time_point<chrono::high_resolution_clock> timeStart = chrono::high_resolution_clock::now();

	if (!onlyCapture) {

		if (player) {

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {

					if (b.board[x][y] == 0) {
						continue;
					}

					else if (b.board[x][y] == 1000) {
						Generate_PawnMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 3000) {
						Generate_HorseMoves(b, moves, x, y);

					}

					else if (b.board[x][y] == 3100) {
						Generate_BishopMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 5000) {
						Generate_RookMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 9000) {
						Generate_QueenMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == 100000) {
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

					else if (b.board[x][y] == -1000) {
						Generate_PawnMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -3000) {
						Generate_HorseMoves(b, moves, x, y);

					}

					else if (b.board[x][y] == -3100) {
						Generate_BishopMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -5000) {
						Generate_RookMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -9000) {
						Generate_QueenMoves(b, moves, x, y);
					}

					else if (b.board[x][y] == -100000) {
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

					else if (b.board[x][y] == 1000) {
						Generate_PawnCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 3000) {
						Generate_HorseCaptures(b, moves, x, y);

					}

					else if (b.board[x][y] == 3100) {
						Generate_BishopCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 5000) {
						Generate_RookCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 9000) {
						Generate_QueenCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == 100000) {
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

					else if (b.board[x][y] == -1000) {
						Generate_PawnCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -3000) {
						Generate_HorseCaptures(b, moves, x, y);

					}

					else if (b.board[x][y] == -3100) {
						Generate_BishopCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -5000) {
						Generate_RookCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -9000) {
						Generate_QueenCaptures(b, moves, x, y);
					}

					else if (b.board[x][y] == -100000) {
						Generate_KingCaptures(b, moves, x, y);
					}
				}
			}
		}
	}
	//chrono::time_point<chrono::high_resolution_clock> timeStop = chrono::high_resolution_clock::now();
	//chrono::duration<double> time = timeStop - timeStart;

	//cout << time.count() << "\n";
}



void MakeMove(Board& b, Move& move) {

	// Eval
	b.eval -= move.capture;

	/*// En Passant
	if (abs(b.board[move.fromX][move.fromY]) == 1000 && abs(move.toY - move.fromY) == 2) {
		b.enPassant = {move.toX, move.toY};
	}
	else {
		b.enPassant = { -1, 0 };
	}

	if (move.enPassant) {
		b.board[move.toX][move.toY] = b.board[move.fromX][move.fromY];
		b.board[move.fromX][move.fromY] = 0;
		b.board[move.toX][move.fromY] = 0;
	}*/


	// Promotion
	if (move.promotion) {
		b.board[move.toX][move.toY] = -move.capture;
		b.board[move.fromX][move.fromY] = 0;
	}

	// Castle
	else if (move.castle) {

		if (move.castle == 1) {
			b.board[4][0] = 0;
			b.board[5][0] = 5000;
			b.board[6][0] = 100000;
			b.board[7][0] = 0;

			b.eval += 1;
		}

		else if (move.castle == 2) {
			b.board[4][0] = 0;
			b.board[3][0] = 5000;
			b.board[2][0] = 100000;
			b.board[0][0] = 0;

			b.eval += 1;
		}

		else if (move.castle == 3) {
			b.board[4][7] = 0;
			b.board[5][7] = -5000;
			b.board[6][7] = -100000;
			b.board[7][7] = 0;

			b.eval -= 1;
		}

		else {
			b.board[4][7] = 0;
			b.board[3][7] = -5000;
			b.board[2][7] = -100000;
			b.board[0][7] = 0;

			b.eval -= 1;
		}
	}


	// ~ ~
	else {

		/*// Fix Castle
		if (abs(b.board[move.fromX][move.fromY]) == 100000) {
			if (b.board[move.fromX][move.fromY] > 0) {
				b.b
			}
		}*/

		b.board[move.toX][move.toY] = b.board[move.fromX][move.fromY];
		b.board[move.fromX][move.fromY] = 0;
	}
}

void UndoMove(Board& b, Move& move) {

	// Eval
	b.eval += move.capture;


	/*// En Passant
	if (move.enPassant) {
		b.board[move.fromX][move.fromY] = b.board[move.toX][move.toY];
		b.board[move.toX][move.toY] = 0;
		b.board[move.toX][move.fromY] = -move.enPassant;
	}*/


	// Promotion
	if (move.promotion) {
		b.board[move.fromX][move.fromY] = move.promotion;
		b.board[move.toX][move.toY] = 0;
	}

	// Castle
	else if (move.castle) {

		if (move.castle == 1) {
			b.board[4][0] = 100000;
			b.board[5][0] = 0;
			b.board[6][0] = 0;
			b.board[7][0] = 5000;

			b.eval -= 1;
		}

		else if (move.castle == 2) {
			b.board[4][0] = 100000;
			b.board[3][0] = 0;
			b.board[2][0] = 0;
			b.board[0][0] = 5000;

			b.eval -= 1;
		}

		else if (move.castle == 3) {
			b.board[4][7] = -100000;
			b.board[5][7] = 0;
			b.board[6][7] = 0;
			b.board[7][7] = -5000;

			b.eval += 1;
		}

		else {
			b.board[4][7] = -100000;
			b.board[3][7] = 0;
			b.board[2][7] = 0;
			b.board[0][7] = -5000;

			b.eval += 1;
		}
	}

	// ~ ~
	else {
		b.board[move.fromX][move.fromY] = b.board[move.toX][move.toY];
		b.board[move.toX][move.toY] = move.capture;
	}
}