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
	MCTSAgent mcts_agent_1(1000, 50); // pass depth of evaluation and c_param in ucb1
	


	float score = 0, tmp;
	int iter = 100;


	bool display = true;
	Env env(h1, mcts_agent_1, b, display);





	for (int i = 0;i < iter;i++) {
		tmp = env.play();
		score += tmp;
		env.resetBoard();
		cout << i << endl;
	}

	cout << "avg score: " << score / iter << endl;
	
	

	return 0;
}