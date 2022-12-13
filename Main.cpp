

#include<iostream>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>
#include <numeric>
#include <cstdlib>

using namespace std;

#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGame.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "ComputerPlayer.h"
#include "MiniMaxPlayer.h"
#include "MonteCarlo.h"

int main() {
	srand(time(0));
	cout << "Example solution for high distinction level" << endl;

	Player *players[2];
    
    cout << "Choose a level to run: " << endl;
    cout << "1. Human vs human" << endl;
    cout << "2. Random player vs random player" << endl;
    cout << "3. Computer player vs random player" << endl;
    cout << "4. Random player vs Computer player" << endl;
    cout << "5. Human player vs Random Player" << endl;
    cout << "6. Human player vs Computer Player" << endl;
    cout << "7. Computer player vs Human player" << endl;
    cout << "8. Human player vs MiniMax player" << endl;
    cout << "9. Random player vs MiniMax player" << endl;
    cout << "10. Computer player vs MiniMax player" << endl;
    cout << "11. Human player vs Monte Carlo player" << endl;
    cout << "12. Random player vs Monte Carlo player" << endl;
    cout << "13. Computer player vs Monte Carlo player" << endl;


    cout << "Others: Quit" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        players[0] = new HumanPlayer(1);
        players[1] = new HumanPlayer(-1);
    } else if (choice == 2) {
        players[0] = new RandomPlayer(1);
        players[1] = new RandomPlayer(-1);
    } else if (choice == 3) {
        players[0] = new ComputerPlayer(1);
        players[1] = new ComputerPlayer(-1);
    } else if (choice == 4) {
        players[0] = new RandomPlayer(1);
        players[1] = new ComputerPlayer(-1);
    } else if (choice == 5) {
        players[0] = new HumanPlayer(1);
        players[1] = new RandomPlayer(-1);
    } else if (choice == 6) {
        players[0] = new HumanPlayer(1);
        players[1] = new ComputerPlayer(-1);
    } else if (choice == 7) {
        players[0] = new ComputerPlayer(1);
        players[1] = new HumanPlayer(-1);
    }else if (choice == 8) {
        players[0] = new HumanPlayer(1);
        players[1] = new MiniMaxPlayer(-1);
    } else if (choice == 9) {
        players[0] = new RandomPlayer(1);
        players[1] = new MiniMaxPlayer(-1);
    } else if (choice == 10) {
        players[0] = new ComputerPlayer(1);
        players[1] = new MiniMaxPlayer(-1);
    } else if (choice == 11) {
        players[0] = new HumanPlayer(1);
        players[1] = new MonteCarloPlayer(-1);
    } else if (choice == 12) {
        players[0] = new RandomPlayer(1);
        players[1] = new MonteCarloPlayer(-1);
    } else if (choice == 13) {
        players[0] = new ComputerPlayer(1);
        players[1] = new MonteCarloPlayer(-1);
    }

    else {
        return 0;
    }

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

    int row, col;
	cin >> row >> col;

	Board board(row, col);
	CephalopodGame game(board, players);
	game.play();

	delete players[0];
	delete players[1];

	return 0;
}
