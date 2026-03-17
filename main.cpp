#include <iostream>

using namespace std;

void printBoard(char board[8][8]) {
    cout << "Board:\n";
    cout << "  a b c d e f g h\n";
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << ' ';
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == ' ') {
                cout << '.' << ' ';
            } else {
                cout << board[i][j] << ' ';
            }
        }
        cout << '\n';
    }
}

int main() {
    char board[8][8] = {
        {'R','N','B','Q','K','B','N','R'},
        {'P','P','P','P','P','P','P','P'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'p','p','p','p','p','p','p','p'},
        {'r','n','b','q','k','b','n','r'}
    };
    printBoard(board);
    return 0;
}