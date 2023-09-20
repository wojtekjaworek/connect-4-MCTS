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
	MCTSAgent mcts_agent_1(500000, 50); // pass depth of evaluation and c_param in ucb1
	MCTSAgent mcts_agent_2(10000, 50); // pass depth of evaluation and c_param in ucb1



	float score = 0, tmp, win1=0, win2=0, draw=0;
	int iter = 100;


	bool display = true;
	Env env(mcts_agent_1, h1, b, display);





	for (int i = 0;i < iter;i++) {
		tmp = env.play();
		if (tmp == 1) {
			win1++;
		}
		else if (tmp == -1) {
			win2++;
		}
		else {
			draw++;
		}
		score += tmp;
		if (display) {
			cout << "Gra zakonczona! " << (tmp == 1 ? "wygral gracz pierwszy" : (tmp == -1 ? "wygral gracz drugi" : "remis"));
			cout << "Nacisnij enter" << endl;
			_getch();
		}
		env.resetBoard();
		system("cls");
		cout << i << endl;
		//cout << "win1: " << win1 << " win2: " << win2 << " draw: " << draw << endl;
	}

	cout << "win1: " << win1 << " win2: " << win2 << " draw: " << draw << endl;
	cout << "avg score: " << score / iter << endl;
	
	

	return 0;
}