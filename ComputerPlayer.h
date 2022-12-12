//
//  ComputerPlayer.h
//  Ass1
//
//  Created by Kyle Goosen on 16/4/2022.
//

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

class ComputerPlayer: public Player {
    int playerSymbol;
public:
    ComputerPlayer(int t):Player("Comupter", t){
        playerSymbol = t;
    }
    void getMove(Board board, int&, int&);
};

void ComputerPlayer::getMove(Board board, int& x, int& y)
{
    
        if (board.isBoardFull())
                return;

        priority_queue<Cell> moves;

        for (int i = 0; i < board.getBoardSizeY(); i++) {
            for (int j = 0; j < board.getBoardSizeX(); j++) {
                Board tempBoard(board);
                if (tempBoard.validMove(i, j)) {
                    tempBoard.addMove(playerSymbol, i, j);
                    Cell c(i, j, tempBoard.heuristics(playerSymbol));
                    moves.push(c);
                }
            }
        }
        if (moves.size() > 0) {
            x = moves.top().x;
            y = moves.top().y;
        } else {
            cout << "Can't find a new replacement" << endl;
        }
        cout << "Heuristic = " << moves.top().heuristic << " at ("
                << (x + 1) << "," << (y + 1) << ")" << endl;
    
}


#endif /* ComputerPlayer_h */
