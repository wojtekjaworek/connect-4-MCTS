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

	float score = 0, tmp;
	int iter = 100;

	

	Env env(r1, r2, b);

	MCTS mcts(env, 1, 10);
	mcts.search();




	for (int i = 0;i < iter;i++) {
		tmp = env.play();
		score += tmp;
		env.resetBoard();
		
	}

	cout << "avg score: " << score / iter << endl;
	
	

	return 0;
}