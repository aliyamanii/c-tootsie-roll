#include <iostream>
#include <vector>
#include <algorithm>

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
    cout << "-------------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << endl;
        cout << "-------------" << endl;
    }
}

void play(int position) {
    if (board[position] != ' ' || finishGame)
        return;

    board[position] = currentPlayerSymbol;
    printBoard();

    if (checkIsWinner()) {
        cout << "Player " << currentPlayerSymbol << " wins!" << endl;
        finishGame = true;
        return;
    } else if (count(board.begin(), board.end(), ' ') == 0) {
        cout << "It's a draw!" << endl;
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
        cout << "Current Player: " << currentPlayerSymbol << endl;
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

