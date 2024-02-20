//Creates and initializes both the hidden board and the user's board
#pragma once

#include <vector>
#include <cstdlib>

extern const char MINE = 'M';
extern const char UNREVEALED = 'X';
extern const char FLAG = 'F';
extern const char REVEALEDZERO = '*';

class Board {
	int boardSize;
	int mines;
	std::vector<std::vector<char>> hiddenBoard;
	std::vector<std::vector<char>> userBoard;
public:
	Board(int boardSize, int mines);
	//Randomly place the mines on the hidden board
	void placeMines();
	void completeBoard();
	bool checkCell(int i, int j);
};
