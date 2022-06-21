#pragma once
#include "definies.h"
#include "board.h"
#include "agent.h"


using namespace std;

class Env
{
public:
	Env();
	Env(Agent& agent1, Agent& agent2, bool display); // start with empty board
	Env(Agent& agent1, Agent& agent2, Board& board, bool display); // we can continue game from given position
	Board accessBoard();
	int play(); // returns outcome, 1-first player won, -1 - opposite player, 0 means draw
	void resetBoard();
	bool diplay = false;

private:

	Agent* agent1;
	Agent* agent2;
	Board* board;


};
