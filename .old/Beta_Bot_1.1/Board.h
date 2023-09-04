#pragma once

#include <utility>
#include <vector>
#include <string>



struct Piece {

	Piece()
	{
		Color = 0;
		Type = 0;
	}

	Piece(int color, std::pair<int, int> position, double type)
	{
		Color = color;
		piecePosition = position;
		Type = type;
	}

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pieceLegalMoves;
	std::pair<int, int> piecePosition;
	int Color;
	double Type;

	void Generate_PawnLegalMoves(Piece boardPos[8][8]);
	void Generate_HorseLegalMoves(Piece boardPos[8][8]);
	void Generate_BishopLegalMoves(Piece boardPos[8][8]);
	void Generate_RookLegalMoves(Piece boardPos[8][8]);
	void Generate_QueenLegalMoves(Piece boardPos[8][8]);
	void Generate_KingLegalMoves(Piece boardPos[8][8]);
};

class Board {

public:

	Board()
	{
		eval = 0;
		depth = 5;
		isWhitePlayer = true;
	}

	static bool isExit;

	bool isWhitePlayer;
	int depth;
	double eval;

	std::pair<std::pair<int, int>, std::pair<int, int>> nextMove;
	static std::pair<std::pair<int, int>, std::pair<int, int>> bestMove;


	Piece boardPos[8][8];


	void InitializeBoard();
	bool InputPlayerColor();

	void GetAllLegalMoves(bool isWhitePlayer);

	void MakeMove(std::pair<int, int> from, std::pair<int, int> to);


	/* Other stuff for main */
	void InputAndMakeNextMove();
};

double Minimax(Board b, int depth, double alpha, double beta, bool whitePlayer);

std::pair<std::pair<int, int>, std::pair<int, int>> TranslateToPair(std::string notation);
std::string TranslateToNotation(std::pair<std::pair<int, int>, std::pair<int, int>> coordinates);

void PrintBoard(Piece boardPos[8][8]);