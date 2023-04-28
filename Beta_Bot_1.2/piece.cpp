#include "Board.h"

#include <vector>
#include <utility>

using namespace std;



// Add: Castling, Promotion, En Passant



// Non Captures ~ ~
void Piece::Generate_Pawn_Non_Captures(Board* b, vector<Move>& moves) {

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (color == 1) {

		// Y + 2
		if (Y == 1 && b->boardPos[X][Y + 1].Type == 0 && b->boardPos[X][Y + 2].Type == 0) {
			moves.push_back(Move({X, Y}, {X, Y + 2}));
		}

		// Y + 1
		if (Y + 1 < 8 && b->boardPos[X][Y + 1].Type == 0) {

			if (Y + 1 == 7) {
				moves.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 3, false, false));
				moves.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 3.1, false, false));
				moves.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 5, false, false));
				moves.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 9, false, false));
			}

			else {
				moves.push_back(Move({ X, Y }, { X, Y + 1 }));
			}
		}
	}

	else {

		// Y - 2
		if (Y == 6 && b->boardPos[X][Y - 1].Type == 0 && b->boardPos[X][Y - 2].Type == 0) {
			moves.push_back(Move({X, Y}, {X, Y - 2}));
		}

		// Y - 1
		if (-1 < Y - 1 && b->boardPos[X][Y - 1].Type == 0) {

			if (Y - 1 == 0) {
				moves.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -3, false, false));
				moves.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -3.1, false, false));
				moves.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -5, false, false));
				moves.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -9, false, false));
			}

			else {
				moves.push_back(Move({ X, Y }, { X, Y - 1 }));
			}
		}
	}
};


void Piece::Generate_Horse_Non_Captures(Board* b, vector<Move>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (X + 1 < 8 && Y + 2 < 8 && b->boardPos[X + 1][Y + 2].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 1, Y + 2}));
	}

	if (-1 < X - 1 && Y + 2 < 8 && b->boardPos[X - 1][Y + 2].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 1, Y + 2}));
	}

	if (X + 2 < 8 && Y + 1 < 8 && b->boardPos[X + 2][Y + 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 2, Y + 1}));
	}

	if (-1 < X - 2 && Y + 1 < 8 && b->boardPos[X - 2][Y + 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 2, Y + 1}));
	}

	if (X + 2 < 8 && -1 < Y - 1 && b->boardPos[X + 2][Y - 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 2, Y - 1}));
	}

	if (-1 < X - 2 && -1 < Y - 1 && b->boardPos[X - 2][Y - 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 2, Y - 1}));
	}

	if (X + 1 < 8 && -1 < Y - 2 && b->boardPos[X + 1][Y - 2].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 1, Y - 2}));
	}

	if (-1 < X - 1 && -1 < Y - 2 && b->boardPos[X - 1][Y - 2].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 1, Y - 2}));
	}
};


void Piece::Generate_Bishop_Non_Captures(Board* b, vector<Move>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}
};


void Piece::Generate_Rook_Non_Captures(Board* b, vector<Move>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y + 1; y < 8; y++) {

		if (b->boardPos[X][y].Color == 0) {
			moves.push_back(Move({X, Y}, {X, y}));
		}
		else { break; }
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == 0) {
			moves.push_back(Move({X, Y}, {X, y}));
		}
		else { break; }
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, Y}));
		}
		else { break; }
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, Y}));
		}
		else { break; }
	}
};


void Piece::Generate_Queen_Non_Captures(Board* b, vector<Move>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y + 1; y < 8; y++) {

		if (b->boardPos[X][y].Color == 0) {
			moves.push_back(Move({X, Y}, {X, y}));
		}
		else { break; }
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == 0) {
			moves.push_back(Move({X, Y}, {X, y}));
		}
		else { break; }
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, Y}));
		}
		else { break; }
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, Y}));
		}
		else { break; }
	}





	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.push_back(Move({X, Y}, {x, y}));
		}
		else { break; }
	}
};


void Piece::Generate_King_Non_Captures(Board* b, vector<Move>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	if (Y + 1 < 8 && b->boardPos[X][Y + 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X, Y + 1}));
	}

	// DOWN
	if (Y - 1 > -1 && b->boardPos[X][Y - 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X, Y - 1}));
	}

	// RIGHT
	if (X + 1 < 8 && b->boardPos[X + 1][Y].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 1, Y}));
	}

	// LEFT
	if (X - 1 > -1 && b->boardPos[X - 1][Y].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 1, Y}));
	}





	// UP RIGHT
	if (X + 1 < 8 && Y + 1 < 8 && b->boardPos[X + 1][Y + 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 1, Y + 1}));
	}

	// UP LEFT
	if (X - 1 > -1 && Y + 1 < 8 && b->boardPos[X - 1][Y + 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 1, Y + 1}));
	}

	// DOWN RIGHT
	if (X + 1 < 8 && Y - 1 > -1 && b->boardPos[X + 1][Y - 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X + 1, Y - 1}));
	}

	// DOWN LEFT
	if (X - 1 > -1 && Y - 1 > -1 && b->boardPos[X - 1][Y - 1].Color == 0) {
		moves.push_back(Move({X, Y}, {X - 1, Y - 1}));
	}
};










// Captures ~ ~
void Piece::Generate_PawnCaptures(Board* b, vector<Move>& moves) {

	int color = this->Color;
	int otherColor = color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (color == 1) {

		// En Passant
		/*if (b->canEnPassant.first != -1 && X == 5) {

			if (X + 1 < 8 && b->canEnPassant.first == X + 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X + 1, Y + 1}, -1, 0, true ,false));

			}

			else if (-1 < X - 1 && b->canEnPassant.first == X - 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X - 1, Y + 1}, -1, 0, true, false));
			}
		}*/



		// Take Right
		if (X + 1 < 8 && Y + 1 < 8 && b->boardPos[X + 1][Y + 1].Color == otherColor) {
			moves.push_back(Move({X, Y}, {X + 1, Y + 1}, b->boardPos[X + 1][Y + 1].Type));
		}

		// Take Left
		if (-1 < X - 1 && Y + 1 < 8 && b->boardPos[X - 1][Y + 1].Color == otherColor) {
			moves.push_back(Move({X, Y}, {X - 1, Y + 1}, b->boardPos[X - 1][Y + 1].Type));
		}
	}

	else {

		// En Passant
		/*if (b->canEnPassant.first != -1 && X == 2) {

			if (X + 1 < 8 && b->canEnPassant.first == X + 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X + 1, Y - 1}, 1, 0, true, false));

			}

			else if (-1 < X - 1 && b->canEnPassant.first == X - 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X - 1, Y - 1}, 1, 0, true, false));
			}
		}*/



		// Take Right
		if (-1 < X - 1 && -1 < Y - 1 && b->boardPos[X - 1][Y - 1].Color == otherColor) {
			moves.push_back(Move({X, Y}, {X - 1, Y - 1}, b->boardPos[X - 1][Y - 1].Type));
		}

		// Take Left
		if (X + 1 < 8 && -1 < Y - 1 && b->boardPos[X + 1][Y - 1].Color == otherColor) {
			moves.push_back(Move({X, Y}, {X + 1, Y - 1}, b->boardPos[X + 1][Y - 1].Type));
		}
	}
};


void Piece::Generate_HorseCaptures(Board* b, vector<Move>& moves) {

	int otherColor = this->Color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (X + 1 < 8 && Y + 2 < 8 && b->boardPos[X + 1][Y + 2].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 1, Y + 2}, b->boardPos[X + 1][Y + 2].Type));
	}

	if (-1 < X - 1 && Y + 2 < 8 && b->boardPos[X - 1][Y + 2].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 1, Y + 2}, b->boardPos[X - 1][Y + 2].Type));
	}

	if (X + 2 < 8 && Y + 1 < 8 && b->boardPos[X + 2][Y + 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 2, Y + 1}, b->boardPos[X + 2][Y + 1].Type));
	}

	if (-1 < X - 2 && Y + 1 < 8 && b->boardPos[X - 2][Y + 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 2, Y + 1}, b->boardPos[X - 2][Y + 1].Type));
	}

	if (X + 2 < 8 && -1 < Y - 1 && b->boardPos[X + 2][Y - 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 2, Y - 1}, b->boardPos[X + 2][Y - 1].Type));
	}

	if (-1 < X - 2 && -1 < Y - 1 && b->boardPos[X - 2][Y - 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 2, Y - 1}, b->boardPos[X - 2][Y - 1].Type));
	}

	if (X + 1 < 8 && -1 < Y - 2 && b->boardPos[X + 1][Y - 2].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 1, Y - 2}, b->boardPos[X + 1][Y - 2].Type));
	}

	if (-1 < X - 1 && -1 < Y - 2 && b->boardPos[X - 1][Y - 2].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 1, Y - 2}, b->boardPos[X - 1][Y - 2].Type));
	}
};


void Piece::Generate_BishopCaptures(Board* b, vector<Move>& moves) {

	int color = this->Color;
	int otherColor = color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			break;
		}
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			break;
		}
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			break;
		}
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			break;
		}
	}
};


void Piece::Generate_RookCaptures(Board* b, vector<Move>& moves) {

	int color = this->Color;
	int otherColor = color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y + 1; y < 8; y++) {

		if (b->boardPos[X][y].Color == color) {
			break;
		}

		if (b->boardPos[X][y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {X, y}, b->boardPos[X][y].Type));
			break;
		}
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == color) {
			break;
		}

		if (b->boardPos[X][y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {X, y}, b->boardPos[X][y].Type));
			break;
		}
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {x, Y}, b->boardPos[x][Y].Type));
			break;
		}
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.push_back(Move({X, Y}, {x, Y}, b->boardPos[x][Y].Type));
			break;
		}
	}
};


void Piece::Generate_QueenCaptures(Board* b, vector<Move>& moves) {

	int color = this->Color;
	int otherColor = color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y + 1; y < 8; y++) {

		if (b->boardPos[X][y].Color == color) {
			break;
		}

		if (b->boardPos[X][y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { X, y }, b->boardPos[X][y].Type));
			break;
		}
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == color) {
			break;
		}

		if (b->boardPos[X][y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { X, y }, b->boardPos[X][y].Type));
			break;
		}
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { x, Y }, b->boardPos[x][Y].Type));
			break;
		}
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { x, Y }, b->boardPos[x][Y].Type));
			break;
		}
	}





	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			break;
		}
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			break;
		}
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			break;
		}
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			break;
		}
	}
};


void Piece::Generate_KingCaptures(Board* b, vector<Move>& moves) {

	int otherColor = this->Color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	if (Y + 1 < 8 && b->boardPos[X][Y + 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X, Y + 1}, b->boardPos[X][Y + 1].Type));
	}

	// DOWN
	if (Y - 1 > -1 && b->boardPos[X][Y - 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X, Y - 1}, b->boardPos[X][Y - 1].Type));
	}

	// RIGHT
	if (X + 1 < 8 && b->boardPos[X + 1][Y].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 1, Y}, b->boardPos[X + 1][Y].Type));
	}

	// LEFT
	if (X - 1 > -1 && b->boardPos[X - 1][Y].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 1, Y}, b->boardPos[X - 1][Y].Type));
	}





	// UP RIGHT
	if (X + 1 < 8 && Y + 1 < 8 && b->boardPos[X + 1][Y + 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 1, Y + 1}, b->boardPos[X + 1][Y + 1].Type));
	}

	// UP LEFT
	if (X - 1 > -1 && Y + 1 < 8 && b->boardPos[X - 1][Y + 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 1, Y + 1}, b->boardPos[X - 1][Y + 1].Type));
	}

	// DOWN RIGHT
	if (X + 1 < 8 && Y - 1 > -1 && b->boardPos[X + 1][Y - 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X + 1, Y - 1}, b->boardPos[X + 1][Y - 1].Type));
	}

	// DOWN LEFT
	if (X - 1 > -1 && Y - 1 > -1 && b->boardPos[X - 1][Y - 1].Color == otherColor) {
		moves.push_back(Move({X, Y}, {X - 1, Y - 1}, b->boardPos[X - 1][Y - 1].Type));
	}
};
