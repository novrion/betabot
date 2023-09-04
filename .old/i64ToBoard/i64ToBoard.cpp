#include <iostream>
#include <map>

using namespace std;



map<float, char> indexToPiece = {
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





int main() {

    float inputIndex[64];


    while (true) {

        cout << endl << endl << "i64:" << endl;

        int count = 0;

        // Input
        for (int i = 0; i < 64; i++) {
            cin >> inputIndex[i];
        }

        // Output
        cout << "-------------------------------------------------" << endl;

        for (int i = 0; i < 8; i++) {
            cout << "|     |     |     |     |     |     |     |     |" << endl;
            cout << "|  ";

            for (int j = 0; j < 8; j++) {
                cout << indexToPiece.at(inputIndex[count++]) << "  |  ";
            }

            cout << endl << "|     |     |     |     |     |     |     |     |" << endl;
            cout << "-------------------------------------------------" << endl;
        }
    }

    return 0;
}