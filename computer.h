//
//  computer.h
//  tictactoe3
//  COP4530
//  Yoshitaka Meguro
//
//

#pragma once

#include "board.h"
#include <vector>
using namespace std;

struct ComputerMove {
    ComputerMove() {};
    ComputerMove(int Score) : score(Score) {}
    int score;
    int x;
    int y;
};

class Computer {
public:
    void init(int computerPlayer);      // Initializes computer player
    void moveOfComputer(Board& board);  // computer's move
private:
    ComputerMove getBestMove(Board& board, int player);
    int _computerPlay;                  // computer
    int _livePlayer;                    // live player
};

// initializes computer's play and live player's play
void Computer::init(int computerPlayer) {
    _computerPlay = computerPlayer;
    if (_computerPlay == X) {
        _livePlayer = O;
    } else {
        _livePlayer = X;
    }
}

// computer's move
void Computer::moveOfComputer(Board& board) {
    ComputerMove bestMove = getBestMove(board, _computerPlay);
    board.setVal(bestMove.x, bestMove.y, _computerPlay);
}

// computer's best move
ComputerMove Computer::getBestMove(Board& board, int player) {
    int toWin = board.winner();
    if (toWin == _computerPlay) {
        return ComputerMove(10);
    } else if (toWin == _livePlayer) {
        return ComputerMove(-10);
    } else if (toWin == DRAW) {
        return ComputerMove(0);
    }
    
// computer's moves stored in vector
    vector<ComputerMove> moves;
    for (int y = 0; y < board.getSize(); y++) {
        for (int x = 0; x < board.getSize(); x++) {
            if (board.getVal(x, y) == ZERO) {
                ComputerMove move;
                move.x = x;
                move.y = y;
                board.setVal(x, y, player);
                if (player == _computerPlay) {
                    move.score = getBestMove(board, _livePlayer).score;
                } else {
                    move.score = getBestMove(board, _computerPlay).score;
                }
                moves.push_back(move);
                board.setVal(x, y, ZERO);
            }
        }
    }
    
// the best move for each case
    int bestMove = 0;
    if (player == _computerPlay) {
        int bestScore = -10;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score > bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    } else {
        int bestScore = 10;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score < bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    return moves[bestMove];
}
