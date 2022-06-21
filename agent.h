#pragma once
#include "definies.h"
#include "board.h"
#include "mcts.h"

class Agent {
public:
	Agent();
	virtual int pick_move(Board* b); // pick move on current board state
	

private:

};



class Random : public Agent {

public:
	Random();
	int pick_move(Board* b);



private:

};


class Human : public Agent {
public:
	Human();
	int pick_move(Board* b);

private:

};


class MCTSAgent : public Agent {
public:
	MCTSAgent(int depth); // maybe replace depth with time for single move?
	int pick_move(Board* b);

private:
	MCTS* mcts;
	int depth;

};





