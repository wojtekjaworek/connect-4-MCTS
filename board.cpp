#include "board.h"

Board::Board() {

	this->initBoard();
}

Board::Board(int who_to_play) {

	this->_who_to_play = _who_to_play;
	this->initBoard();
}

Board::Board(const Board& b) {
	
	this->initBoard();

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			this->board[i][j] = b.board[i][j];
		}
	}

	this->_who_to_play = b._who_to_play;

}


vector<int> Board::generate_legal_moves() {

	vector<int> temp;

	for (int j = 0;j < COLS;j++) {
		if (this->board[0][j] == 0) {
			temp.push_back(j);
		}
	}
	return temp;
}

void Board::print() {

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (this->board[i][j] == 1 || this->board[i][j] == 0) {
				cout << " " << this->board[i][j] << " ";
			}
			else {
				cout << "" << this->board[i][j] << " ";
			}
		}

		cout << endl;
	}
	cout << endl;
}

void Board::make_move(int move) {

	if (is_move_legal(move)) {
		for (int i = ROWS - 1; i >= 0; i--) {
			if (this->board[i][move] == 0) {
				this->board[i][move] = this->_who_to_play;
				this->_who_to_play = -this->_who_to_play; // change player to move to opposite
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
		if (this->board[0][move] == 0) {
			return true;
		}
	}
	return false;
}

int Board::who_to_play() {
	return this->_who_to_play;
}

int Board::outcome() {
	// return 1 means first player won, -1 - opposite player won, 2 means the game goes on, 0 means draw

	int temp = 2;


	// poziome
	for (int i = 0; i < ROWS;i++) {
		for (int j = 0;j < COLS-3; j++) {
			temp = this->board[i][j] + this->board[i][j+1] + this->board[i][j+2] + this->board[i][j+3];
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



	//pionowe

	for (int i = 0; i < ROWS-3;i++) {
		for (int j = 0;j < COLS; j++) {
			temp = this->board[i][j] + this->board[i+1][j] + this->board[i+2][j] + this->board[i+3][j];
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

	//ukosne plus

	for (int i = 0; i < ROWS - 3;i++) {
		for (int j = 0;j < COLS - 3; j++) {
			temp = this->board[i][j] + this->board[i + 1][j + 1] + this->board[i + 2][j + 2] + this->board[i + 3][j + 3];
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

	//ukosne minus

	for (int i = 0; i < ROWS - 3; i++) {
		for (int j = COLS;j >= 3; j--) {
			temp = this->board[i][j] + this->board[i + 1][j - 1] + this->board[i + 2][j - 2] + this->board[i + 3][j - 3];
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


	if (this->is_fully_expanded()) {
		return 0;
	}

	return temp;
}

bool Board::is_fully_expanded() {

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (this->board[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool Board::is_terminal_state() {
	if (this->outcome() == 1 || this->outcome() == -1 || this->outcome() == 0) return true;
	else return false;
}

void Board::reset() {
	this->initBoard(); // reset to all-zeros
	this->_who_to_play = 1;
}

void Board::initBoard() {

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			this->board[i][j] = 0;
		}
	}
}


