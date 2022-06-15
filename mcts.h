#pragma once
#include "definies.h"
#include "env.h"
#include "board.h"
#include "agent.h"


class MCTSNode { 
	/*
	MCTS graph node has properties:
		- 
	*/

public:
	friend class MCTS;
	MCTSNode(Env& env); // for init purposes, without epecifying parent 
	MCTSNode(Env& env, MCTSNode& parent, int parent_action);
	void print();
private:
	Env* env;
	Board* board; // might not be necessary to use this
	// here to put parent node
	MCTSNode* parent = nullptr;
	int action;
	int parent_action;
	int player_to_move; // get from Env
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
	MCTS(Env env, int player_to_move, int depth);
	void search();



private:
	int player_to_move = 1;
	Env env;
	int depth = 100;

	MCTSNode selection(MCTSNode& node);
	MCTSNode expansion(MCTSNode& node);
	void rollout();
	void backpropagate();
	MCTSNode ucb1(MCTSNode node);



};

























