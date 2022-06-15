#include "env.h"
#include "definies.h"

Env::Env() {
}

Env::Env(Agent& agent1, Agent& agent2) {
	this->agent1 = &agent1;
	this->agent2 = &agent2;
	this->board = new Board;
}

Env::Env(Agent& agent1, Agent& agent2, Board& board) {

	this->agent1 = &agent1;
	this->agent2 = &agent2;
	this->board = &board;



}
Board Env::accessBoard() {
	return *this->board;
}


int Env::play() {

	while (this->board->outcome() == 2) {
		

		if (this->board->who_to_play() == 1) {

			int a1 = this->agent1->pick_move();
			while (!this->board->is_move_legal(a1)) { // only legal move
				a1 = this->agent1->pick_move();
			}
			this->board->make_move(a1);

			if (this->diplay == true) {
				system("cls");
				cout << "agent1 move: " << a1 << endl;
				cout << "current state: " << endl;
				this->board->print();
			}
		}


		else if (this->board->who_to_play() == -1) {
			
			int a2 = this->agent2->pick_move();
			while (!this->board->is_move_legal(a2)) { // only legal move
				a2 = this->agent2->pick_move();
			}
			this->board->make_move(a2);

			if (this->diplay == true) {
				system("cls");
				cout << "agent2 move: " << a2 << endl;
				cout << "current state: " << endl;
				this->board->print();
			}
		}

	} 

	if (this->board->outcome() == 1 || this->board->outcome() == -1 || this->board->outcome() == 0) {
		return this->board->outcome();
	}
}

void Env::resetBoard() {
	this->board->reset();
}

