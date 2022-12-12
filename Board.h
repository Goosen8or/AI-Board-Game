/*
 * Board.h
 *
 *  Created on: 25/02/2022
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int row, col;
	int player; //1 = white; -1 = black
	int **grid; // 0 = empty; other values for pip count; positive for white; negative for black

public:
	Board(int r, int c) :
			row(r), col(c) {
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
			}
		}

                       
		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board &cboard) {//Copy constructor
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j];
			}

		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if(grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	int getBoardSizeY(){
		return row;
	}

	int getBoardSizeX(){
		return col;
	}

	int getGrid(int i, int j) {
		return grid[i][j];
	}

	bool validMove(int x, int y);

	bool addMove(int player, int x, int y);

	int checkWinningStatus();

	void printBoard();

	int getBoardSize();

	int capturingPlacement(int, int);//to be implemented
    
    void removeNeighbors(vector<int> neighbors, int x, int y);
    
    int heuristics(int player);
    
    int isPositive(int num){
        if (num > 0){
            return 1;
        } else if (num < 0){
            return -1;
        }
        
        return 0;
    }
    
    vector<Cell> getEmptyPositions();
};

vector<Cell> Board::getEmptyPositions() {
    vector<Cell> emptyCells;
    for (int i = 0; i < getBoardSizeY(); i++) {
        for (int j = 0; j < getBoardSizeX(); j++) {
            if (grid[i][j] == 0){
                Cell empty(i, j, 0);
                emptyCells.push_back(empty);
            }
        }
    }

    return emptyCells;
}

int Board::heuristics(int player){

    int numOfDice = 0;
    
    for (int i = 0; i < getBoardSizeY(); i++) {
        for (int j = 0; j < getBoardSizeX(); j++) {
            
            if (isPositive(grid[i][j]) == player)
                numOfDice++;
        }
    }
    
    return numOfDice;
}

bool notZero(int i){
    {
        return i != 0;
        
    }
}

void Board::removeNeighbors(vector<int> neighbors, int x, int y){
    if (neighbors[0] != 0){
        grid[x-1][y] = 0;
    }
    if (neighbors[1] != 0){
        grid[x+1][y] = 0;
    }
    if (neighbors[2] != 0){
        grid[x][y-1] = 0;
    }
    if (neighbors[3] != 0){
        grid[x][y+1] = 0;
    }
}

int Board::capturingPlacement(int x, int y) {
	//To be implemented
    
    vector<int> neighbors(4,0);
    int neighboursUsed[4] = {0,0,0,0};
    
    if (x > 0)
        neighbors[0] = abs(grid[x-1][y]);   //UP
    if (x < row-1)
        neighbors[1] = abs(grid[x+1][y]);   //DOWN
    if (y > 0)
        neighbors[2] = abs(grid[x][y - 1]);   //LEFT
    if (y < col-1)
        neighbors[3] = abs(grid[x][y + 1]);   //RIGHT
    

    int numNeighbors = count_if(neighbors.begin(), neighbors.end(), notZero);
    int sum=0;
    
    for(int i = 0; i < 4; i++)
    {
        sum += neighbors[i];
    }
    
    if (numNeighbors < 2){
        return 1;
        
    } else if (numNeighbors == 2){
        
        if (sum <= 6){
            removeNeighbors(neighbors, x, y);
            return sum;
        } else {
            return 1;
        }
        
    } else if (numNeighbors > 2){
        if (sum <= 6){
            removeNeighbors(neighbors, x, y);
            return sum;
        } else if (sum > 6){
            int currSum = 0;
            bool changed = false;
            int n = 4;
            int maxSum = 1;
            int neighborsUsed[4] = {0,0,0,0};
            int temp[4];
              
            for (int i = 0; i < n; i++) {
                currSum = 0;
                std::fill_n(temp, 4, 0);
                if (neighbors[i] != 0){
                  currSum = neighbors[i];
                  temp[i] = 1;
                }
                else {
                  temp[i] = 0;
                  continue;
                }

                for (int j = i + 1; j < n ; j++) {
                  if (neighbors[j] != 0)
                    currSum += neighbors[j];
                  else
                    continue;
                  if (currSum >= maxSum && currSum <= 6) {
                    maxSum = currSum;
                    temp[j] = 1;
                    changed = true;
                  } else {
                    temp[j] = 0;
                    currSum = neighbors[i];
                  }
                    if (changed){
                      std::copy(std::begin(temp), std::end(temp), std::begin(neighborsUsed));
                      changed = false;
                    }
                }
              }

            vector<int> nbUsed;
              for (int i = 0; i < 4; i++){
                nbUsed.push_back(neighborsUsed[i]);
              }
            
            if (maxSum > 1)
                removeNeighbors(nbUsed, x, y);

            return maxSum;
            
        }
    }
    
    return sum;
}

int Board::checkWinningStatus() {
	if (!isBoardFull())
		return -2; //error message

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1; //white player won
	else if (counter * 2 < row * col)
		return -1; //black player won
	else
		return 0;//draw
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

bool Board::addMove(int p, int x, int y) {
	
	if (!validMove(x, y))
		return false;

	grid[x][y] = player * capturingPlacement(x, y);

	player = -1 * player;

	return true;
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

#endif /* BOARD_H_ */
