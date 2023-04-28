#include <iostream>
#include <map>
#include <vector>

#include "Board.h"

using namespace std;



// Initialize Static Members (Board)
bool Board::isExit = false;



int main() {

    cout << "\n" << "-----Commands-----" << endl << "position->position" << endl << "exit" << endl << "------------------" << endl << endl;

    bool firstMove = true;



    pair<double, vector<Move>> minimaxData;

    Board b;
    b.Initialize();



    while (true) {

        // Check If First Move ~ ~
        if (firstMove) {
            firstMove = false;

            if (!b.isWhitePlayer) {
                b.Main_MakeMove();
            }
        }
        else {
            b.Main_MakeMove();
        }

        // Exit ~ ~
        if (Board::isExit) {
            break;
        }





        // Logic ~ ~
        minimaxData = Minimax(b, b.depth, -99999, 99999, b.isWhitePlayer);
        b.MakeMove(minimaxData.second[minimaxData.second.size() - 1]);


        // Print ~ ~
        PrintMain(b.boardPos, minimaxData);
    }

    return 0;
}