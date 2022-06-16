#include "mcts.h"

MCTSNode::MCTSNode(Board& board) {
	this->board = &board;
	this->parent = nullptr;
	this->parent_action = NULL;
	this->player_to_move = this->board->who_to_play();
	this->untried_actions = this->board->generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();

}

MCTSNode::MCTSNode(Board& board, MCTSNode& parent, int parent_action) {
	this->board = &board;
	this->parent = &parent;
	this->parent_action = parent_action;
	this->player_to_move = this->board->who_to_play();
	this->untried_actions = this->board->generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();


}

MCTSNode::MCTSNode(const MCTSNode& n) { // deepcopy n
	this->board = n.board;
	this->parent = n.parent;
	this->parent_action = n.parent_action;
	this->player_to_move = this->board->who_to_play();
	this->untried_actions = this->board->generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();
	this->visits = n.visits;
	this->score = score;
	this->ucb1 = n.ucb1;
	this->untried_actions = n.untried_actions;
	this->children = n.children;
}

bool MCTSNode::check_if_fully_expanded() {
	return (untried_actions.size() == 0);
}

bool MCTSNode::check_if_terminal_state() {
	return this->board->is_terminal_state();
}

void MCTSNode::print() {
	cout << endl;
	cout << "               Node: " << &*this << endl;
	cout << "              Board: " << board << endl;
	cout << "        Board state: " << endl;
	this->board->print();
	cout << "     Player to move: " << this->player_to_move << endl;
	cout << "             Parent: " << this->parent << endl;
	cout << "      Parent action: " << this->parent_action << endl;
	cout << "    Untried actions: " << this->untried_actions.size() << endl;
	cout << "Is fully expanded? : " << this->_is_fully_expanded << endl;
	cout << " Is teminal state? : " << this->_is_terminal_state << endl;
	cout << "             visits: " << this->visits << endl;
	cout << "              score: " << this->score << endl;

}

/*

	from now on defs for MCTS class (not MCTSNode)
*/

MCTS::MCTS(Board board, int depth) {
	this->board = board;
	this->depth = depth;
	this->player_to_move = board.who_to_play();
}

void MCTS::search() {

	MCTSNode root(this->board); // create root without parent nor parent_action
	root.print();
	
	for (int i = 0; i < this->depth; i++) {
		MCTSNode node = this->selection(root);
		root.children.back().print();
	}



}


MCTSNode MCTS::selection(MCTSNode& node) {

	while (node._is_terminal_state == false) {
		if (node._is_fully_expanded == false) {
			return this->expansion(node);
		}
		else {
			node = this->ucb1(node); // tutaj sie zapetla ale jak napisze kod do ucb to sie 'samo' naprawi
		}
	}
	return node;

}



MCTSNode MCTS::expansion(MCTSNode& node) {

	int action = node.untried_actions.back(); // get last element
	node.untried_actions.pop_back(); // remove this element as it is now 'tried' action
	Board new_board(*node.board);
	cout << "at new boardd: " << &new_board << endl;
	new_board.make_move(action);
	MCTSNode child_node(new_board, node, action);
	node.children.push_back(child_node);
	node._is_fully_expanded = node.check_if_fully_expanded();

	return child_node;
}

MCTSNode MCTS::ucb1(MCTSNode& node) {
	return node;
}