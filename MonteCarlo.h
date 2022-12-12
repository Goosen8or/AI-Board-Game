//
//  MonteCarlo.h
//  Ass1
//
//  Created by Kyle Goosen on 18/4/2022.
//

#ifndef MonteCarlo_h
#define MonteCarlo_h

class MonteCarloPlayer : public Player {
    int playerSymbol;
private:
    int simulationNum;
public:
    MonteCarloPlayer(int ps) : Player("Monte Carlo", ps) {
        cout << "Please enter simulation number (recommended min. 100):";
        cin >> simulationNum;
        playerSymbol = ps;
    }

    void getMove(Board board, int& x, int& y) {

        vector<Cell> emptyCells =board.getEmptyPositions();

        if (emptyCells.empty())
            return;

        double maxUtility = -1.0;

        for (int index = 0; index < emptyCells.size(); index++) {
            int i = emptyCells[index].x;
            int j = emptyCells[index].y;
            Board tempBoard(board);
            tempBoard.addMove(playerSymbol, i, j);

            double utility = simulation(tempBoard);

            if (utility > maxUtility) {
                maxUtility = utility;
                x = i;
                y = j;
            }
        }

        cout << "Monte Carlo Utility = " << maxUtility  << endl;

        return;
    }

    double simulation(Board board) {
        double winning = 0.0;

        for (int i = 0; i < simulationNum; i++) {
            Board tempBoard(board);
            winning += expansion((playerSymbol == 1) ? -1 : 1, tempBoard);
        }

        return winning/simulationNum;
    }



    double expansion(int player, Board temp) {
        
        int gameStatus = temp.checkWinningStatus();
        if (gameStatus != -2) {
            if ( gameStatus == playerSymbol)
                return  1; //score 1 if wins
            else if (gameStatus == 0)
                return 0; //score 0 if tie
            else
                return -1; //score -1 if lose
        }
        
        vector<Cell> emptyCells = temp.getEmptyPositions();

        int index = rand() % emptyCells.size();

        int x = emptyCells[index].x;
        int y = emptyCells[index].y;

        temp.addMove(player, x, y);

        player = (player == 1) ? -1 : 1;

        return expansion(player, temp);
    }

};
#endif /* MonteCarlo_h */
