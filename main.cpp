#include <iostream>
#include <map>

#include "Board.h"

using namespace std;


// Initialize Static Members (Board)
pair<pair<int, int>, pair<int, int>> Board::bestMove = { {0, 0}, {0, 0} };
bool Board::isExit = false;

map<float, char> piecesValue = {
    {0, 'O'},
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



int main()
{
    float evaluation;

    Board bord;
    bord.InitializeBoard();


    // White player Start -------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if (bord.isWhitePlayer) {
        evaluation = Minimax(bord, bord.depth, bord.isWhitePlayer);
        bord.MakeMove(Board::bestMove.first, Board::bestMove.second);

        cout << endl << "Got final result... eval: " << evaluation << endl;
        cout << endl << endl << "Final move: " << Board::bestMove.first.first << Board::bestMove.first.second << Board::bestMove.second.first << Board::bestMove.second.second << endl;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << piecesValue.at(bord.boardPos[i][j].Type) << " ";
            }
            cout << endl;
        }
    }
    // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    // Loop ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    while (true) {

        bord.InputAndMakeNextMove();
        if (Board::isExit) {
            break;
        }

        evaluation = Minimax(bord, bord.depth, bord.isWhitePlayer);
        bord.MakeMove(Board::bestMove.first, Board::bestMove.second);

        cout << endl << "Got final result... eval: " << evaluation << endl;
        cout << endl << endl << "Final move: " << Board::bestMove.first.first << Board::bestMove.first.second << Board::bestMove.second.first << Board::bestMove.second.second << endl;

        // Print Board
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << piecesValue.at(bord.boardPos[i][j].Type) << " ";
            }
            cout << endl;
        }
    }
    // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    return 0;
}












//----------------------------------------------------------------------------------------------------------------------------------------
// Fix so that getting moves only gets for either white or black. Can't have both. For each search you only want one of the colours moves!
// Other wise i.e black will think white moves are valid!
//----------------------------------------------------------------------------------------------------------------------------------------