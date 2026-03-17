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

struct Position {
	int column;
	int row;
};

void movePiece(char board[8][8], Position origin, Position target) {
	board[target.row][target.column] = board[origin.row][origin.column];
	board[origin.row][origin.column] = ' ';
}

bool isInsideBoard(Position pos){
	return pos.row >= 0 && pos.row <= 7 && pos.column >= 0 && pos.column <= 7;
}

bool isSameTeam(char piece1, char piece2){
	if(piece1 == ' ' || piece2 == ' ') {
		return false;
	}
	return isupper(piece1) == isupper(piece2);
}

bool validMove(char board[8][8], Position origin, Position target) {
	if(!isInsideBoard(origin) || !isInsideBoard(target)){
		return false;
	}
	if(board[origin.row][origin.column] == ' '){
		return false;
	}
	if(isSameTeam(board[origin.row][origin.column], board[target.row][target.column])){
		return false;
	}
	return true;
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
	Position origen = {.column = 4, .row = 6};  // e2
	Position destino = {.column = 4, .row = 4}; // e4
	if(validMove(board, origen, destino)){
		movePiece(board, origen, destino);
	}
	printBoard(board);
	return 0;
}