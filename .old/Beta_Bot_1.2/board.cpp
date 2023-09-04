#include <iostream>
#include <vector>

#include "Board.h"

using namespace std;



void Board::MakeMove(Move move) {

	pair<int, int> from = move.from;
	pair<int, int> to = move.to;

	Piece pieceFrom = this->boardPos[from.first][from.second];
	pieceFrom.piecePosition = { to.first, to.second };



	// Set Up & Clear En Passant
	this->previousEnPassant = canEnPassant;
	this->canEnPassant = { -1, 0 };

	if ((pieceFrom.Type == 1 || pieceFrom.Type == -1) && (to.second == from.second + 2 || to.second == from.second - 2)) {
		this->canEnPassant = to;
	}



	// En Passant ~ ~
	if (move.isEnPassant) {

		this->boardPos[to.first][to.second] = pieceFrom;
		this->boardPos[from.first][from.second] = Piece(0, { from.first, from.second }, 0);

		if (to.second > from.second) {

			this->boardPos[to.first][to.second - 1] = Piece(0, { from.first, from.second }, 0);
			this->eval += 1;
		}

		else {

			this->boardPos[to.first][to.second + 1] = Piece(0, { from.first, from.second }, 0);
			this->eval -= 1;
		}
	}

	// Castle ~ ~
	else if (move.isCastle) {

	}

	// Promotion ~ ~
	else if (move.promotion != 0) {

		this->boardPos[from.first][from.second] = Piece(0, { from.first, from.second }, 0);


		if (move.promotion > 0) {

			this->boardPos[to.first][to.second] = Piece(1, { to.first, to.second }, move.promotion);
			this->eval += move.promotion - 1;
		}

		else {

			this->boardPos[to.first][to.second] = Piece(-1, { to.first, to.second }, move.promotion);
			this->eval += move.promotion + 1;
		}
	}

	// ~ ~
	else {
		this->eval -= this->boardPos[to.first][to.second].Type;

		this->boardPos[to.first][to.second] = pieceFrom;
		this->boardPos[from.first][from.second] = Piece(0, { from.first, from.second }, 0);
	}
}





void Board::UndoMove(Move move) {

	pair<int, int> from = move.from;
	pair<int, int> to = move.to;

	Piece pieceTo = this->boardPos[to.first][to.second];
	pieceTo.piecePosition = { from.first, from.second };

	// Reverse En Passant Coordinates
	this->canEnPassant = previousEnPassant;



	// Capture ~ ~
	if (move.isCapture != 0) {

		this->boardPos[from.first][from.second] = pieceTo;

		if (move.isCapture > 0) {
			this->boardPos[to.first][to.second] = Piece(1, { to.first, to.second }, move.isCapture);
		}
		else {
			this->boardPos[to.first][to.second] = Piece(-1, { to.first, to.second }, move.isCapture);
		}

		this->eval += move.isCapture;
	}

	// En Passant ~ ~
	else if (move.isEnPassant) {

		this->boardPos[from.first][from.second] = pieceTo;
		this->boardPos[to.first][to.second] = Piece(0, { to.first, to.second }, 0);

		if (move.isCapture == -1) {
			boardPos[to.first][to.second - 1] = Piece(-1, { to.first, to.second - 1 }, -1);
		}
		else {
			boardPos[to.first][to.second + 1] = Piece(1, { to.first, to.second + 1 }, 1);
		}

		this->eval += move.isCapture;
	}

	// Castle ~ ~
	else if (move.isCastle) {

	}

	// Promotion ~ ~
	else if (move.promotion != 0) {

		this->boardPos[to.first][to.second] = Piece(0, { to.first, to.second }, 0);

		if (move.promotion > 0) {

			this->boardPos[from.first][from.second] = Piece(1, { from.first, from.second }, 1);
			this->eval -= (move.promotion - 1);
		}

		else {

			this->boardPos[from.first][from.second] = Piece(1, { from.first, from.second }, 1);
			this->eval -= (move.promotion + 1);
		}
	}

	// ~ ~
	else {

		this->boardPos[from.first][from.second] = pieceTo;
		this->boardPos[to.first][to.second] = Piece(0, { to.first, to.second }, 0);
	}
}










vector<Move> Board::GenerateMoves(bool isWhitePlayer) {

	vector<Move> moves;


	if (isWhitePlayer) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				if (this->boardPos[i][j].Type == 0) {
					continue;
				}

				else if (this->boardPos[i][j].Type == 1) {
					this->boardPos[i][j].Generate_Pawn_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_PawnCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 3) {
					this->boardPos[i][j].Generate_Horse_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_HorseCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 3.1) {
					this->boardPos[i][j].Generate_Bishop_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_BishopCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 5) {
					this->boardPos[i][j].Generate_Rook_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_RookCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 9) {
					this->boardPos[i][j].Generate_Queen_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_QueenCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 55555) {
					this->boardPos[i][j].Generate_King_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_KingCaptures(this, moves);
				}
			}
		}
	}

	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				if (this->boardPos[i][j].Type == 0) {
					continue;
				}

				else if (this->boardPos[i][j].Type == -1) {
					this->boardPos[i][j].Generate_Pawn_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_PawnCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -3) {
					this->boardPos[i][j].Generate_Horse_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_HorseCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -3.1) {
					this->boardPos[i][j].Generate_Bishop_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_BishopCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -5) {
					this->boardPos[i][j].Generate_Rook_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_RookCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -9) {
					this->boardPos[i][j].Generate_Queen_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_QueenCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -55555) {
					this->boardPos[i][j].Generate_King_Non_Captures(this, moves);
					this->boardPos[i][j].Generate_KingCaptures(this, moves);
				}
			}
		}
	}

	return moves;
}





vector<Move> Board::GenerateCaptures(bool isWhitePlayer) {

	vector<Move> moves;


	if (isWhitePlayer) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				if (this->boardPos[i][j].Type == 0) {
					continue;
				}

				else if (this->boardPos[i][j].Type == 1) {
					this->boardPos[i][j].Generate_PawnCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 3) {
					this->boardPos[i][j].Generate_HorseCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 3.1) {
					this->boardPos[i][j].Generate_BishopCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 5) {
					this->boardPos[i][j].Generate_RookCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 9) {
					this->boardPos[i][j].Generate_QueenCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == 55555) {
					this->boardPos[i][j].Generate_KingCaptures(this, moves);
				}
			}
		}
	}

	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				if (this->boardPos[i][j].Type == 0) {
					continue;
				}

				else if (this->boardPos[i][j].Type == -1) {
					this->boardPos[i][j].Generate_PawnCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -3) {
					this->boardPos[i][j].Generate_HorseCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -3.1) {
					this->boardPos[i][j].Generate_BishopCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -5) {
					this->boardPos[i][j].Generate_RookCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -9) {
					this->boardPos[i][j].Generate_QueenCaptures(this, moves);
				}

				else if (this->boardPos[i][j].Type == -55555) {
					this->boardPos[i][j].Generate_KingCaptures(this, moves);
				}
			}
		}
	}

	return moves;
}






void Board::Initialize() {

	// Input color
	this->isWhitePlayer = InputColor();

	// Input depth
	cout << endl << "Depth: ";
	cin >> this->depth;


	// Space
	for (int i = 0; i < 8; i++) {
		this->boardPos[i][2] = Piece(0, { i, 2 }, 0);
		this->boardPos[i][3] = Piece(0, { i, 3 }, 0);
		this->boardPos[i][4] = Piece(0, { i, 4 }, 0);
		this->boardPos[i][5] = Piece(0, { i, 5 }, 0);
	}



	// Pawns
	for (int i = 0; i < 8; i++) {
		this->boardPos[i][1] = Piece(1, { i, 1 }, 1);
	}

	for (int i = 0; i < 8; i++) {
		this->boardPos[i][6] = Piece(-1, { i, 6 }, -1);
	}

	// Horses
	this->boardPos[1][0] = Piece(1, { 1, 0 }, 3);
	this->boardPos[6][0] = Piece(1, { 6, 0 }, 3);

	this->boardPos[1][7] = Piece(-1, { 1, 7 }, -3);
	this->boardPos[6][7] = Piece(-1, { 6, 7 }, -3);

	// Bishops
	this->boardPos[2][0] = Piece(1, { 2, 0 }, 3.1);
	this->boardPos[5][0] = Piece(1, { 5, 0 }, 3.1);

	this->boardPos[2][7] = Piece(-1, { 2, 7 }, -3.1);
	this->boardPos[5][7] = Piece(-1, { 5, 7 }, -3.1);

	// Rooks
	this->boardPos[0][0] = Piece(1, { 0, 0 }, 5);
	this->boardPos[7][0] = Piece(1, { 7, 0 }, 5);

	this->boardPos[0][7] = Piece(-1, { 0, 7 }, -5);
	this->boardPos[7][7] = Piece(-1, { 7, 7 }, -5);

	// Queens
	this->boardPos[3][0] = Piece(1, { 3, 0 }, 9);

	this->boardPos[3][7] = Piece(-1, { 3, 7 }, -9);

	// Kings
	this->boardPos[4][0] = Piece(1, { 4, 0 }, 55555);

	this->boardPos[4][7] = Piece(-1, { 4, 7 }, -55555);

	cout << "Board Initialized" << endl << "----------------------------------------" << endl << endl;
}