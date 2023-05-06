#pragma once

#include <vector>
#include <string>


struct Move {

	Move() {
		fromX = -1;
		fromY = 0;
		toX = 0;
		toY = 0;

		capture = 0;
	}

	Move(int f_X, int f_Y, int t_X, int t_Y, double _capture) {

		fromX = f_X;
		fromY = f_Y;
		toX = t_X;
		toY = t_Y;

		capture = _capture;
	}

	Move(int f_X, int f_Y, int t_X, int t_Y, double board[8][8]) {

		fromX = f_X;
		fromY = f_Y;
		toX = t_X;
		toY = t_Y;

		capture = board[t_X][t_Y];
	}

	int fromX, fromY, toX, toY;
	double capture;
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
	}

	double eval;
	std::pair<int, int> enPassant;

	bool w_castleShort;
	bool w_castleLong;
	bool b_castleShort;
	bool b_castleLong;


	Move n_move;
	double board[8][8];


	void Initialize();
};


// Logic ~ ~
void MakeMove(Board& b, Move& move);
void UndoMove(Board& b, Move& move);

std::string TranslateToNotation(Move& move);

// Input ~ ~
bool InputColor();
int InputDepth();
void Main_MakeMove(Board& b);


// Output ~ ~
void PrintBoard(double board[8][8]);
void PrintMain(double board[8][8], double eval, Move& move);



void GenerateMoves(Board& b, std::vector<Move>& moves, bool player, bool onlyCapture);

void Generate_PawnMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_HorseMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_BishopMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_RookMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_QueenMoves(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_KingMoves(Board& b, std::vector<Move>& moves, int posX, int posY);

void Generate_PawnCaptures(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_HorseCaptures(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_BishopCaptures(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_RookCaptures(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_QueenCaptures(Board& b, std::vector<Move>& moves, int posX, int posY);
void Generate_KingCaptures(Board& b, std::vector<Move>& moves, int posX, int posY);



double firstLayerMinimax(Board& b, int depth, double alpha, double beta, bool color);
double Minimax(Board& b, int depth, double alpha, double beta, bool color);
double Quiescence(Board& b, int depth, double alpha, double beta, bool color);
