//Creates and initializes both the hidden board and the user's board
#pragma once

#include <vector>
#include <cstdlib>

const char MINE = 'M';
const char UNREVEALED = 'X';
const char FLAG = 'F';
const char REVEALEDZERO = '*';

class Board {
public:
	int boardSize;
	int mines;
	std::vector<std::vector<char>> hiddenBoard;
	std::vector<std::vector<char>> userBoard;
	Board();
	Board(int boardSize, int mines);
	//Randomly place the mines on the hidden board
	void placeMines();
	//Proximity=a 9-cell square centered in the given cell
	//Assigns the numerical values on the hidden board based on the number of mines in the cell's proximity
	void checkProximity(int i, int j);
	void completeBoard();
	//Recursiveley reveals all the non-mine cells in the proximity if the user reveals a '0' 
	void clearProximity(int i, int j);
	bool checkCell(int i, int j);
};
