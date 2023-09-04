#include <iostream>
#include <vector>

#include "board.h"

using namespace std;



// Initialize Static Members (Board)
bool Board::isExit = false;



int main() {

    cout << "\n" << "-----Commands-----" << "\n" << "position->position" << "\n" << "exit" << "\n" << "------------------" << "\n\n";
    
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

            // Input Move ~ ~
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