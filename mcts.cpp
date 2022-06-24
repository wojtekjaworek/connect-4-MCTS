#include "mcts.h"

MCTSNode::MCTSNode(Board board) {
	this->board = board;
	this->parent = nullptr;
	this->parent_action = NULL;
	this->player_to_move = this->board.who_to_play();
	this->untried_actions = this->board.generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();

}

MCTSNode::MCTSNode(Board board, MCTSNode* parent, int parent_action) {
	this->board = board;
	this->parent = parent;
	this->parent_action = parent_action;
	this->player_to_move = this->board.who_to_play();
	this->untried_actions = this->board.generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();


}

MCTSNode::MCTSNode(const MCTSNode& n) { // deepcopy n
	this->board = n.board;
	this->parent = n.parent;
	this->parent_action = n.parent_action;
	this->player_to_move = n.player_to_move;
	this->untried_actions = n.untried_actions;
	this->_is_fully_expanded = n._is_fully_expanded;
	this->_is_terminal_state = n._is_terminal_state;
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
	return this->board.is_terminal_state();
}




MCTSNode& MCTSNode::operator=(const MCTSNode& n) {
	this->board = n.board;
	this->parent = n.parent;
	this->parent_action = n.parent_action;
	this->player_to_move = this->board.who_to_play();
	this->untried_actions = this->board.generate_legal_moves();
	this->_is_fully_expanded = this->check_if_fully_expanded();
	this->_is_terminal_state = this->check_if_terminal_state();
	this->visits = n.visits;
	this->score = score;
	this->ucb1 = n.ucb1;
	this->untried_actions = n.untried_actions;
	this->children = n.children;

	return *this;
}



void MCTSNode::print() {
	cout << endl;
	cout << "               Node: " << &*this << endl;
	cout << "              Board: " << &board << endl;
	cout << "        Board state: " << endl;
	this->board.print();
	cout << "     Player to move: " << this->player_to_move << endl;
	cout << "             Parent: " << this->parent << endl;
	cout << "      Parent action: " << this->parent_action << endl;
	cout << "    Untried actions: " << this->untried_actions.size() << endl;
	cout << "Is fully expanded? : " << this->_is_fully_expanded << endl;
	cout << " Is teminal state? : " << this->_is_terminal_state << endl;
	cout << "             visits: " << this->visits << endl;
	cout << "              score: " << this->score << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

}

/*

	from now on defs for MCTS class (not MCTSNode)
*/

MCTS::MCTS(double c_param) {
	this->c_param = c_param;
	
}

int MCTS::search(Board board, int depth) {
	this->_how_deep = 0;
	this->all_nodes.clear();


	if (board.who_to_play() == -1) {
		// multiply board by -1 and change who to play to opposite
		// due to algorithm we cannot just pick move with lowest score for -1 player
		board.flip();
		this->board = board;
		this->depth = depth;
		this->player_to_move = board.who_to_play();
	}

	this->board = board;
	this->depth = depth;
	this->player_to_move = board.who_to_play();

	MCTSNode* root = new MCTSNode(this->board);
	this->all_nodes.push_back(root);

	for (int i = 0; i < this->depth; i++) {
		MCTSNode* node = this->selection(root);
		int score = this->rollout(node);
		this->backpropagate(node, score);

	}

	//printing parent tree
	/*
	cout << "print parent " << endl;
	this->print_tree(root, 1);
	*/

	//printing root children with  info
	
	int aa = 0;
	for (auto& child : root->children) {
		cout << " Child: " << aa;
		cout << " Parent action: " << child->parent_action;
		cout << " visits: " << child->visits;
		cout << " score: " << child->score << endl;

		aa++;
	}
	_getch();

	return this->most_scoring_node(root)->parent_action;
	//return this->most_visited_node(root)->parent_action;
}


void MCTS::print_tree(MCTSNode* node, int r) {

	for (int i = 0;i < r;i++) {
		cout << "\t";
	}

	cout << "node: " << node << " parent: " << node->parent <<  endl;
	cout << endl;
	r++;



	if (node->children.size() != 0) {
		for (auto& child : node->children) {
			this->print_tree(child, r);
		}
	}

}

MCTSNode* MCTS::most_visited_node(MCTSNode* node) {

	vector<MCTSNode*> temp;
	temp.clear();
	int temp_visits = 0;

	for (auto& child : node->children) {
		if (child->visits > temp_visits) {
			temp_visits = child->visits;
			temp.clear();
			temp.push_back(child);
		}
		else if (child->visits == temp_visits) {
			temp.push_back(child);

		}
	}

	int random_index = rand() % temp.size();

	return temp[random_index];
}

MCTSNode* MCTS::most_scoring_node(MCTSNode* node) {

	vector<MCTSNode*> temp;
	temp.clear();
	int temp_score = -999999;

	for (auto& child : node->children) {
		if (child->score > temp_score) {
			temp_score = child->score;
			temp.clear();
			temp.push_back(child);
		}
		else if (child->score == temp_score) {
			temp.push_back(child);

		}
	}
	if (temp.size() == 0) {
		
		for (auto& child : node->children) {
			child->print();
			cout << endl;
			cout << endl;
		}

		exit(-100);
	}
	int random_index = rand() % temp.size();
	
	return temp[random_index];
}



MCTSNode* MCTS::selection(MCTSNode* node) {
	this->_how_deep = 1;

	while (node->_is_terminal_state == false) {
		if (node->_is_fully_expanded == false) {
			return this->expansion(node);
		}
		else {
			node = this->ucb1(node);
			this->_how_deep++;
		}
	}
	this->_how_deep++; // once more because we just selected another node, counting root as deep=0;
	return node;
}

MCTSNode* MCTS::expansion(MCTSNode* node) {



	int action = node->untried_actions.back(); // get last element
	node->untried_actions.pop_back(); // remove this element as it is now 'tried' action
	Board new_board(node->board);
	new_board.make_move(action);
	MCTSNode* child_node = new MCTSNode(new_board, node, action);
	node->children.push_back(child_node);
	node->_is_fully_expanded = node->check_if_fully_expanded();

	this->all_nodes.push_back(child_node);

	return child_node;
}

int MCTS::rollout(MCTSNode* node) {

	Board rollout_board(node->board);
	while (!rollout_board.is_terminal_state()) {
		vector<int> untried = rollout_board.generate_legal_moves();

		int random_index = rand() % untried.size();

		int action = untried[random_index];
		untried.erase(untried.begin() + random_index);
		rollout_board.make_move(action);
		untried.clear();
	} 
	return rollout_board.outcome();

}

void MCTS::backpropagate(MCTSNode* node, double score) {
	node->visits++;

	node->score += score;

	if (node->parent != nullptr) {
		this->backpropagate(node->parent, score);
	}

}

MCTSNode* MCTS::ucb1(MCTSNode* node) {

	vector<MCTSNode*> best_moves; 
	best_moves.clear();
	double best_score = -999999;
	double c_param = this->c_param;
	double move_score;

	for (auto& child : node->children) {
		move_score = child->score / child->visits + c_param * sqrt(log(node->visits)/child->visits);

		if (move_score > best_score) {
			best_score = move_score;
			best_moves.clear();
			best_moves.push_back(child);
		}
		else if (move_score == best_score) {
			best_moves.push_back(child);
		}

	}
	int random_index;
	if (best_moves.size() != 0) {
		random_index = rand() % best_moves.size();
	}
	else {
		random_index = 0;
		cout << "else" << endl;
	}

	return best_moves[random_index];
}



