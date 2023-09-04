#pragma once

#include <vector>
#include <string>
#include <iostream>


struct Move {

	Move() {

		fromX = -1;
		fromY = 0;
		toX = 0;
		toY = 0;

		capture = 0;
		promotion = 0;
		enPassant = 0;
		castle = 0;

		eval = 0;
	}

	Move(int f_X, int f_Y, int t_X, int t_Y, int _capture) {

		fromX = f_X;
		fromY = f_Y;
		toX = t_X;
		toY = t_Y;

		capture = _capture;
		promotion = 0;
		enPassant = 0;
		castle = 0;

		eval = 0;
	}

	Move(int f_X, int f_Y, int t_X, int t_Y, int _capture, int _promotion, int _enPassant, int _castle) {

		fromX = f_X;
		fromY = f_Y;
		toX = t_X;
		toY = t_Y;

		capture = _capture;
		promotion = _promotion;
		enPassant = _enPassant;
		castle = _castle;

		eval = 0;
	}

	int fromX, fromY, toX, toY;
	int capture;
	int promotion;
	int enPassant;
	int castle;

	int eval;
};

struct Board {

	Board() {

		eval = 0;

		// Same error as with l_capturePiece... won't work!!
		enPassant = { -1, 0 };
		// -------------------------------------------------

		w_castleShort = true;
		w_castleLong = true;
		b_castleShort = true;
		b_castleLong = true;

		w_castle = 0;
		b_castle = 0;
	}

	int eval;
	std::pair<int, int> enPassant;

	bool w_castleShort;
	bool w_castleLong;
	bool b_castleShort;
	bool b_castleLong;

	int w_castle;
	int b_castle;


	Move n_move;
	int board[8][8];


	void Initialize();
};


// Logic ~ ~
void MakeMove(Board& b, Move& move);
void UndoMove(Board& b, Move& move);

void GenerateMoves(Board& b, std::vector<Move>& moves, bool player, bool onlyCapture);

void Generate_PawnMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_HorseMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_BishopMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_RookMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_QueenMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_KingMoves(Board& b, std::vector<Move>& moves, int posX, int posY);

int Minimax(Board& b, int depth, bool color);