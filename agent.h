#pragma once
#include "definies.h"

class Agent {
public:
	Agent();
	virtual int pick_move();
	

private:
};



class Random : public Agent {

public:
	Random();
	int pick_move();



private:

};


class Human : public Agent {
public:
	Human();
	int pick_move();

private:

};

