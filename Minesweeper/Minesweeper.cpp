// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Basic Minesweeper game. Creates a board based on the difficulty. The user has to reveal all the non-mine cells in order to win. If the user reveals a mine, the game is over.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

//Predefined constants for the boards
const char MINE = 'M';
const char UNREVEALED = 'X';
const char FLAG = 'F';
const char REVEALEDZERO = '*';

//Assigned based on the difficulty
int boardSize;
int mines;

//Game generation-related methods

//Generates the board based on the size
vector<vector<char>> generateBoard() {
    vector<vector<char>> board(boardSize);
    for (int i = 0; i < boardSize; i++)
        board[i] = vector<char>(boardSize, UNREVEALED); 
    return board;
}

//Randomly places the mines when the game begins
void putMines(vector<vector<char>>& board) {
    for (int i = 0; i < mines; i++) {
        int pos = rand() % (boardSize * boardSize);
        int m = pos / boardSize;
        int n = pos % boardSize;
        board[m][n] = MINE;
    }
}

//Proximity=a 9-cell square
//Assigns the numerical values on the hidden board based on the number of mines in their proximity
void checkProximity(vector<vector<char>>& board, int i, int j) {
    int cntr = 0;
    for (int m = max(0, i - 1); m <= min(i + 1, boardSize - 1); m++)
        for (int n = max(0, j - 1); n <= min(j + 1, boardSize - 1); n++)
            if (board[m][n] == MINE)
                cntr++;
    board[i][j] = (char)(cntr + '0');
    return;
}

void completeBoard(vector<vector<char>>& board) {
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            if(board[i][j]!=MINE)
                checkProximity(board, i, j);
}

//User-related methods

//Assigns the size of the board and the number of mines based on the user's input
int getDifficulty() {
    int difficulty;
    cout << "Choose the difficulty! (1 for Beginner | 2 for Intermediate | 3 for Advanced)" << endl;
    cin >> difficulty;
    switch (difficulty) {
    case 1:
        boardSize = 9;
        mines = 10;
        break;
    case 2:
        boardSize = 16;
        mines = 40;
        break;
    case 3:
        boardSize = 24;
        mines = 99;
        break;
    default:
        cout << "Error!" << endl;
        return 0;
    }
    return difficulty;
}

//Displays the board
void printBoard(vector<vector<char>> board) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++)
            cout << board[i][j];
        cout << endl;
    }
}

//Reveals the mines when the game is over
void printFinalBoard(vector<vector<char>> board, vector<vector<char>> userBoard) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++)
            if (board[i][j] == MINE)
                cout << board[i][j];
            else
                cout << userBoard[i][j];
        cout << endl;
    }
}

//If the user finds a '0', this function recursively reveals all the other numbers in the proximity
void clearProximity(vector<vector<char>> board, vector<vector<char>>& userBoard, int i, int j) {
    if (board[i][j] != '0')
        return;
    for (int m = max(0, i - 1); m <= min(boardSize - 1, i + 1); m++)
        for (int n = max(0, j - 1); n <= min(boardSize - 1, j + 1); n++) {
            if (userBoard[m][n] == UNREVEALED || userBoard[m][n] == FLAG) {
                if (board[m][n] == '0')
                    userBoard[m][n] = REVEALEDZERO;
                else
                    userBoard[m][n] = board[m][n];
                clearProximity(board, userBoard, m, n);
            }
        }
    return;
}

//Checks if the user has completed the game
bool gameWon(vector<vector<char>> board, vector<vector<char>> userBoard) {
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            if ((board[i][j] == '0' && userBoard[i][j] != REVEALEDZERO) || (board[i][j] >= '1' && board[i][j] < MINE && board[i][j] != userBoard[i][j]))
                return false;
    return true;
}


//The user can place a flag
void putFlag(vector<vector<char>>& userBoard, int i, int j) {
    if (i < 0 || j<0 || i >= boardSize || j>boardSize)
        return;
    if (userBoard[i][j] == UNREVEALED)
        userBoard[i][j] = FLAG;
    return;
}

//The user can remove a flag
void removeFlag(vector<vector<char>>& userBoard, int i, int j) {
    if (i < 0 || j<0 || i >= boardSize || j>boardSize)
        return;
    if (userBoard[i][j] == FLAG)
        userBoard[i][j] = UNREVEALED;
    return;
}

//Handles flag-related actions
void flagHandler(vector<vector<char>>& userBoard, string put_Flag, string remove_Flag) {
    while (put_Flag == "y" || remove_Flag == "y") {
        cout << "Place a flag?[press y for yes/any key for no]" << endl;
        cin >> put_Flag;
        if (put_Flag == "y") {
            int rowPlaceFlag, colPlaceFlag;
            cout << "Insert row and column!" << endl;
            cin >> rowPlaceFlag >> colPlaceFlag;
            putFlag(userBoard, rowPlaceFlag, colPlaceFlag);
            printBoard(userBoard);
        }
        cout << "Remove a flag?[press y for yes/any key for no]" << endl;
        cin >> remove_Flag;
        if (remove_Flag == "y") {
            int rowRemoveFlag, colRemoveFlag;
            cout << "Insert row and column!" << endl;
            cin >> rowRemoveFlag >> colRemoveFlag;
            removeFlag(userBoard, rowRemoveFlag, colRemoveFlag);
            printBoard(userBoard);
        }
    }
}

//Checks if the game is lost(user selects a mine). Otherwise, it reveals the number(s).
bool checkBoard(vector<vector<char>> board, vector<vector<char>>& userBoard, int i, int j) {
    if (board[i][j] == MINE) {
        cout << "Game over! You lost!" << endl;
        return false;
    }
    if (board[i][j] != '0') {
        userBoard[i][j] = board[i][j];
    }
    else {
        userBoard[i][j] = REVEALEDZERO;
        clearProximity(board, userBoard, i, j);
    }
    if (gameWon(board, userBoard)) {
        cout << "Congratulations! You won!" << endl;
        return false;
    }
    return true;
}

//Handles the user's input 
bool checkInput(vector<vector<char>> board, vector<vector<char>>& userBoard) {
    //Asks the user to choose a cell to be revealed. The user can exit the game by choosing -1 and -1.
    cout << "Insert row and column![Insert -1&-1 to end the game]" << endl;
    int row, col;
    cin >> row >> col;
    if (row == -1 && col == -1) {
        cout << "Game over!" << endl;
        return false;
    }
    //Checks if the given values can be used
    while (row >= boardSize || col >= boardSize || row < 0 || col < 0 || userBoard[row][col] != 'X') {
        cout << "Incorrect values! Insert row and column!" << endl;
        cin >> row >> col;
    }
    //Checks if the game reaches the next turn
    return checkBoard(board, userBoard, row, col);
}
int main()
{
    int difficulty=getDifficulty();
    //Ensures that the difficulty level is correct
    while (difficulty == 0)
        difficulty = getDifficulty();
    vector<vector<char>> board = generateBoard();
    //The board that is displayed to the user
    vector<vector<char>> userBoard=board;
    srand(time(0));
    putMines(board);
    completeBoard(board);
    bool playOn = true;
    //Uncomment the following line if you want to see the hidden board before the game begins
    //printBoard(board);
    while (playOn) {
        //Displays the board at the beginning of the turn
        printBoard(userBoard);
        string put_Flag = "y";
        string remove_Flag = "y";
        //Checks if the user wants to perform a flag-related action and displays the board if such action takes place
        flagHandler(userBoard, put_Flag, remove_Flag);
        playOn=checkInput(board, userBoard);     
    }
    //Reveals the mines when the game is over
    printFinalBoard(board, userBoard);
    return 0;
}



