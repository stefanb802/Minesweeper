#include "Board.h"

Board::Board(int boardSize, int mines) {
	this->boardSize = boardSize;
	this->mines = mines;
	hiddenBoard.resize(boardSize);
	for (int i = 0; i < boardSize; i++)
		hiddenBoard[i] = std::vector<char>(boardSize, UNREVEALED);
	userBoard.resize(boardSize);
	userBoard = hiddenBoard;
}

void Board::placeMines() {
	for (int i = 0; i < mines; i++) {
		int pos = std::rand() % (boardSize * boardSize);
		int m = pos / boardSize;
		int n = pos % boardSize;
		hiddenBoard[m][n] = MINE;
	}
}

//Proximity=a 9-cell square centered in the given cell
//Assigns the numerical values on the hidden board based on the number of mines in the cell's proximity
static void checkProximity(int i, int j) {
	int cntr = 0;
	for (int m = max(0, i - 1); m <= min(i + 1, boardSize - 1); m++)
		for (int n = max(0, j - 1); n <= min(j + 1, boardSize - 1); n++)
			if (hiddenBoard[m][n] == MINE)
				cntr++;
	hiddenBoard[i][j] = (char)(cntr + '0');
	return;
}

void Board::completeBoard() {
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (hiddenBoard[i][j] != MINE)
				checkProximity(i, j);
}

bool Board::checkCell(int i, int j) {
	if (board[i][j] == MINE) {
		return false;
	if (hiddenBoard[i][j] != '0') {
		userBoard[i][j] = hiddenBoard[i][j];
	}
	else {
		userBoard[i][j] = REVEALEDZERO;
		clearProximity(i, j);
	}
	return true;
}

//Recursiveley reveals all the non-mine cells in the proximity if the user reveals a '0' 
static void clearProximity(int i, int j) {
	if (hiddenBoard[i][j] != '0')
		return;
	for (int m = max(0, i - 1); m <= min(boardSize - 1, i + 1); m++)
		for (int n = max(0, j - 1); n <= min(boardSize - 1, j + 1); n++) {
			if (userBoard[m][n] == UNREVEALED || userBoard[m][n] == FLAG) {
				if (hiddenBoard[m][n] == '0')
					userBoard[m][n] = REVEALEDZERO;
				else
					userBoard[m][n] = hiddenBoard[m][n];
				clearProximity(m, n);
			}
		}
	return;
}