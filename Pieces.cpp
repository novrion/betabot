#include <vector>
#include <utility>

#include "Board.h"

using namespace std;



void Piece::Generate_PawnLegalMoves(Piece boardPos[8][8]) {

	this->pieceLegalMoves.clear();

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (color == 1) {

		// Y + 2
		if (Y == 1 && boardPos[X][Y + 1].Type == 0 && boardPos[X][Y + 2].Type == 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, Y + 2} });
		};

		// Y + 1
		if (Y+1 < 8 && boardPos[X][Y + 1].Type == 0) {
			this->pieceLegalMoves.push_back({{X, Y}, {X, Y+1}});
		};


		// Take Right
		if (X+1 < 8 && Y+1 < 8 && boardPos[X + 1][Y + 1].Color != color && boardPos[X + 1][Y + 1].Type != 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y+1} });
		};

		// Take Left
		if (-1 < X-1 && Y+1 < 8 && boardPos[X - 1][Y + 1].Color != color && boardPos[X - 1][Y + 1].Type != 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y+1} });
		};
	}

	else {

		// Y - 2
		if (Y == 6 && boardPos[X][Y - 1].Type == 0 && boardPos[X][Y - 2].Type == 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, Y-2} });
		};

		// Y - 1
		if (-1 < Y-1 && boardPos[X][Y - 1].Type == 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, Y-1} });
		};


		// Take Right
		if (-1 < X-1 && -1 < Y-1 && boardPos[X - 1][Y - 1].Color != color && boardPos[X - 1][Y - 1].Type != 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y-1} });
		};

		// Take Left
		if (X-1 < 8 && -1 < Y-1 && boardPos[X + 1][Y - 1].Color != color && boardPos[X + 1][Y - 1].Type != 0) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y-1} });
		};
	}
};


void Piece::Generate_HorseLegalMoves(Piece boardPos[8][8]) {

	this->pieceLegalMoves.clear();

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (X+1 < 8 && Y+2 < 8 && boardPos[X + 1][Y + 2].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y+2} });
	};

	if (-1 < X-1 && Y+2 < 8 && boardPos[X - 1][Y + 2].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y+2} });
	};

	if (X+2 < 8 && Y+1 < 8 && boardPos[X + 2][Y + 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+2, Y+1} });
	};

	if (-1 < X-2 && Y+1 < 8 && boardPos[X - 2][Y + 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-2, Y+1} });
	};

	if (X+2 < 8 && -1 < Y-1 && boardPos[X + 2][Y - 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+2, Y-1} });
	};

	if (-1 < X-2 && -1 < Y-1 && boardPos[X - 2][Y - 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-2, Y-1} });
	};

	if (X+1 < 8 && -1 < Y-2 && boardPos[X + 1][Y - 2].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y-2} });
	};

	if (-1 < X-1 && -1 < Y-2 && boardPos[X - 1][Y - 2].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y-2} });
	};
};


void Piece::Generate_BishopLegalMoves(Piece boardPos[8][8]) {

	this->pieceLegalMoves.clear();

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP RIGHT
	for (int x = X, y = Y; x < 8 && y < 8; x++, y++) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}

	// UP LEFT
	for (int x = X, y = Y; -1 < x && y < 8; x--, y++) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}

	// DOWN RIGHT
	for (int x = X, y = Y; x < 8 && -1 < y; x++, y--) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}

	// DOWN LEFT
	for (int x = X, y = Y; -1 < x && -1 < y; x--, y--) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}
};


void Piece::Generate_RookLegalMoves(Piece boardPos[8][8]) {

	this->pieceLegalMoves.clear();

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y; y < 8; y++) {
		if (boardPos[X][y].Color != 0 && boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
			break;
		}
		else if (boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
		}
		else { break; }
	}

	// DOWN
	for (int y = Y; -1 < y; y--) {

		if (boardPos[X][y].Color != 0 && boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
			break;
		}
		else if (boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
		}
		else { break; }
	}

	// RIGHT
	for (int x = X; x < 8; x++) {
		if (boardPos[x][Y].Color != 0 && boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
			break;
		}
		else if (boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
		}
		else { break;}
	}

	// LEFT
	for (int x = X; -1 < x; x--) {
		if (boardPos[x][Y].Color != 0 && boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
			break;
		}
		else if (boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
		}
		else { break; }
	}
};


void Piece::Generate_QueenLegalMoves(Piece boardPos[8][8]) {

	this->pieceLegalMoves.clear();

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y; y < 8; y++) {
		if (boardPos[X][y].Color != 0 && boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
			break;
		}
		else if (boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
		}
		else { break; }
	}

	// DOWN
	for (int y = Y; -1 < y; y--) {

		if (boardPos[X][y].Color != 0 && boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
			break;
		}
		else if (boardPos[X][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {X, y} });
		}
		else { break; }
	}

	// RIGHT
	for (int x = X; x < 8; x++) {
		if (boardPos[x][Y].Color != 0 && boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
			break;
		}
		else if (boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
		}
		else { break; }
	}

	// LEFT
	for (int x = X; -1 < x; x--) {
		if (boardPos[x][Y].Color != 0 && boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
			break;
		}
		else if (boardPos[x][Y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, Y} });
		}
		else { break; }
	}





	// UP RIGHT
	for (int x = X, y = Y; x < 8 && y < 8; x++, y++) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}

	// UP LEFT
	for (int x = X, y = Y; -1 < x && y < 8; x--, y++) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}

	// DOWN RIGHT
	for (int x = X, y = Y; x < 8 && -1 < y; x++, y--) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}

	// DOWN LEFT
	for (int x = X, y = Y; -1 < x && -1 < y; x--, y--) {

		if (boardPos[x][y].Color != 0 && boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
			break;
		}
		else if (boardPos[x][y].Color != color) {
			this->pieceLegalMoves.push_back({ {X, Y}, {x, y} });
		}
		else { break; }
	}
};


void Piece::Generate_KingLegalMoves(Piece boardPos[8][8]) {

	this->pieceLegalMoves.clear();

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	if (Y+1 < 8 && boardPos[X][Y + 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X, Y+1} });
	}

	// DOWN
	if (Y-1 > -1 && boardPos[X][Y - 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X, Y-1} });
	}
	
	// RIGHT
	if (X+1 < 8 && boardPos[X + 1][Y].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y} });
	}

	// LEFT
	if (X-1 > -1 && boardPos[X - 1][Y].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y} });
	}





	// UP RIGHT
	if (X+1 < 8 && Y+1 < 8 && boardPos[X + 1][Y + 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y+1} });
	}

	// UP LEFT
	if (X-1 > -1 && Y+1 < 8 && boardPos[X - 1][Y + 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y+1} });
	}

	// DOWN RIGHT
	if (X+1 < 8 && Y-1 > -1 && boardPos[X + 1][Y - 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X+1, Y-1} });
	}

	// DOWN LEFT
	if (X-1 > -1 && Y-1 > -1 && boardPos[X - 1][Y - 1].Color != color) {
		this->pieceLegalMoves.push_back({ {X, Y}, {X-1, Y-1} });
	}
};