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

bool validMovePiece(char board[8][8], Position origin, Position target){
	char piece = board[origin.row][origin.column];
	switch(piece) {
		case 'P':
			if(board[target.row][target.column] == ' '){
				if(origin.column == target.column && origin.row == 6 && (target.row == 5 || (target.row == 4 && board[5][target.column] == ' '))) {
					return true;
				} 
				if(origin.row < 6 && target.row >= 0 && target.row - origin.row == -1 && origin.column == target.column) {
					return true;
				}
			}
		case 'p':
		if(board[target.row][target.column] == ' '){
			if(origin.column == target.column && origin.row == 1 && (target.row == 2 || (target.row == 3 && board[2][target.column] == ' '))) {
				return true;
			} 
			if(origin.row > 1 && target.row <= 7 && target.row - origin.row == 1 && origin.column == target.column) {
				return true;
			}
		}
		default: 
			return false;
	}
}

int main() {
	char board[8][8] = {
		{'r','n','b','q','k','b','n','r'},
		{'p','p','p','p','p','p','p','p'},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{'P','P','P','P','P','P','P','P'},
		{'R','N','B','Q','K','B','N','R'}
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