#include <iostream>
#include <map>

#include "Board.h"

using namespace std;



// Initialize Static Members (Board)
pair<pair<int, int>, pair<int, int>> Board::bestMove = { {0, 0}, {0, 0} };
bool Board::isExit = false;





int main() {

    cout << endl << "-----Commands-----" << endl << "position->position" << endl << "exit" << endl << "------------------" << endl << endl;

    bool firstMove = true;



    string output;
    double evaluation;

    Board bord;
    bord.InitializeBoard();



    while (true) {

        if (firstMove) {
            firstMove = false;

            if (!bord.isWhitePlayer) {
                bord.InputAndMakeNextMove();
            }
        }
        else {
            bord.InputAndMakeNextMove();
        }

        if (Board::isExit) {
            break;
        }

        evaluation = Minimax(bord, bord.depth, -99999, 99999, bord.isWhitePlayer);
        bord.MakeMove(Board::bestMove.first, Board::bestMove.second);


        // Print ~ ~
        output = TranslateToNotation(Board::bestMove);

        cout << endl << "Eval: " << evaluation << endl;
        cout << "Move: " << output << endl << endl;
        PrintBoard(bord.boardPos);
        cout << endl << endl << endl;
    }

    return 0;
}