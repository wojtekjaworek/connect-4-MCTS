#pragma once
#include "definies.h"
#include "board.h"


class MCTSNode { 
	/*
	MCTS graph node has properties:
		- 
	*/

public:
	friend class MCTS;
	MCTSNode(Board board); // for init purposes, without epecifying parent 
	MCTSNode(Board board, MCTSNode* parent, int parent_action);
	MCTSNode(const MCTSNode& n); // deepcopy constructor
	MCTSNode& operator=(const MCTSNode& n);
	void print();

private:
	Board board; // might not be necessary to use this
	// here to put parent node
	MCTSNode* parent = nullptr;
	int action;
	int parent_action;
	int player_to_move; // get from board
	int visits = 0;
	int score = 0;
	double ucb1 = 0;
	vector<int> untried_actions; // generate legal moves
	vector<MCTSNode*> children;
	bool _is_fully_expanded; // check if current state had developed all possible continuations
	bool _is_terminal_state;

	bool check_if_fully_expanded();

	bool check_if_terminal_state();

	
};


class MCTS{
	/*
	given root calculate mcts method for given board state

	*/

public:
	friend class MCTSNode;
	MCTS(double c_param); // c_param to adjust ucb1 algorithm 
	int search(Board board, int depth); // return best move in current position according to MCTS evaluation in given depth




private:
	int player_to_move = 1;
	Board board;
	int depth = 100;
	int _how_deep = 1; // how deep did the tree went
	double c_param = 1;

	vector<MCTSNode*> all_nodes;

	MCTSNode* selection(MCTSNode* node);
	MCTSNode* expansion(MCTSNode* node);
	int rollout(MCTSNode* node);
	void backpropagate(MCTSNode* node, double score);
	MCTSNode* ucb1(MCTSNode* node);
	void print_tree(MCTSNode* node, int r);
	MCTSNode* most_visited_node(MCTSNode* node); // pass parent node as an agrument and it returns child with most visits
	MCTSNode* most_scoring_node(MCTSNode* node); // pass parent node as an agrument and it returns child with most visits


};

























