#include <iostream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

// ANSI escape sequences for color formatting
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

using namespace std;

char currentPlayerSymbol = 'X';
bool finishGame = false;
vector<char> ticTacToeBoard(9, ' ');
vector<char> connect4Board(42, ' ');

bool checkIsWinnerTicTacToe() {
    // Check rows
    for (int i = 0; i <= 6; i += 3) {
        if (ticTacToeBoard[i] != ' ' && ticTacToeBoard[i] == ticTacToeBoard[i + 1] && ticTacToeBoard[i + 1] == ticTacToeBoard[i + 2])
            return true;
    }

    // Check columns
    for (int i = 0; i <= 2; ++i) {
        if (ticTacToeBoard[i] != ' ' && ticTacToeBoard[i] == ticTacToeBoard[i + 3] && ticTacToeBoard[i + 3] == ticTacToeBoard[i + 6])
            return true;
    }

    // Check diagonals
    if ((ticTacToeBoard[0] != ' ' && ticTacToeBoard[0] == ticTacToeBoard[4] && ticTacToeBoard[4] == ticTacToeBoard[8]) ||
        (ticTacToeBoard[2] != ' ' && ticTacToeBoard[2] == ticTacToeBoard[4] && ticTacToeBoard[4] == ticTacToeBoard[6]))
        return true;

    return false;
}

bool checkIsWinnerConnect4() {
    // Check horizontal
    for (int i = 0; i <= 20; i += 7) {
        for (int j = i; j <= i + 3; ++j) {
            if (connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 1] && connect4Board[j + 1] == connect4Board[j + 2] && connect4Board[j + 2] == connect4Board[j + 3])
                return true;
        }
    }

    // Check vertical
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= i + 14; j += 7) {
            if (connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 7] && connect4Board[j + 7] == connect4Board[j + 14] && connect4Board[j + 14] == connect4Board[j + 21])
                return true;
        }
    }

    // Check diagonal (top left to bottom right)
    for (int i = 0; i <= 20; i += 7) {
        for (int j = i; j <= i + 3; ++j) {
            if (j + 24 < 42 && connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 8] && connect4Board[j + 8] == connect4Board[j + 16] && connect4Board[j + 16] == connect4Board[j + 24])
                return true;
        }
    }

    // Check diagonal (top right to bottom left)
    for (int i = 3; i <= 23; i += 7) {
        for (int j = i; j <= i + 3; ++j) {
            if (j + 18 < 42 && connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 6] && connect4Board[j + 6] == connect4Board[j + 12] && connect4Board[j + 12] == connect4Board[j + 18])
                return true;
        }
    }

    return false;
}

void printTicTacToeBoard() {
    system(CLEAR_COMMAND);
    cout << YELLOW << "-------------" << RESET << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << YELLOW << "| " << RESET;
        if (ticTacToeBoard[i] == 'X')
            cout << RED << ticTacToeBoard[i] << RESET;
        else if (ticTacToeBoard[i] == 'O')
            cout << BLUE << ticTacToeBoard[i] << RESET;
        else
            cout << ticTacToeBoard[i];
        cout << YELLOW << " | " << RESET;
        if (ticTacToeBoard[i + 1] == 'X')
            cout << RED << ticTacToeBoard[i + 1] << RESET;
        else if (ticTacToeBoard[i + 1] == 'O')
            cout << BLUE << ticTacToeBoard[i + 1] << RESET;
        else
            cout << ticTacToeBoard[i + 1];
        cout << YELLOW << " | " << RESET;
        if (ticTacToeBoard[i + 2] == 'X')
            cout << RED << ticTacToeBoard[i + 2] << RESET;
        else if (ticTacToeBoard[i + 2] == 'O')
            cout << BLUE << ticTacToeBoard[i + 2] << RESET;
        else
            cout << ticTacToeBoard[i + 2];
        cout << YELLOW << " |" << RESET << endl;
        cout << YELLOW << "-------------" << RESET << endl;
    }
}

void printConnect4Board() {
    system(CLEAR_COMMAND);
    cout << YELLOW << "-----------------------------" << RESET << endl;
    for (int i = 0; i < 42; i += 7) {
        cout << YELLOW << "| " << RESET;
        for (int j = i; j < i + 7; ++j) {
            if (connect4Board[j] == 'X')
                cout << RED << connect4Board[j] << RESET;
            else if (connect4Board[j] == 'O')
                cout << BLUE << connect4Board[j] << RESET;
            else
                cout << connect4Board[j];
            cout << YELLOW << " | " << RESET;
        }
        cout << endl;
        cout << YELLOW << "-----------------------------" << RESET << endl;
    }
}

void playTicTacToe(int position) {
    if (ticTacToeBoard[position] != ' ' || finishGame)
        return;

    ticTacToeBoard[position] = currentPlayerSymbol;
    printTicTacToeBoard();

    if (checkIsWinnerTicTacToe()) {
        cout << GREEN << "Player " << currentPlayerSymbol << " wins!" << RESET << endl;
        finishGame = true;
        return;
    } else if (count(ticTacToeBoard.begin(), ticTacToeBoard.end(), ' ') == 0) {
        cout << CYAN << "It's a draw!" << RESET << endl;
        finishGame = true;
        return;
    }

    currentPlayerSymbol = (currentPlayerSymbol == 'X') ? 'O' : 'X';
}

void playConnect4(int column) {
    if (finishGame)
        return;

    for (int i = column + 35; i >= column; i -= 7) {
        if (connect4Board[i] == ' ') {
            connect4Board[i] = currentPlayerSymbol;
            break;
        }
    }

    printConnect4Board();

    if (checkIsWinnerConnect4()) {
        cout << GREEN << "Player " << currentPlayerSymbol << " wins!" << RESET << endl;
        finishGame = true;
        return;
    } else if (count(connect4Board.begin(), connect4Board.end(), ' ') == 0) {
        cout << CYAN << "It's a draw!" << RESET << endl;
        finishGame = true;
        return;
    }

    currentPlayerSymbol = (currentPlayerSymbol == 'X') ? 'O' : 'X';
}

int main() {
    int gameOption;
    int position;
    int column;

    cout << "Welcome to the Game Center!" << endl;
    cout << "Select a game to play:" << endl;
    cout << "1. Tic Tac Toe" << endl;
    cout << "2. Connect 4" << endl;
    cout << "Enter your choice (1-2): ";
    cin >> gameOption;

    if (gameOption == 1) {
        cout << "Tic Tac Toe Game" << endl;
        cout << "Player X starts the game." << endl;

        while (!finishGame) {
            cout << "Current Player: ";
            if (currentPlayerSymbol == 'X')
                cout << RED << currentPlayerSymbol << RESET << endl;
            else
                cout << BLUE << currentPlayerSymbol << RESET << endl;

            cout << "Enter the position (0-8): ";
            cin >> position;

            if (position < 0 || position > 8) {
                cout << "Invalid position! Please try again." << endl;
                continue;
            }

            playTicTacToe(position);
        }
    } else if (gameOption == 2) {
        cout << "Connect 4 Game" << endl;
        cout << "Player X starts the game." << endl;

        while (!finishGame) {
            cout << "Current Player: ";
            if (currentPlayerSymbol == 'X')
                cout << RED << currentPlayerSymbol << RESET << endl;
            else
                cout << BLUE << currentPlayerSymbol << RESET << endl;

            cout << "Enter the column (0-6): ";
            cin >> column;

            if (column < 0 || column > 6) {
                cout << "Invalid column! Please try again." << endl;
                continue;
            }

            playConnect4(column);
        }
    } else {
        cout << "Invalid game option! Please try again." << endl;
    }

    return 0;
}

