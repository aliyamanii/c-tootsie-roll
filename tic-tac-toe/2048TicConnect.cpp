#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

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

enum class GameOption {
    TicTacToe,
    Connect4,
    Game2048
};

char currentPlayerSymbol = 'X';
bool finishGame = false;
vector<char> ticTacToeBoard(9, ' ');
vector<char> connect4Board(42, ' ');
vector<int> game2048Board(16, 0);
random_device rd;
mt19937 rng(rd());

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
    // Check rows
    for (int i = 0; i < 42; i += 7) {
        for (int j = i; j <= i + 3; ++j) {
            if (j + 3 < i + 7 && connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 1] &&
                connect4Board[j + 1] == connect4Board[j + 2] && connect4Board[j + 2] == connect4Board[j + 3])
                return true;
        }
    }

    // Check columns
    for (int i = 0; i <= 20; ++i) {
        if (connect4Board[i] != ' ' && connect4Board[i] == connect4Board[i + 7] && connect4Board[i + 7] == connect4Board[i + 14] &&
            connect4Board[i + 14] == connect4Board[i + 21])
            return true;
    }

    // Check diagonal (top left to bottom right)
    for (int i = 0; i <= 17; i += 7) {
        for (int j = i; j <= i + 3; ++j) {
            if (j + 24 < 42 && connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 8] &&
                connect4Board[j + 8] == connect4Board[j + 16] && connect4Board[j + 16] == connect4Board[j + 24])
                return true;
        }
    }

    // Check diagonal (top right to bottom left)
    for (int i = 3; i <= 20; i += 7) {
        for (int j = i; j <= i + 3; ++j) {
            if (j + 18 < 42 && connect4Board[j] != ' ' && connect4Board[j] == connect4Board[j + 6] &&
                connect4Board[j + 6] == connect4Board[j + 12] && connect4Board[j + 12] == connect4Board[j + 18])
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

void printGame2048Board() {
    system(CLEAR_COMMAND);
    cout << YELLOW << "-----------------------------" << RESET << endl;
    for (int i = 0; i < 16; i += 4) {
        cout << YELLOW << "|";
        for (int j = i; j < i + 4; ++j) {
            if (game2048Board[j] == 0)
                cout << "     |";
            else
                printf(" %4d|", game2048Board[j]);
        }
        cout << endl;
        cout << YELLOW << "-----------------------------" << RESET << endl;
    }
}

int getRandomEmptyCell() {
    vector<int> emptyCells;
    for (int i = 0; i < 16; ++i) {
        if (game2048Board[i] == 0)
            emptyCells.push_back(i);
    }

    if (emptyCells.empty())
        return -1;

    uniform_int_distribution<int> dist(0, emptyCells.size() - 1);
    return emptyCells[dist(rng)];
}

void insertRandomValueInGame2048() {
    int emptyCell = getRandomEmptyCell();
    if (emptyCell != -1) {
        uniform_int_distribution<int> dist(0, 9);
        int value = (dist(rng) < 9) ? 2 : 4;
        game2048Board[emptyCell] = value;
    }
}

bool performMoveInGame2048(int direction) {
    vector<int> tempBoard = game2048Board;
    bool moved = false;

    // Move tiles in the specified direction
    for (int i = 0; i < 4; ++i) {
        vector<int> row;
        for (int j = 0; j < 4; ++j) {
            int index = (direction == 0) ? i * 4 + j : (direction == 1) ? j * 4 + i : (direction == 2) ? i * 4 + (3 - j) : (3 - j) * 4 + i;
            if (game2048Board[index] != 0)
                row.push_back(game2048Board[index]);
        }

        int rowSize = row.size();
        for (int j = 0; j < rowSize - 1; ++j) {
            if (row[j] == row[j + 1]) {
                row[j] *= 2;
                row.erase(row.begin() + j + 1);
                rowSize--;
            }
        }

        while (row.size() < 4)
            row.push_back(0);

        for (int j = 0; j < 4; ++j) {
            int index = (direction == 0) ? i * 4 + j : (direction == 1) ? j * 4 + i : (direction == 2) ? i * 4 + (3 - j) : (3 - j) * 4 + i;
            game2048Board[index] = row[j];
            if (tempBoard[index] != game2048Board[index])
                moved = true;
        }
    }

    return moved;
}

bool checkIsGameOverInGame2048() {
    for (int i = 0; i < 16; ++i) {
        if (game2048Board[i] == 0)
            return false;
        if (i % 4 != 3 && game2048Board[i] == game2048Board[i + 1])
            return false;
        if (i < 12 && game2048Board[i] == game2048Board[i + 4])
            return false;
    }
    return true;
}

void playTicTacToe(int position) {
    if (ticTacToeBoard[position] != ' ') {
        cout << "Invalid move. Please try again." << endl;
        return;
    }

    ticTacToeBoard[position] = currentPlayerSymbol;

    if (checkIsWinnerTicTacToe()) {
        printTicTacToeBoard();
        cout << "Player " << currentPlayerSymbol << " wins!" << endl;
        finishGame = true;
    } else if (count(ticTacToeBoard.begin(), ticTacToeBoard.end(), ' ') == 0) {
        printTicTacToeBoard();
        cout << "It's a draw!" << endl;
        finishGame = true;
    } else {
        currentPlayerSymbol = (currentPlayerSymbol == 'X') ? 'O' : 'X';
        printTicTacToeBoard();
    }
}

void playConnect4(int column) {
    if (column < 0 || column > 6 || connect4Board[column] != ' ') {
        cout << "Invalid move. Please try again." << endl;
        return;
    }

    int row = 35 + column;
    while (row >= 0) {
        if (connect4Board[row] == ' ') {
            connect4Board[row] = currentPlayerSymbol;
            break;
        }
        row -= 7;
    }

    if (checkIsWinnerConnect4()) {
        printConnect4Board();
        cout << "Player " << currentPlayerSymbol << " wins!" << endl;
        finishGame = true;
    } else if (count(connect4Board.begin(), connect4Board.end(), ' ') == 0) {
        printConnect4Board();
        cout << "It's a draw!" << endl;
        finishGame = true;
    } else {
        currentPlayerSymbol = (currentPlayerSymbol == 'X') ? 'O' : 'X';
        printConnect4Board();
    }
}

void playGame2048(char move) {
    int direction;
    switch (move) {
        case 'w':
            direction = 1; // Up
            break;
        case 's':
            direction = 3; // Down
            break;
        case 'a':
            direction = 0; // Left
            break;
        case 'd':
            direction = 2; // Right
            break;
        default:
            cout << "Invalid move. Please try again." << endl;
            return;
    }

    if (!performMoveInGame2048(direction)) {
        cout << "Invalid move. Please try again." << endl;
        return;
    }

    if (checkIsGameOverInGame2048()) {
        printGame2048Board();
        cout << "Game over!" << endl;
        finishGame = true;
    } else {
        insertRandomValueInGame2048();
        printGame2048Board();
    }
}

void runGame(GameOption gameOption) {
    finishGame = false;
    currentPlayerSymbol = 'X';
    ticTacToeBoard = vector<char>(9, ' ');
    connect4Board = vector<char>(42, ' ');
    game2048Board = vector<int>(16, 0);

    switch (gameOption) {
        case GameOption::TicTacToe:
            printTicTacToeBoard();
            break;
        case GameOption::Connect4:
            printConnect4Board();
            break;
        case GameOption::Game2048:
            insertRandomValueInGame2048();
            insertRandomValueInGame2048();
            printGame2048Board();
            break;
    }

    while (!finishGame) {
        cout << "Player " << currentPlayerSymbol << ", make your move: ";
        string move;
        getline(cin, move);

        switch (gameOption) {
            case GameOption::TicTacToe:
                playTicTacToe(stoi(move) - 1);
                break;
            case GameOption::Connect4:
                playConnect4(stoi(move));
                break;
            case GameOption::Game2048:
                playGame2048(move[0]);
                break;
        }
    }
}

int main() {
    cout << "Welcome to the Game Hub!" << endl;
    cout << "Select a game to play:" << endl;
    cout << "1. Tic Tac Toe" << endl;
    cout << "2. Connect 4" << endl;
    cout << "3. 2048" << endl;

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    GameOption gameOption;
    switch (choice) {
        case 1:
            gameOption = GameOption::TicTacToe;
            break;
        case 2:
            gameOption = GameOption::Connect4;
            break;
        case 3:
            gameOption = GameOption::Game2048;
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl;
            return 0;
    }

    runGame(gameOption);

    return 0;
}

