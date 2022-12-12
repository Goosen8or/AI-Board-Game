#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

class RandomPlayer: public Player {
public:
	RandomPlayer(int t):Player("Random", t){}
	void getMove(Board board, int&, int&);
};

struct Coordinate {
    int xVal;
    int yVal;
    Coordinate(int paramx, double paramy) : xVal(paramx), yVal(paramy) {}
};

void RandomPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

    vector<Coordinate> emptyCells;
    int boardSizeX = board.getBoardSizeX();
    int boardSizeY = board.getBoardSizeY();
    for (int i = 0; i < boardSizeY; i++) {
      for (int j = 0; j < boardSizeX; j++) {
        if (board.getGrid(i, j) == 0)
          emptyCells.push_back(Coordinate(i,j));
      }
    }
    int index = rand() % emptyCells.size();
    x = emptyCells[index].xVal;
    y = emptyCells[index].yVal;
    return;
}

#endif /* HUMANPLAYER_H_ */
