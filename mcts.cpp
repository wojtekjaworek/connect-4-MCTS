#include "mcts.h"

MCTSNode::MCTSNode(Env& env) {
	this->env = &env;
	this->parent = nullptr;
	this->parent_action = NULL;
	this->player_to_move = this->env->accessBoard().who_to_play();
	this->untried_actions = this->env->accessBoard().generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();

}

MCTSNode::MCTSNode(Env& env, MCTSNode& parent, int parent_action) {
	this->env = &env;
	this->parent = &parent;
	this->parent_action = parent_action;
	this->player_to_move = this->env->accessBoard().who_to_play();
	this->untried_actions = this->env->accessBoard().generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();


}

bool MCTSNode::check_if_fully_expanded() {
	return (untried_actions.size() == 0);
}

bool MCTSNode::check_if_terminal_state() {
	return this->env->accessBoard().is_terminal_state();
}

void MCTSNode::print() {
	cout << endl;
	cout << "               Node: " << &*this << endl;
	cout << "                Env: " << env << endl;
	cout << "          Env board: " << endl;
	this->env->accessBoard().print();
	cout << "     Player to move: " << this->player_to_move << endl;
	cout << "             Parent: " << this->parent << endl;
	cout << "      Parent action: " << this->parent_action << endl;
	cout << "    Untried actions: " << &this->untried_actions << endl;
	cout << "Is fully expanded? : " << this->_is_fully_expanded << endl;
	cout << " Is teminal state? : " << this->_is_terminal_state << endl;
	cout << "             visits: " << this->visits << endl;
	cout << "              score: " << this->score << endl;

}

/*

	from now on defs for MCTS class (not MCTSNode)
*/

MCTS::MCTS(Env env, int player_to_move, int depth) {
	this->env = env;
	this->depth = depth;
	this->player_to_move = player_to_move;
}

void MCTS::search() {

	MCTSNode root(this->env); // create root without parent nor parent_action
	
	for (int i = 0; i < this->depth; i++) {
		MCTSNode node = this->selection(root);
	}



}


MCTSNode MCTS::selection(MCTSNode& node) {

	while (node._is_terminal_state == false) {
		if (node._is_fully_expanded == false) {
			return this->expansion(node);
		}
		else {
			node = this->ucb1(node);
		}
	}
	return node;

}



MCTSNode MCTS::expansion(MCTSNode& node) {

	int action = node.untried_actions.back();
	Env new_env = node.env;
	new_env.accessBoard().make_move(action);
	MCTSNode child_node(new_env, node, action);
	node.children.push_back(&child_node);
	node._is_fully_expanded = node.check_if_fully_expanded();
	
	return child_node;
}

MCTSNode MCTS::ucb1(MCTSNode& node) {
	return node;
}