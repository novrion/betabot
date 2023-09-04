#pragma once

#include <vector>
#include <string>

struct Board;
struct Piece;
struct Move;





struct Piece {

	Piece()
	{
		Color = 0;
		piecePosition = { 0, 0 };
		Type = 0;
		isMoved = false;
	}

	Piece(int color, std::pair<int, int> position, double type)
	{
		Color = color;
		piecePosition = position;
		Type = type;
		isMoved = false;
	}

	std::pair<int, int> piecePosition;
	int Color;
	double Type;
	bool isMoved;

	// Generate Moves
	void Generate_Pawn_Non_Captures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_Horse_Non_Captures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_Bishop_Non_Captures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_Rook_Non_Captures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_Queen_Non_Captures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_King_Non_Captures(Board* b, std::pair<int, std::vector<Move>>& moves);

	// Generate Captures
	void Generate_PawnCaptures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_HorseCaptures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_BishopCaptures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_RookCaptures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_QueenCaptures(Board* b, std::pair<int, std::vector<Move>>& moves);
	void Generate_KingCaptures(Board* b, std::pair<int, std::vector<Move>>& moves);
};



struct Move {

	Move() {

		// Maybe not -1 because of bugs?
		from = { -1, 0 };
		to = { 0, 0 };
	}

	Move(std::pair<int, int> from_, std::pair<int, int> to_) {

		from = from_;
		to = to_;

		isCapture = 0;
		promotion = 0;
		isEnPassant = false;
		isCastle = 0;
	}

	Move(std::pair<int, int> from_, std::pair<int, int> to_, double isCapture_) {

		from = from_;
		to = to_;

		isCapture = isCapture_;

		promotion = 0;
		isEnPassant = false;
		isCastle = 0;
	}

	Move(std::pair<int, int> from_, std::pair<int, int> to_, double isCapture_, double promotion_, bool isEnPassant_, int isCastle_) {

		from = from_;
		to = to_;

		isCapture = isCapture_;
		promotion = promotion_;
		isEnPassant = isEnPassant_;
		isCastle = isCastle_;
	}

	std::pair<int, int> from;
	std::pair<int, int> to;

	double isCapture;
	double promotion;
	bool isEnPassant;

	// 1 = short W, 2 = long W, 3 = short B, 4 = long B
	int isCastle;
};



struct Board {

	Board()
	{
		eval = 0;
		depth = 4;
		isWhitePlayer = true;
		canEnPassant = { -1, 0 };
	}

	static bool isExit;
	bool isWhitePlayer;
	int depth;
	double eval;
	double mobility;



	std::pair<int, int> previousEnPassant;
	std::pair<int, int> canEnPassant;

	Piece boardPos[8][8];


	void Initialize();
	bool InputColor();

	std::pair<int, std::vector<Move>> GenerateMoves(bool isWhitePlayer);
	std::pair<int, std::vector<Move>> GenerateCaptures(bool isWhitePlayer);

	void MakeMove(Move move);
	void UndoMove(Move previousMove);


	/* Other stuff for main */
	void Main_MakeMove();
};



// Other stuff
std::pair<double, std::vector<Move>> Minimax(Board& b, int depth, double alpha, double beta, bool whitePlayer);

void ConvertToMove(Board* b, Move& move);

Move TranslateToPair(std::string notation);
std::string TranslateToNotation(Move move);

void PrintMain(Piece boardPos[8][8], std::pair<double, std::vector<Move>> minimaxData);