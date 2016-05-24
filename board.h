//
//  board.h
//  tictactoe3
//  COP4530
//  Yoshitaka Meguro
//
//

#pragma once

#include <vector>
#include <iostream>
#include <string>
using namespace std;

// board values for each situation
const int DRAW = -1;
const int ZERO = 0;
const int X = 1;
const int O = 2;

class Board {
public:
    void init(int size);                // Initializes the board
    void reset();                       // resets the board
    void displayBoard() const;          // display the board
    int winner() const;                 // checks if there is a winner
    void setVal(int col, int row, int val)  // Sets value at column, row, and spot
    {
        _board[row * _size + col] = val;
    }
    int getVal(int col, int row) const  // gets value at column, row, and spot
    {
        return _board[row * _size + col];
    }
    int getSize() const                 // get the size of the board
    {
        return _size;
    }

private:
    void boardLine(string& L) const;   // lines for the board
    vector<int> _board;
    int _size;
};


// board display
const char pos[3][3][3] = {
    {
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' }
    },
    {
        { ' ', ' ', ' ' },
        { ' ', 'X', ' ' },
        { ' ', ' ', ' ' }
    },
    {
        { ' ', ' ', ' ' },
        { ' ', 'O', ' ' },
        { ' ', ' ', ' ' }
    }
};


void Board::init(int size) {
    
    if (size > 9) size = 9;
    _size = size;
    
    _board.resize(size * size);
    
    reset();                    // reset the used board
}


void Board::reset() {
    for (int i = 0; i < _board.size(); i++) {
        _board[i] = ZERO;
    }
}

void Board::displayBoard() const {
    
    string boardFrame;
    boardFrame.reserve(_size * _size * 4);
    
    for (int row = 0; row < _size; row++) {
        boardLine(boardFrame);
        for (int posRow = 0; posRow < 3; posRow++) {
            if (posRow == 1) {
                boardFrame += " ";
            } else {
                boardFrame += " ";
            }
            for (int col = 0; col < _size; col++) {
                boardFrame += "|";
                for (int posCol = 0; posCol < 3; posCol++) {
                    boardFrame += pos[getVal(col, row)][posRow][posCol];
                }
            }
            boardFrame += "|";
            if (posRow == 1) {
                boardFrame += "\n";
            } else {
                boardFrame += "\n";
            }
        }
    }
    boardLine(boardFrame);
    printf("%s\n", boardFrame.c_str());
}

// cheking winning cases
int Board::winner() const {
    bool win;
    int winCase;
    
    // rows
    for (int row = 0; row < _size; row++) {
        winCase = getVal(0, row);
        if (winCase != ZERO) {
            win = true;
            for (int col = 0; col < _size; col++) {
                if (getVal(col, row) != winCase) {
                    win = false;
                    break;
                }
            }
            if (win) return winCase;
        }
    }
    
    // columns
    for (int col = 0; col < _size; col++) {
        winCase = getVal(col, 0);
        if (winCase != ZERO) {
            win = true;
            for (int row = 0; row < _size; row++) {
                if (getVal(col, row) != winCase) {
                    win = false;
                    break;
                }
            }
            if (win) return winCase;
        }
    }
    
    // left diagonal
    winCase = getVal(0, 0);
    if (winCase != ZERO) {
        win = true;
        for (int ld = 0; ld < _size; ld++) {
            if (getVal(ld, ld) != winCase) {
                win = false;
                break;
            }
        }
        if (win) return winCase;
    }
    
    // right diagonal
    winCase = getVal(_size - 1, 0);
    if (winCase != ZERO) {
        win = true;
        for (int rd = 0; rd < _size; rd++) {
            if (getVal(_size - rd - 1, rd) != winCase) {
                win = false;
                break;
            }
        }
        if (win) return winCase;
    }
    
    for (int i = 0; i < _board.size(); i++) {
        if (_board[i] == ZERO) return ZERO;
    }
    // draw
    return DRAW;
}

void Board::boardLine(string& L) const {
    L += "-";
    for (int x = 0; x < _size; x++) {
        L += "----";
    }
    L += "--\n";
}


