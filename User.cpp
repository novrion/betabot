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
void Board::InputAndMakeNextMove() {

    string input;
    pair<pair<int, int>, pair<int, int>> move;


    // Input
    cout << endl << endl << endl;
    cout << "Input: " << endl;
    cin >> input;

    // Check if exit
    if (input == "exit") {
        Board::isExit = true;
        return;
    }

    move = TranslateToPair(input);

    this->MakeMove({ move.first.first, move.first.second }, { move.second.first, move.second.second });
}

bool Board::InputPlayerColor() {

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
std::pair<std::pair<int, int>, std::pair<int, int>> TranslateToPair(std::string notation) {
    int fromX, fromY, toX, toY;

    fromX = indexValue.at(notation[0]);
    fromY = notation[1] - 1 - '0';

    toX = indexValue.at(notation[4]);
    toY = notation[5] - 1 - '0';

    return { {fromX, fromY}, {toX, toY} };
}

std::string TranslateToNotation(std::pair<std::pair<int, int>, std::pair<int, int>> coordinates) {
    string notation;

    notation.push_back(notationValue.at(coordinates.first.first));
    notation = notation + to_string(coordinates.first.second + 1);

    notation.push_back('-');
    notation.push_back('>');

    notation.push_back(notationValue.at(coordinates.second.first));
    notation = notation + to_string(coordinates.second.second + 1);

    return notation;
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
    cout << "-------------------------------------------------" << endl;

    for (int i = 0; i < 8; i++) {
        cout << "|     |     |     |     |     |     |     |     |" << endl;
        cout << "|  ";

        for (int j = 0; j < 8; j++) {
            cout << piecesValue.at(boardPos[i][j].Type) << "  |  ";
        }

        cout << endl << "|     |     |     |     |     |     |     |     |" << endl;
        cout << "-------------------------------------------------" << endl;
    }

    cout << endl << endl;

    // Print i64
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << boardPos[i][j].Type << " ";
        }
    }
}