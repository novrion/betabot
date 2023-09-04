#include <vector>

#include "Board.h"

using namespace std;


// --------------------------------------------------------------------------------------------------------
// Remember!!!!!!!! if pawn takes and gets to promotion square !!!!!!!!!! Not implemented!!!!!!!
// --------------------------------------------------------------------------------------------------------


// Non Captures ~ ~
void Piece::Generate_Pawn_Non_Captures(Board* b, pair<int, vector<Move>>& moves) {

	int color = this->Color;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (color == 1) {

		// Y + 2
		if (Y == 1 && b->boardPos[X][Y + 1].Type == 0 && b->boardPos[X][Y + 2].Type == 0) {
			moves.second.push_back(Move({X, Y}, {X, Y + 2}));
		}

		// Y + 1
		if (Y + 1 < 8 && b->boardPos[X][Y + 1].Type == 0) {

			if (Y + 1 == 7) {
				moves.second.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 3, false, 0));
				moves.second.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 3.1, false, 0));
				moves.second.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 5, false, 0));
				moves.second.push_back(Move({ X, Y }, { X, Y + 1 }, 0, 9, false, 0));
				moves.first += 4;
			}

			else {
				moves.second.push_back(Move({ X, Y }, { X, Y + 1 }));
				moves.first++;
			}
		}
	}

	else {

		// Y - 2
		if (Y == 6 && b->boardPos[X][Y - 1].Type == 0 && b->boardPos[X][Y - 2].Type == 0) {
			moves.second.push_back(Move({X, Y}, {X, Y - 2}));
			moves.first++;
		}

		// Y - 1
		if (-1 < Y - 1 && b->boardPos[X][Y - 1].Type == 0) {

			if (Y - 1 == 0) {
				moves.second.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -3, false, 0));
				moves.second.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -3.1, false, 0));
				moves.second.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -5, false, 0));
				moves.second.push_back(Move({ X, Y }, { X, Y - 1 }, 0, -9, false, 0));
				moves.first += 4;
			}

			else {
				moves.second.push_back(Move({ X, Y }, { X, Y - 1 }));
				moves.first++;
			}
		}
	}
};


void Piece::Generate_Horse_Non_Captures(Board* b, pair<int, vector<Move>>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (X + 1 < 8 && Y + 2 < 8 && b->boardPos[X + 1][Y + 2].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y + 2}));
		moves.first++;
	}

	if (-1 < X - 1 && Y + 2 < 8 && b->boardPos[X - 1][Y + 2].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y + 2}));
		moves.first++;
	}

	if (X + 2 < 8 && Y + 1 < 8 && b->boardPos[X + 2][Y + 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 2, Y + 1}));
		moves.first++;
	}

	if (-1 < X - 2 && Y + 1 < 8 && b->boardPos[X - 2][Y + 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 2, Y + 1}));
		moves.first++;
	}

	if (X + 2 < 8 && -1 < Y - 1 && b->boardPos[X + 2][Y - 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 2, Y - 1}));
		moves.first++;
	}

	if (-1 < X - 2 && -1 < Y - 1 && b->boardPos[X - 2][Y - 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 2, Y - 1}));
		moves.first++;
	}

	if (X + 1 < 8 && -1 < Y - 2 && b->boardPos[X + 1][Y - 2].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y - 2}));
		moves.first++;
	}

	if (-1 < X - 1 && -1 < Y - 2 && b->boardPos[X - 1][Y - 2].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y - 2}));
		moves.first++;
	}
};


void Piece::Generate_Bishop_Non_Captures(Board* b, pair<int, vector<Move>>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}
};


void Piece::Generate_Rook_Non_Captures(Board* b, pair<int, vector<Move>>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y + 1; y < 8; y++) {

		if (b->boardPos[X][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {X, y}));
			moves.first++;
		}
		else { break; }
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {X, y}));
			moves.first++;
		}
		else { break; }
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, Y}));
			moves.first++;
		}
		else { break; }
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, Y}));
			moves.first++;
		}
		else { break; }
	}
};


void Piece::Generate_Queen_Non_Captures(Board* b, pair<int, vector<Move>>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	for (int y = Y + 1; y < 8; y++) {

		if (b->boardPos[X][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {X, y}));
			moves.first++;
		}
		else { break; }
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {X, y}));
			moves.first++;
		}
		else { break; }
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, Y}));
			moves.first++;
		}
		else { break; }
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, Y}));
			moves.first++;
		}
		else { break; }
	}





	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == 0) {
			moves.second.push_back(Move({X, Y}, {x, y}));
			moves.first++;
		}
		else { break; }
	}
};


void Piece::Generate_King_Non_Captures(Board* b, pair<int, vector<Move>>& moves) {

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;



	// UP
	if (Y + 1 < 8 && b->boardPos[X][Y + 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X, Y + 1}));
		moves.first++;
	}

	// DOWN
	if (Y - 1 > -1 && b->boardPos[X][Y - 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X, Y - 1}));
		moves.first++;
	}

	// RIGHT
	if (X + 1 < 8 && b->boardPos[X + 1][Y].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y}));
		moves.first++;
	}

	// LEFT
	if (X - 1 > -1 && b->boardPos[X - 1][Y].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y}));
		moves.first++;
	}





	// UP RIGHT
	if (X + 1 < 8 && Y + 1 < 8 && b->boardPos[X + 1][Y + 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y + 1}));
		moves.first++;
	}

	// UP LEFT
	if (X - 1 > -1 && Y + 1 < 8 && b->boardPos[X - 1][Y + 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y + 1}));
		moves.first++;
	}

	// DOWN RIGHT
	if (X + 1 < 8 && Y - 1 > -1 && b->boardPos[X + 1][Y - 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y - 1}));
		moves.first++;
	}

	// DOWN LEFT
	if (X - 1 > -1 && Y - 1 > -1 && b->boardPos[X - 1][Y - 1].Color == 0) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y - 1}));
		moves.first++;
	}





	// Castle
	if (this->isMoved == false) {

		// White Short
		if (this->Color == 1) {
			bool canCastle = true;

			if (b->boardPos[X + 1][0].Color == 0 && b->boardPos[X + 2][0].Color == 0 && b->boardPos[X + 3][0].Color == 5 && b->boardPos[X + 3][0].isMoved == false) {

				// For each square
				for (int i = 4; i < 7; i++) {

					// UP
					for (int y = 1; y < 8; y++) {

						if (b->boardPos[i][y].Type == -5 || b->boardPos[i][y].Type == -9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// UP LEFT
					for (int x = i - 1, y = 1; -1 < x && y < 8; x--, y++) {

						if (b->boardPos[i][y].Type == -3.1 || b->boardPos[i][y].Type == -9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// UP RIGHT
					for (int x = i + 1, y = 1; x < 8 && y < 8; x++, y++) {

						if (b->boardPos[i][y].Type == -3.1 || b->boardPos[i][y].Type == -9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}
				}


				// HORSE
				for (int x = 3; x < 8; x++) {
					for (int y = 1; y < 3; y++) {
						if (b->boardPos[x][y].Type == -3) {
							canCastle = false;
							break;
						}
					}
				}
				if (b->boardPos[2][1].Type == -3) {
					canCastle = false;
				}


				// PAWN
				for (int x = 3; x < 8; x++) {
					if (b->boardPos[x][1].Type == -1) {
						canCastle = false;
						break;
					}
				}


				// KING
				if (b->boardPos[6][1].Type == -55555) {
					canCastle = false;
				}





				if (canCastle) {
					moves.second.push_back(Move({ 4, 0 }, { 6, 0 }, 0, 0, false, 1));
					moves.first++;
				}
			}





			// White Long
			if (b->boardPos[X - 1][0].Color == 0 && b->boardPos[X - 2][0].Color == 0 && b->boardPos[X - 3][0].Color == 0 && b->boardPos[X - 4][0].Color == 5 && b->boardPos[X - 4][0].isMoved == false) {
				canCastle = true;

				// For each square
				for (int i = 4; 0 < i; i--) {

					// UP
					for (int y = 1; y < 8; y++) {

						if (b->boardPos[i][y].Type == -5 || b->boardPos[i][y].Type == -9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// UP LEFT
					for (int x = i - 1, y = 1; -1 < x && y < 8; x--, y++) {

						if (b->boardPos[i][y].Type == -3.1 || b->boardPos[i][y].Type == -9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// UP RIGHT
					for (int x = i + 1, y = 1; x < 8 && y < 8; x++, y++) {

						if (b->boardPos[i][y].Type == -3.1 || b->boardPos[i][y].Type == -9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}
				}


				// HORSE
				for (int x = 5; -1 < x; x--) {
					for (int y = 1; y < 3; y++) {
						if (b->boardPos[x][y].Type == -3) {
							canCastle = false;
							break;
						}
					}
				}
				if (b->boardPos[6][1].Type == -3) {
					canCastle = false;
				}


				// PAWN
				for (int x = 5; -1 < x; x--) {
					if (b->boardPos[x][1].Type == -1) {
						canCastle = false;
						break;
					}
				}


				// KING
				if (b->boardPos[1][1].Type == -55555 || b->boardPos[2][1].Type == -55555) {
					canCastle = false;
				}





				if (canCastle) {
					moves.second.push_back(Move({ 4, 0 }, { 2, 0 }, 0, 0, false, 2));
					moves.first++;
				}
			}
		}




		
		// Black Short
		else {
			bool canCastle = true;

			if (b->boardPos[X + 1][7].Color == 0 && b->boardPos[X + 2][7].Color == 0 && b->boardPos[X + 3][7].Color == -5 && b->boardPos[X + 3][7].isMoved == false) {

				// For each square
				for (int i = 4; i < 7; i++) {

					// DOWN
					for (int y = 1; -1 < y; y--) {

						if (b->boardPos[i][y].Type == 5 || b->boardPos[i][y].Type == 9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// DOWN LEFT
					for (int x = i - 1, y = 6; -1 < x && -1 < y; x--, y--) {

						if (b->boardPos[i][y].Type == 3.1 || b->boardPos[i][y].Type == 9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// DOWN RIGHT
					for (int x = i + 1, y = 6; x < 8 && -1 < y; x++, y--) {

						if (b->boardPos[i][y].Type == 3.1 || b->boardPos[i][y].Type == 9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}
				}


				// HORSE
				for (int x = 3; x < 8; x++) {
					for (int y = 5; y < 7; y++) {
						if (b->boardPos[x][y].Type == 3) {
							canCastle = false;
							break;
						}
					}
				}
				if (b->boardPos[2][6].Type == -3) {
					canCastle = false;
				}


				// PAWN
				for (int x = 3; x < 8; x++) {
					if (b->boardPos[x][6].Type == 1) {
						canCastle = false;
						break;
					}
				}


				// KING
				if (b->boardPos[6][6].Type == 55555) {
					canCastle = false;
				}





				if (canCastle) {
					moves.second.push_back(Move({ 4, 7 }, { 6, 7 }, 0, 0, false, 3));
					moves.first++;
				}
			}




			// Black Long
			if (b->boardPos[X - 1][7].Color == 0 && b->boardPos[X - 2][7].Color == 0 && b->boardPos[X - 3][7].Color == 0 && b->boardPos[X - 4][7].Color == -5 && b->boardPos[X - 4][7].isMoved == false) {
				canCastle = true;

				// For each square
				for (int i = 4; 0 < i; i--) {

					// DOWN
					for (int y = 6; -1 < y; y--) {

						if (b->boardPos[i][y].Type == 5 || b->boardPos[i][y].Type == 9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// DOWN LEFT
					for (int x = i - 1, y = 6; -1 < x && -1 < y; x--, y--) {

						if (b->boardPos[i][y].Type == 3.1 || b->boardPos[i][y].Type == 9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}

					// DOWN RIGHT
					for (int x = i + 1, y = 6; x < 8 && -1 < y; x++, y--) {

						if (b->boardPos[i][y].Type == 3.1 || b->boardPos[i][y].Type == 9) {
							canCastle = false;
							break;
						}

						else if (b->boardPos[i][y].Color != 0) {
							break;
						}
					}
				}


				// HORSE
				for (int x = 5; -1 < x; x--) {
					for (int y = 5; y < 7; y++) {
						if (b->boardPos[x][y].Type == 3) {
							canCastle = false;
							break;
						}
					}
				}
				if (b->boardPos[6][6].Type == 3) {
					canCastle = false;
				}


				// PAWN
				for (int x = 5; -1 < x; x--) {
					if (b->boardPos[x][6].Type == 1) {
						canCastle = false;
						break;
					}
				}


				// KING
				if (b->boardPos[1][6].Type == 55555 || b->boardPos[2][6].Type == 55555) {
					canCastle = false;
				}





				if (canCastle) {
					moves.second.push_back(Move({ 4, 7 }, { 2, 7 }, 0, 0, false, 4));
					moves.first++;
				}
			}
		}
	}
};










// Captures ~ ~
void Piece::Generate_PawnCaptures(Board* b, pair<int, vector<Move>>& moves) {

	int color = this->Color;
	int otherColor = color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (color == 1) {

		/*// En Passant
		if (b->canEnPassant.first != -1 && X == 5) {

			if (b->canEnPassant.first == X + 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X + 1, Y + 1}, -1, 0, true ,0));
				moves.first++;

			}

			else if (b->canEnPassant.first == X - 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X - 1, Y + 1}, -1, 0, true, 0));
				moves.first++;
			}
		}*/



		// Take Right
		if (X + 1 < 8 && Y + 1 < 8 && b->boardPos[X + 1][Y + 1].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {X + 1, Y + 1}, b->boardPos[X + 1][Y + 1].Type));
			moves.first++;
		}

		// Take Left
		if (-1 < X - 1 && Y + 1 < 8 && b->boardPos[X - 1][Y + 1].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {X - 1, Y + 1}, b->boardPos[X - 1][Y + 1].Type));
			moves.first++;
		}
	}

	else {

		/*// En Passant
		if (b->canEnPassant.first != -1 && X == 2) {

			if (b->canEnPassant.first == X + 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X + 1, Y - 1}, 1, 0, true, 0));
				moves.first++;

			}

			else if (b->canEnPassant.first == X - 1 && b->canEnPassant.second == Y) {
				moves.push_back(Move({X, Y}, {X - 1, Y - 1}, 1, 0, true, 0));
				moves.first++;
			}
		}*/



		// Take Right
		if (-1 < X - 1 && -1 < Y - 1 && b->boardPos[X - 1][Y - 1].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {X - 1, Y - 1}, b->boardPos[X - 1][Y - 1].Type));
			moves.first++;
		}

		// Take Left
		if (X + 1 < 8 && -1 < Y - 1 && b->boardPos[X + 1][Y - 1].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {X + 1, Y - 1}, b->boardPos[X + 1][Y - 1].Type));
			moves.first++;
		}
	}
};


void Piece::Generate_HorseCaptures(Board* b, pair<int, vector<Move>>& moves) {

	int otherColor = this->Color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;

	if (X + 1 < 8 && Y + 2 < 8 && b->boardPos[X + 1][Y + 2].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y + 2}, b->boardPos[X + 1][Y + 2].Type));
		moves.first++;
	}

	if (-1 < X - 1 && Y + 2 < 8 && b->boardPos[X - 1][Y + 2].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y + 2}, b->boardPos[X - 1][Y + 2].Type));
		moves.first++;

	}

	if (X + 2 < 8 && Y + 1 < 8 && b->boardPos[X + 2][Y + 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 2, Y + 1}, b->boardPos[X + 2][Y + 1].Type));
		moves.first++;
	}

	if (-1 < X - 2 && Y + 1 < 8 && b->boardPos[X - 2][Y + 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 2, Y + 1}, b->boardPos[X - 2][Y + 1].Type));
		moves.first++;
	}

	if (X + 2 < 8 && -1 < Y - 1 && b->boardPos[X + 2][Y - 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 2, Y - 1}, b->boardPos[X + 2][Y - 1].Type));
		moves.first++;
	}

	if (-1 < X - 2 && -1 < Y - 1 && b->boardPos[X - 2][Y - 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 2, Y - 1}, b->boardPos[X - 2][Y - 1].Type));
		moves.first++;
	}

	if (X + 1 < 8 && -1 < Y - 2 && b->boardPos[X + 1][Y - 2].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y - 2}, b->boardPos[X + 1][Y - 2].Type));
		moves.first++;
	}

	if (-1 < X - 1 && -1 < Y - 2 && b->boardPos[X - 1][Y - 2].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y - 2}, b->boardPos[X - 1][Y - 2].Type));
		moves.first++;
	}
};


void Piece::Generate_BishopCaptures(Board* b, pair<int, vector<Move>>& moves) {

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
			moves.second.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {x, y}, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}
};


void Piece::Generate_RookCaptures(Board* b, pair<int, vector<Move>>& moves) {

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
			moves.second.push_back(Move({X, Y}, {X, y}, b->boardPos[X][y].Type));
			moves.first++;
			break;
		}
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == color) {
			break;
		}

		if (b->boardPos[X][y].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {X, y}, b->boardPos[X][y].Type));
			moves.first++;
			break;
		}
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {x, Y}, b->boardPos[x][Y].Type));
			moves.first++;
			break;
		}
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.second.push_back(Move({X, Y}, {x, Y}, b->boardPos[x][Y].Type));
			moves.first++;
			break;
		}
	}
};


void Piece::Generate_QueenCaptures(Board* b, pair<int, vector<Move>>& moves) {

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
			moves.second.push_back(Move({ X, Y }, { X, y }, b->boardPos[X][y].Type));
			moves.first++;
			break;
		}
	}

	// DOWN
	for (int y = Y - 1; -1 < y; y--) {

		if (b->boardPos[X][y].Color == color) {
			break;
		}

		if (b->boardPos[X][y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { X, y }, b->boardPos[X][y].Type));
			moves.first++;
			break;
		}
	}

	// RIGHT
	for (int x = X + 1; x < 8; x++) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { x, Y }, b->boardPos[x][Y].Type));
			moves.first++;
			break;
		}
	}

	// LEFT
	for (int x = X - 1; -1 < x; x--) {

		if (b->boardPos[x][Y].Color == color) {
			break;
		}

		if (b->boardPos[x][Y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { x, Y }, b->boardPos[x][Y].Type));
			moves.first++;
			break;
		}
	}





	// UP RIGHT
	for (int x = X + 1, y = Y + 1; x < 8 && y < 8; x++, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}

	// UP LEFT
	for (int x = X - 1, y = Y + 1; -1 < x && y < 8; x--, y++) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}

	// DOWN RIGHT
	for (int x = X + 1, y = Y - 1; x < 8 && -1 < y; x++, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}

	// DOWN LEFT
	for (int x = X - 1, y = Y - 1; -1 < x && -1 < y; x--, y--) {

		if (b->boardPos[x][y].Color == color) {
			break;
		}

		if (b->boardPos[x][y].Color == otherColor) {
			moves.second.push_back(Move({ X, Y }, { x, y }, b->boardPos[x][y].Type));
			moves.first++;
			break;
		}
	}
};


void Piece::Generate_KingCaptures(Board* b, pair<int, vector<Move>>& moves) {

	int otherColor = this->Color * -1;

	int X = this->piecePosition.first;
	int Y = this->piecePosition.second;


	// UP
	if (Y + 1 < 8 && b->boardPos[X][Y + 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X, Y + 1}, b->boardPos[X][Y + 1].Type));
		moves.first++;
	}

	// DOWN
	if (Y - 1 > -1 && b->boardPos[X][Y - 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X, Y - 1}, b->boardPos[X][Y - 1].Type));
		moves.first++;
	}

	// RIGHT
	if (X + 1 < 8 && b->boardPos[X + 1][Y].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y}, b->boardPos[X + 1][Y].Type));
		moves.first++;
	}

	// LEFT
	if (X - 1 > -1 && b->boardPos[X - 1][Y].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y}, b->boardPos[X - 1][Y].Type));
		moves.first++;
	}





	// UP RIGHT
	if (X + 1 < 8 && Y + 1 < 8 && b->boardPos[X + 1][Y + 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y + 1}, b->boardPos[X + 1][Y + 1].Type));
		moves.first++;
	}

	// UP LEFT
	if (X - 1 > -1 && Y + 1 < 8 && b->boardPos[X - 1][Y + 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y + 1}, b->boardPos[X - 1][Y + 1].Type));
		moves.first++;
	}

	// DOWN RIGHT
	if (X + 1 < 8 && Y - 1 > -1 && b->boardPos[X + 1][Y - 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X + 1, Y - 1}, b->boardPos[X + 1][Y - 1].Type));
		moves.first++;
	}

	// DOWN LEFT
	if (X - 1 > -1 && Y - 1 > -1 && b->boardPos[X - 1][Y - 1].Color == otherColor) {
		moves.second.push_back(Move({X, Y}, {X - 1, Y - 1}, b->boardPos[X - 1][Y - 1].Type));
		moves.first++;
	}
};