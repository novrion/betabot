#include <iostream>
#include <map>

#include "Board.h"

using namespace std;



map<int, char> notationValue = {
  {0, 'a'},
  {1, 'b'},
  {2, 'c'},
  {3, 'd'},
  {4, 'e'},
  {5, 'f'},
  {6, 'g'},
  {7, 'h'}
};

map<char, int> indexValue = {
  {'a', 0},
  {'b', 1},
  {'c', 2},
  {'d', 3},
  {'e', 4},
  {'f', 5},
  {'g', 6},
  {'h', 7}
};



// Input ~ ~
void Board::Main_MakeMove() {

    string input;


    // Input
    cout << "\n\n\n";
    cout << "Input: " << "\n";
    cin >> input;

    // Check if exit
    if (input == "exit") {
        Board::isExit = true;
        return;
    }

    Move move = TranslateToPair(input);
    ConvertToMove(this, move);

    this->MakeMove(move);
}

bool Board::InputColor() {

    char indata;

    cout << "(B || W) Black or White: ";
    cin >> indata;

    if (indata == 'W' || indata == 'w') {
        return true;
    }

    else {
        return false;
    }
}





// Translation ~ ~
Move TranslateToPair(std::string notation) {
    int fromX, fromY, toX, toY;

    fromX = indexValue.at(notation[0]);
    fromY = notation[1] - 1 - '0';

    toX = indexValue.at(notation[4]);
    toY = notation[5] - 1 - '0';

    return Move({fromX, fromY}, {toX, toY});
}

std::string TranslateToNotation(Move move) {

    if (move.from.first == -1) {
        return "None";
    }

    string notation;

    notation.push_back(notationValue.at(move.from.first));
    notation = notation + to_string(move.from.second + 1);

    notation.push_back('-');
    notation.push_back('>');

    notation.push_back(notationValue.at(move.to.first));
    notation = notation + to_string(move.to.second + 1);

    return notation;
}

void ConvertToMove(Board* b, Move& move) {

    double type = b->boardPos[move.from.first][move.from.second].Type;
    double kill = b->boardPos[move.to.first][move.to.second].Type;
    
    // Promotion & En Passant ~ ~
    if (abs(type) == 1) {

        // White
        if (type == 1) {

            // Promotion
            if (move.to.second == 7) {
                move.promotion = 9;
            }

            // En Passant
            else if (kill == 0 && move.from.first != move.to.first) {
                move.isEnPassant = true;
                move.isCapture = -1;
            }
        }

        // Black
        else if (type == -1) {

            // Promotion
            if (move.to.second == 0) {
                move.promotion = 0;
            }

            // En Passant
            else if (kill == 0 && move.from.first != move.to.first) {
                move.isEnPassant = true;
                move.isCapture = 1;
            }
        }
    }


    // Castling ~ ~
    else if (abs(type) == 55555) {

        // White
        if (type == 55555) {

            // Short
            if (move.to.first == move.from.first + 2) {
                move.isCastle = 1;
            }

            // Long
            else if (move.to.first == move.from.first - 2) {
                move.isCastle = 2;
            }
        }

        // Black
        else {

            // Short
            if (move.to.first == move.from.first + 2) {
                move.isCastle = 3;
            }

            // Long
            else if (move.to.first == move.from.first - 2) {
                move.isCastle = 4;
            }
        }
    }


    // ~ ~
    else {
        move.isCapture = kill;
    }
}



void PrintLine(std::vector<Move> moves) {

    cout << "Line: ";

    for (int i = moves.size() - 1; -1 < i; i--) {
        cout << TranslateToNotation(moves[i]) << " ";
    }

    cout << "\n";
}

void PrintBoard(Piece boardPos[8][8]) {

    map<double, char> piecesValue = {
      {0, ' '},
      {1, 'P'},
      {3, 'H'},
      {3.1, 'B'},
      {5, 'R'},
      {9, 'Q'},
      {55555, 'K'},

      {-1, 'p'},
      {-3, 'h'},
      {-3.1, 'b'},
      {-5, 'r'},
      {-9, 'q'},
      {-55555, 'k'}
    };

    // Print Board
    cout << "-------------------------------------------------" << "\n";

    for (int i = 7; -1 < i; i--) {
        cout << "|     |     |     |     |     |     |     |     |" << "\n";
        cout << "|  ";

        for (int j = 0; j < 8; j++) {
            cout << piecesValue.at(boardPos[j][i].Type) << "  |  ";
        }

        cout << "\n" << "|     |     |     |     |     |     |     |     |" << "\n";
        cout << "-------------------------------------------------" << "\n";
    }

    cout << "\n\n";

    // Print i64
    for (int i = 7; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << boardPos[i][j].Type << " ";
        }
    }
}





// Print Main ~ ~
void PrintMain(Piece boardPos[8][8], std::pair<double, std::vector<Move>> minimaxData) {

    string output = TranslateToNotation(minimaxData.second[minimaxData.second.size() - 1]);
    double evaluation = minimaxData.first;

    cout << "\n" << "Eval: " << evaluation << "\n";
    cout << "Move: " << output << "\n\n";

    PrintLine(minimaxData.second);

    PrintBoard(boardPos);

    cout << "\n\n\n";
}