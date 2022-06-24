#pragma once
#include "definies.h"



class Board
{

public:
	Board(); // constructor
	Board(int who_to_play); // constructor
	Board(const Board& b); // constructor for deepcopy
	vector<int> generate_legal_moves();
	void print(); // print current board position
	void make_move(int move); 
	bool is_move_legal(int move);
	int who_to_play();
	int outcome(); // return 1 means first player won, -1 - opposite player won, 2 means not terminal state, 0 means draw
	bool is_fully_expanded();
	bool is_terminal_state();
	void reset();
	void flip();
	

private:
	int board[ROWS][COLS];
	void initBoard(); // init board 2d array with zeros
	int x = 1; // first player
	int o = -1; // second player
	int _who_to_play = 1; // matches player x and o int states
	

};

