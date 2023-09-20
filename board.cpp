#include "board.h"

Board::Board() {

	initBoard();
}

Board::Board(int who_to_play) {

	this->_who_to_play = _who_to_play;
	initBoard();
}

Board::Board(const Board& b) {
	
	initBoard();

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			board[i][j] = b.board[i][j];
		}
	}

	_who_to_play = b._who_to_play;

}


vector<int> Board::generate_legal_moves() {

	vector<int> temp;

	for (int j = 0;j < COLS;j++) {
		if (board[0][j] == 0) {
			temp.push_back(j);
		}
	}
	return temp;
}

void Board::print() {
	cout << " 0  1  2  3  4  5  6" << endl;
	cout << "____________________" << endl;

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {


			if (board[i][j] == 1) {
				cout << " " << "X" << " ";
			}
			if (board[i][j] ==-1) {
				cout << " " << "O" << " ";
			}
			if (board[i][j] == 0) {
				cout << " " << "." << " ";
			}
		}

		cout << endl;
	}
	cout << endl;
}

void Board::make_move(int move) {

	if (is_move_legal(move)) {
		for (int i = ROWS - 1; i >= 0; i--) {
			if (board[i][move] == 0) {
				board[i][move] = _who_to_play;
				_who_to_play = -_who_to_play; // change player to move to opposite
				return;
			}
		}
	}
	cout << "This move is not legal." << endl;
	cout << "Program did not make any changes into current position" << endl;
	return;
	
}

bool Board::is_move_legal(int move) {
	if (move < 0 || move > 6) {
		return false;
	}
	else {
		if (board[0][move] == 0) {
			return true;
		}
	}
	return false;
}

int Board::who_to_play() {
	return _who_to_play;
}

int Board::outcome() {
	// return 1 means first player won, -1 - opposite player won, 2 means the game goes on, 0 means draw

	int temp = 2;


	// horizontal
	for (int i = 0; i < ROWS;i++) {
		for (int j = 0;j < COLS-3; j++) {
			temp = board[i][j] + board[i][j+1] + board[i][j+2] + board[i][j+3];
			if (temp == 4) {
				return 1;
			}
			else if (temp == -4) {
				return -1;
			}
			else {
				temp = 2;
			}
		}

	}



	//vertical

	for (int i = 0; i < ROWS-3;i++) {
		for (int j = 0;j < COLS; j++) {
			temp = board[i][j] + board[i+1][j] + board[i+2][j] + board[i+3][j];
			if (temp == 4) {
				return 1;
			}
			else if (temp == -4) {
				return -1;
			}
			else {
				temp = 2;
			}
		}

	}

	//diag plus

	for (int i = 0; i < ROWS - 3;i++) {
		for (int j = 0;j < COLS - 3; j++) {
			temp = board[i][j] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3];
			if (temp == 4) {
				return 1;
			}
			else if (temp == -4) {
				return -1;
			}
			else {
				temp = 2;
			}
		}

	}

	//diag minus

	for (int i = 3; i < ROWS; i++) {
		for (int j = 0; j < COLS - 3; j++) {
			temp = board[i][j] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3];
			if (temp == 4) {
				return 1;
			}
			else if (temp == -4) {
				return -1;
			}
			else {
				temp = 2;
			}
		}

	}


	if (is_fully_expanded()) {
		return 0;
	}

	return temp;
}

bool Board::is_fully_expanded() {

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool Board::is_terminal_state() {
	if (outcome() == 1 || outcome() == -1 || outcome() == 0) return true;
	else return false;
}

void Board::reset() {
	initBoard(); // reset to all-zeros
	_who_to_play = 1;
}

void Board::flip() {
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			board[i][j] = -1 * board[i][j];
		}
	}
	_who_to_play = -1 * _who_to_play;
}

void Board::initBoard() {

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			board[i][j] = 0;
		}
	}
}


