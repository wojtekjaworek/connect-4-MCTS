#include "board.h"
#include "agent.h"
#include "env.h"
#include "mcts.h"
#include "definies.h"



int main() {
	srand(time(NULL));

	Board b;
	Random r1;
	Random r2;
	Human h1;
	Human h2;
	MCTSAgent mcts_agent_1(1000); // pass depth of evaluation


	float score = 0, tmp;
	int iter = 1000;


	bool display = false;
	Env env(mcts_agent_1, r2, b, display); // match between mcts depth 100 and random





	for (int i = 0;i < iter;i++) {
		tmp = env.play();
		score += tmp;
		env.resetBoard();
		cout << i << endl;
	}

	cout << "avg score: " << score / iter << endl;
	
	

	return 0;
}