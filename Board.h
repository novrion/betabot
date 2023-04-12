#pragma once

#include <utility>
#include <vector>



struct Piece {

	Piece()
	{
		this->Color = 0;
		this->Type = 0;
	}

	Piece(int color, std::pair<int, int> position, float type)
	{
		this->Color = color;
		this->piecePosition = position;
		this->Type = type;
	}

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pieceLegalMoves;
	std::pair<int, int> piecePosition;
	int Color;
	float Type;

	void Generate_PawnLegalMoves(Piece boardPos[8][8]);
	void Generate_HorseLegalMoves(Piece boardPos[8][8]);
	void Generate_BishopLegalMoves(Piece boardPos[8][8]);
	void Generate_RookLegalMoves(Piece boardPos[8][8]);
	void Generate_QueenLegalMoves(Piece boardPos[8][8]);
	void Generate_KingLegalMoves(Piece boardPos[8][8]);
};

class Board {

	public : 

		Board()
		{
			this->eval = 0;
		}

		static bool isExit;

		bool isWhitePlayer;
		int depth;
		float eval;

		std::pair<std::pair<int, int>, std::pair<int, int>> nextMove;
		static std::pair<std::pair<int, int>, std::pair<int, int>> bestMove;


		Piece boardPos[8][8];

			
		void InitializeBoard();
		void GetAllLegalMoves(bool isWhitePlayer);

		void EvalMove(std::pair<int, int> from, std::pair<int, int> to);
		void MakeMove(std::pair<int, int> from, std::pair<int, int> to);


		/* Other stuff for main */
		void InputAndMakeNextMove();
};

float Minimax(Board b, int depth, bool whitePlayer);