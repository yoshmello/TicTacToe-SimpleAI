//
//  tictactoe.cpp
//  tictactoe3
//  COP4530
//  Yoshitaka Meguro
//
//

#include <iostream>
#include "computer.h"
#include "board.h"
using namespace std;

enum class GAME { PLAY, END };

class TicTacToe {
public:
    void run();             // runs tic tac toe
private:
    void init();            // Initializes the game
    void playerMove();      // live player's move
    void computerMove();    // computer's move
    void changePlayer();    // change player's turn
    void finishGame(bool draw);  // finishes the game
    Board _board;           // tic tac toe board
    int _currentPlayer;     // represents current player
    int _computerPlayer;    // represents computer player
    GAME _gameState;        // game state playing or not
    Computer _computer;     // computer
    bool _multiplayerMode;  // multiplayer mode
};


void TicTacToe::run() {
    
    // playing the game
    init();
    
    while (_gameState != GAME::END) {
        _board.displayBoard();     // display the board
        
        if (_currentPlayer == X) {
            cout << "Player X's turn!" << endl;
        } else {
            cout << "Player O's turn!" << endl;
        }
        
        // live player's move and computer's move
        if (!_multiplayerMode && _currentPlayer == _computerPlayer) {
            computerMove();
        } else {
            playerMove();
        }
        
        // Check if somebody wins
        int toWin = _board.winner();
        if (toWin != ZERO) {
            finishGame(toWin == DRAW);
        } else {
            changePlayer();
            
            for (int i = 0; i < 3; i++) {
                cout << endl;
            }
        }
    }
}

void TicTacToe::init() {
    _gameState = GAME::PLAY;
    _board.init(3);
    _currentPlayer = X;
    string playerName1;
    string playerName2;
    
    cout << "********** Welcome to Tic Tac Toe! **********" << endl;
    cout << "*                                           *" << endl;
    cout << "* Tic Tac Toe is a game in which one player *" << endl;
    cout << "* draws Xs and another player draws Os      *" << endl;
    cout << "* inside a set of nine squares and each     *" << endl;
    cout << "* player tries to be the first to fill a    *" << endl;
    cout << "* row of squares with either Xs or Os       *" << endl;
    cout << "*                                           *" << endl;
    cout << "*********************************************" << endl << endl;
    
    // select single play mode or multiplayer mode
    int inputMode;
    char inputChar = ' ';
    cout << "Single play Mode? Enter 1" << endl;
    cout << "Multiplayer Mode? Enter 2" << endl;
    cin >> inputMode;
    bool isValid;
    do {
        isValid = true;
        if (inputMode == 1) {
            _multiplayerMode = false;
        } else if (inputMode == 2) {
            _multiplayerMode = true;
            cout << endl <<"****** Multiplayer Mode ******" << endl << endl;
            cout << "Player X, what is your name?" << endl;
            cin >> playerName1;
            cout << "Player O, what is your name?" << endl;
            cin >> playerName2;
            cout << playerName1 << ", you go first!" << endl;
        } else {
            cout << "Invalid input!";
            cin.clear();
            cin.ignore(1000, '\n');
            isValid = false;
        }
    } while (isValid == false);
    
    if (!_multiplayerMode) {
        
        cout << endl << "***** Single play mode! *****" << endl;
        cout << "What is your name?" << endl;
        cin >> playerName1;
        cout << playerName1 << ", would you like to play X or O? -- X plays first, O palys after -- " << endl;
        do {
            isValid = true;
            if (!(cin >> inputChar)) {
                cout << "Invalid input!";
                cin.clear();
                cin.ignore(1000, '\n');
                isValid = false;
            } else if (inputChar == 'x' || inputChar == 'X') {
                _computerPlayer = O;
            } else if (inputChar == 'o' || inputChar == 'O') {
                _computerPlayer = X;
            } else {
                cout << "Must enter X or O!";
                isValid = false;
            }
        } while (isValid == false);
        
        // initializes computer player
        _computer.init(_computerPlayer);
    }
    cout << endl;
}

void TicTacToe::playerMove() {

    bool validInput = false;
    
    int x, y;
    do {
        cout << "Choose column: 1, 2, or 3: ";
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter 1, 2, or 3: ";
        }
        cout << "Choose row   : 1, 2, or 3: ";
        while (!(cin >> y)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter 1, 2, or 3:";
        }
        
        if (x < 1 || y < 1 || x > _board.getSize() || y > _board.getSize()) {
            cout << "Invalid input for either X or Y!" << endl;
        } else if (_board.getVal(x - 1, y - 1) != 0) {
            cout << "That spot is already taken! Choose another one." << endl;
        } else {
            validInput = true;
        }
        
    } while (!validInput);
    
    _board.setVal(x - 1, y - 1, _currentPlayer);
}

void TicTacToe::computerMove() {
    _computer.moveOfComputer(_board);
}

void TicTacToe::changePlayer() {
    if (_currentPlayer == X) {
        _currentPlayer = O;
    } else {
        _currentPlayer = X;
    }
}

void TicTacToe::finishGame(bool draw) {
    
    _board.displayBoard();
    
    if (draw) {
        cout << "*** Draw! ***" << endl << endl << "Enter any key to play again" << endl << "or enter q to quit the game" << endl;
    } else {
        if (_currentPlayer == X) {
            cout << "*** Player X wins! ***" << endl << endl << "Enter any key to play again" << endl << "or enter q to quit the game" << endl;
        } else {
            cout << "*** Player O wins! ***" << endl << endl << "Enter any key to play again" << endl << "or enter q to quit the game" << endl;
        }
    }
    
    char inputQuit;
    cin >> inputQuit;
    if (inputQuit == 'q' || inputQuit == 'Q') {
        _gameState = GAME::END;
    } else {
        // play the game again
        cout << endl;
        init();
    }
}


int main() {
    
    TicTacToe tictactoe;
    tictactoe.run();
    
    return 0;
}