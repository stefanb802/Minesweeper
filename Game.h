#pragma once
#include "Board.h"
#include "UserInterface.h"

class Game {
	Board board;
public:
	Game();
	static bool forceQuit(std::vector<int> position);
	static bool checkInput(std::vector<int> position);
	static bool flagHandler();
	static bool gameWon();
};