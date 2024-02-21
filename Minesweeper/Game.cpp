#include "Game.h"

const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;

bool Game::forceQuit(std::vector<int> position) {
	return (position[0] == -1 && position[1] == -1);
}

bool Game::checkInput(std::vector<int> position) {
	return !(position[0] < 0 || position[0] >= board.boardSize || position[1] < 0 || position[1] >= board.boardSize);
}

bool Game::flagHandler() {
	std::string flagInput;
	std::cout << "Add or remove flag?[press y for yes | press any key for no]"<<std::endl;
	std::cin >> flagInput;
	if (flagInput != "y")
		return false;
	std::vector<int> position = UserInterface::getPosition();
	if (forceQuit(position))
		return false;
	while (!checkInput(position)) {
		std::cout << "Invalid input!" << std::endl;
		position = UserInterface::getPosition();
	}
	if (board.userBoard[position[0]][position[1]] == UNREVEALED) 
		board.userBoard[position[0]][position[1]] = FLAG;
	else if (board.userBoard[position[0]][position[1]] == FLAG)
		board.userBoard[position[0]][position[1]] = UNREVEALED;
	UserInterface::printBoard(board.userBoard);
	return true;
}

bool Game::gameWon() {
	for (int i = 0; i < board.hiddenBoard.size(); i++)
		for (int j = 0; j < board.hiddenBoard.size(); j++)
			if ((board.hiddenBoard[i][j] == '0' && board.userBoard[i][j] != REVEALEDZERO) || (board.hiddenBoard[i][j] >= '1' && board.hiddenBoard[i][j] < MINE && board.hiddenBoard[i][j] != board.userBoard[i][j]))
				return false;
	return true;
}

Game::Game() {
	int difficulty = UserInterface::getDifficulty();
	while (difficulty != EASY && difficulty != MEDIUM && difficulty != HARD) {
		std::cout << "Incorrect input!" << std::endl;
		difficulty = UserInterface::getDifficulty();
	}
	switch (difficulty) {
	case EASY: 
		board = Board(9, 10);
		break;
	case MEDIUM:
		board = Board(16, 40);
		break;
	case HARD:
		board = Board(24, 99);
		break;
	}
	srand(time(0));
	board.placeMines();
	board.completeBoard();
	bool playOn = true;
	//UserInterface::printBoard(board.hiddenBoard);
	while (playOn) {
		UserInterface::printBoard(board.userBoard);
		bool flagAction=true;
		while (flagAction)
			flagAction = flagHandler();
		std::cout << "Reveal cell!"<<std::endl;
		std::vector<int> position = UserInterface::getPosition();
		if (forceQuit(position)) {
			std::cout << "Game over!" << std::endl;
			break;
		}
		while (!checkInput(position)) {
			std::cout << "Invalid input!" << std::endl;
			position = UserInterface::getPosition();
		}
		playOn=board.checkCell(position[0], position[1]);
		if (!playOn)
			std::cout << "Game over! You lost!" << std::endl;
		if (gameWon()) {
			std::cout << "Congratulations! You won!" << std::endl;
			playOn = false;
		}
	}
	UserInterface::printFinalBoard(board.hiddenBoard, board.userBoard);
	
}