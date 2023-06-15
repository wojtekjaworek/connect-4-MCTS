#include "agent.h"

Agent::Agent() {

}

int Agent::pick_move(Board* b) {
	cout << "Should not be here!" << endl;
	return 0;
}

Random::Random() {
}

int Random::pick_move(Board* b) {

	return rand() % COLS;
}

Human::Human() {

}

int Human::pick_move(Board* b) {

	int move = -1;
	cout << "Enter your move: (counting from 0 to 6) " << endl;
	cin >> move;

	return move;
}


MCTSAgent::MCTSAgent(int depth, double c_param) {
	this->mcts = new MCTS(c_param);
	this->depth = depth;
}

int MCTSAgent::pick_move(Board* b) {

	return this->mcts->search(*b, depth);
}

