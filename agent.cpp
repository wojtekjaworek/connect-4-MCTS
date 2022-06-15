#include "agent.h"
#include "definies.h"

Agent::Agent() {

}

int Agent::pick_move() {
	cout << "Should not be here!" << endl;
	return 0;
}

Random::Random() {
}

int Random::pick_move() {

	return rand() % COLS;
}

Human::Human() {

}

int Human::pick_move() {

	int move = -1;
	cout << "Enter your move: (counting from 0) " << endl;
	cin >> move;

	return move;
}
