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

bool validRookMove(char board[8][8], Position origin, Position target){
	bool squareBusy = false;
	if((origin.row == target.row && origin.column != target.column) || (origin.column == target.column && origin.row != target.row)) {
		if(origin.row == target.row && origin.column != target.column) {
			int direction = (target.column > origin.column) ? 1 : -1;
			int distance = abs(target.column - origin.column);
			for(int i = 1; i <= distance - 1; i++) {
				if(board[origin.row][origin.column + i * direction] != ' '){
					squareBusy = true;
				}
			}
		}
		if(origin.column == target.column && origin.row != target.row) {
			int direction = (target.row > origin.row) ? 1 : -1;
			int distance = abs(target.row - origin.row);
			for(int i = 1; i <= distance - 1; i++) {
				if(board[origin.row + i * direction][origin.column] != ' '){
					squareBusy = true;
				}
			}
		}
		return !squareBusy;
	}
	return false;
}

bool validBishopMove(char board[8][8] , Position origin, Position target) {
	bool squareBusy = false;
	if(abs(origin.row - target.row) == abs(origin.column - target.column)) {
		int directionRow = (target.row > origin.row) ? 1 : -1;
		int directionCol = (target.column > origin.column) ? 1 : -1;
		int distance = abs(target.row - origin.row);
		for(int i = 1; i <= distance - 1; i++){
			if(board[origin.row + i * directionRow][origin.column + i * directionCol] != ' ') {
				squareBusy = true;
			}
		}
		return !squareBusy;
	}
	return false;
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
			if(board[target.row][target.column] != ' '){
				if(origin.row - 1 == target.row && origin.column - 1 == target.column){
					return true;
				}
				if(origin.row - 1 == target.row && origin.column + 1 == target.column){
					return true;
				}
			}
			return false;
		case 'p':
			if(board[target.row][target.column] == ' '){
				if(origin.column == target.column && origin.row == 1 && (target.row == 2 || (target.row == 3 && board[2][target.column] == ' '))) {
					return true;
				} 
				if(origin.row > 1 && target.row <= 7 && target.row - origin.row == 1 && origin.column == target.column) {
					return true;
				}
			}
			if(board[target.row][target.column] != ' '){
				if(origin.row + 1 == target.row && origin.column - 1 == target.column){
					return true;
				}
				if(origin.row + 1 == target.row && origin.column + 1 == target.column){
					return true;
				}
			}
			return false;
		case 'R':
		case 'r':
			return validRookMove(board, origin, target);
		case 'B':
		case 'b':
			return validBishopMove(board, origin, target);
		case 'Q':
		case 'q':
			return validRookMove(board, origin, target) || validBishopMove(board, origin, target);
		case 'N':
		case 'n':
			if((abs(origin.row - target.row) == 2 && abs(origin.column - target.column) == 1) || (abs(origin.row - target.row) == 1 && abs(origin.column - target.column) == 2)) {
				return true;
			}
			return false;
		case 'K':
		case 'k':
			if(abs(origin.row - target.row) <= 1 && abs(origin.column - target.column) <= 1) {
				return true;
			}
			if(origin.row == target.row && origin.column == target.column) {
				return false;
			}
			return false;
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
	if(validMove(board, origen, destino) && validMovePiece(board, origen, destino)){
		movePiece(board, origen, destino);
	}
	printBoard(board);
	return 0;
}