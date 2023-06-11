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
vector<char> board(9, ' ');

bool checkIsWinner() {
    // Check rows
    for (int i = 0; i <= 6; i += 3) {
        if (board[i] != ' ' && board[i] == board[i + 1] && board[i + 1] == board[i + 2])
            return true;
    }

    // Check columns
    for (int i = 0; i <= 2; ++i) {
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6])
            return true;
    }

    // Check diagonals
    if ((board[0] != ' ' && board[0] == board[4] && board[4] == board[8]) ||
        (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]))
        return true;

    return false;
}

void printBoard() {
    system(CLEAR_COMMAND);
    cout << YELLOW << "-------------" << RESET << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << YELLOW << "| " << RESET;
        if (board[i] == 'X')
            cout << RED << board[i] << RESET;
        else if (board[i] == 'O')
            cout << BLUE << board[i] << RESET;
        else
            cout << board[i];
        cout << YELLOW << " | " << RESET;
        if (board[i + 1] == 'X')
            cout << RED << board[i + 1] << RESET;
        else if (board[i + 1] == 'O')
            cout << BLUE << board[i + 1] << RESET;
        else
            cout << board[i + 1];
        cout << YELLOW << " | " << RESET;
        if (board[i + 2] == 'X')
            cout << RED << board[i + 2] << RESET;
        else if (board[i + 2] == 'O')
            cout << BLUE << board[i + 2] << RESET;
        else
            cout << board[i + 2];
        cout << YELLOW << " |" << RESET << endl;
        cout << YELLOW << "-------------" << RESET << endl;
    }
}

void play(int position) {
    if (board[position] != ' ' || finishGame)
        return;

    board[position] = currentPlayerSymbol;
    printBoard();

    if (checkIsWinner()) {
        cout << GREEN << "Player " << currentPlayerSymbol << " wins!" << RESET << endl;
        finishGame = true;
        return;
    } else if (count(board.begin(), board.end(), ' ') == 0) {
        cout << CYAN << "It's a draw!" << RESET << endl;
        finishGame = true;
        return;
    }

    currentPlayerSymbol = (currentPlayerSymbol == 'X') ? 'O' : 'X';
}

int main() {
    int position;

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

        play(position);
    }

    return 0;
}

