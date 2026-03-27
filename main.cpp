#include <cctype>
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

Position parsePosition(string input){
	int column = input[0] - 'a';
	int row = 8 - (input[1] - '0'); 
	Position target = {column, row};
	return target;
}

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

bool isInCheck(char board[8][8], char currentKing){
	Position kingPos;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] == currentKing){
				kingPos = {j, i};
			}
		}
	}

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(validMove(board, {j, i}, kingPos) && validMovePiece(board, {j, i}, kingPos)){
				return true;
			}
		}
	}
	
	return false;
}

bool isCheckmate(char board[8][8], char currentKing){
	if(!isInCheck(board, currentKing)){
		return false;
	}
	char lastBoard[8][8];
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			lastBoard[i][j] = board[i][j];
		}
	}

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(isSameTeam(board[i][j], currentKing)){
				for(int k = 0; k < 8; k++){
					for(int l = 0; l < 8; l++){
						if(validMove(board, {j, i}, {l, k}) && validMovePiece(board, {j, i}, {l, k})){
							movePiece(board, {j, i}, {l, k});
							bool savedKing = !isInCheck(board, currentKing);
							for(int r = 0; r < 8; r++){
								for(int c = 0; c < 8; c++){
									board[r][c] = lastBoard[r][c];
								}
							}
							if(savedKing) return false;
						}
					}
				}
			}
		}
	}
	return true;
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
	bool gameOver = false;
	int cont = 0;
	string input = "";
	Position origen, destino;
	
	while (!gameOver) {
		char currentKing = (cont % 2 == 0) ? 'K' : 'k';
		char lastBoard[8][8];
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				lastBoard[i][j] = board[i][j];
			}
		}
		if(currentKing == 'K'){
			cout << "Juegan las BLANCAS\n";
		} else {
			cout << "Juegan las NEGRAS\n";
		}
		cout << "Ingrese la posicion de la pieza que quiere mover (Ej.: e2)\n";	
		cin >> input;
		origen = parsePosition(input);

		if(!isInsideBoard(origen) || board[origen.row][origen.column] == ' '){
			cout << "La posicion de origen seleccionada no se encuentra dentro del tablero o no contiene ninguna pieza\n";
			continue;
		}

		if(!isSameTeam(board[origen.row][origen.column], currentKing)){
			cout << "No puedes mover una ficha del contrincante\n";
			continue;
		}

		cout << "Ingrese la posicion a la que quiere mover la pieza (Ej.: e4)\n";	
		cin >> input;
		destino = parsePosition(input);

		if(validMove(board, origen, destino) && validMovePiece(board, origen, destino)){
			movePiece(board, origen, destino);
		} else {
			cout << "Movimiento invalido\n";
			continue;
		}

		if(isInCheck(board, currentKing)){
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					board[i][j] = lastBoard[i][j];
				}
			}
			cout << "Ese movimiento no es posible porque se produce un jaque\n";
			continue;
		}

		if(isCheckmate(board, (cont % 2 == 0) ? 'k' : 'K')){
			if(cont % 2 == 0){
				cout << "Jaque Mate! Ganan las BLANCAS\n";
			} else {
				cout << "Jaque Mate! Ganan las NEGRAS\n";
			}
			gameOver = true;
		}

		printBoard(board);

		cont++;
	}
	return 0;
}