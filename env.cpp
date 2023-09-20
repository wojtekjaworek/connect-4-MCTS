#include "env.h"

Env::Env() {
	this->agent1 = nullptr;
	this->agent2 = nullptr;
	this->board = nullptr;
}

Env::Env(Agent& agent1, Agent& agent2, bool display) {
	this->agent1 = &agent1;
	this->agent2 = &agent2;
	this->board = new Board;
	this->display = display;
}

Env::Env(Agent& agent1, Agent& agent2, Board& board, bool display) {

	this->agent1 = &agent1;
	this->agent2 = &agent2;
	this->board = &board;
	this->display = display;




}
Board Env::accessBoard() {
	return *board;
}


int Env::play() {

	if (display) {
		cout << "current state: " << endl;
		board->print();
	}

	while (board->outcome() == 2) {
		

		if (board->who_to_play() == 1) {

			int a1 = agent1->pick_move(board);
			while (!board->is_move_legal(a1)) { // only legal move
				a1 = agent1->pick_move(board);
			}
			board->make_move(a1);

			if (display) {
				system("cls");
				cout << "agent1 move: " << a1 << endl;
				cout << "current state: " << endl;
				board->print();
			}
		}


		else if (board->who_to_play() == -1) {
			
			int a2 = agent2->pick_move(board);
			while (!board->is_move_legal(a2)) { // only legal move
				a2 = agent2->pick_move(board);
			}
			board->make_move(a2);

			if (display) {
				system("cls");
				cout << "agent2 move: " << a2 << endl;
				cout << "current state: " << endl;
				board->print();
			}
		}

	} 

	if (board->outcome() == 1 || board->outcome() == -1 || board->outcome() == 0) {
		return board->outcome();
	}
}

void Env::resetBoard() {
	board->reset();
}

