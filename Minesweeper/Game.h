#pragma once
#include "Board.h"
#include "UserInterface.h"

extern const char MINE;
extern const char FLAG;
extern const char REVEALEDZERO;
extern const char UNREVEALED;

class Game {
	Board board;
public:
	Game();
	bool forceQuit(std::vector<int> position);
	bool checkInput(std::vector<int> position);
	bool flagHandler();
	bool gameWon();
};