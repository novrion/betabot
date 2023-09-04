#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "Board.h"

using namespace std;



void Board::MakeMove(pair<int, int> from, pair<int, int> to) {

	Piece pieceFrom = this->boardPos[from.first][from.second];
	int colorTo = this->boardPos[to.first][to.second].Color;

	this->eval -= this->boardPos[to.first][to.second].Type;

	// Change secondary property to make it easier for other functions... Might refactor, is sorta unnecessary ??
	pieceFrom.piecePosition = { to.first, to.second };

	this->boardPos[to.first][to.second] = pieceFrom;
	this->boardPos[from.first][from.second] = Piece(0, { from.first, from.second }, 0);
}





void Board::GetAllLegalMoves(bool isWhitePlayer) {

	if (isWhitePlayer) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				this->boardPos[i][j].pieceLegalMoves.clear();


				if (this->boardPos[i][j].Type == 0) {
					continue;
				}

				else if (this->boardPos[i][j].Type == 1) {
					this->boardPos[i][j].Generate_PawnLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == 3) {
					this->boardPos[i][j].Generate_HorseLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == 3.1) {
					this->boardPos[i][j].Generate_BishopLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == 5) {
					this->boardPos[i][j].Generate_RookLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == 9) {
					this->boardPos[i][j].Generate_QueenLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == 55555) {
					this->boardPos[i][j].Generate_KingLegalMoves(this->boardPos);
				}
			}
		}
	}

	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				this->boardPos[i][j].pieceLegalMoves.clear();


				if (this->boardPos[i][j].Type == 0) {
					continue;
				}

				else if (this->boardPos[i][j].Type == -1) {
					this->boardPos[i][j].Generate_PawnLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == -3) {
					this->boardPos[i][j].Generate_HorseLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == -3.1) {
					this->boardPos[i][j].Generate_BishopLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == -5) {
					this->boardPos[i][j].Generate_RookLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == -9) {
					this->boardPos[i][j].Generate_QueenLegalMoves(this->boardPos);
				}

				else if (this->boardPos[i][j].Type == -55555) {
					this->boardPos[i][j].Generate_KingLegalMoves(this->boardPos);
				}
			}
		}
	}
}





void Board::InitializeBoard() {

	// Input color
	this->isWhitePlayer = InputPlayerColor();

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