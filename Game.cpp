#include "Game.h"

const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;

static bool Game::forceQuit(std::vector<int> position) {
	return (position[0] == -1 && position[1] == -1);
}

static bool Game::checkInput(std::vector<int> position) {
	return !(position[0] < 0 || position[0] >= board.boardSize || poistion[1] < 0 || position[1] >= board.boardSize);
}

static bool Game::flagHandler() {
	string flagInput;
	std::cout << "Add or remove flag?[press y for yes | press any key for no]"<<endl;
	std::cin >> flagInput;
	if (flagInput != "y")
		return false;
	vector<int> position = UserInterface::getPosition();
	if (forceQuit(position))
		return false;
	while (!checkInput(position)) {
		cout << "Invalid input!" << endl;
		position = UserInterface::getPosition();
	}
	if (board.userBoard[poistion[0]][position[1]] == UNREVEALED)
		board.userBoard[poistion[0]][position[1]] = FLAG;
	if (board.userBoard[poistion[0]][position[1]] == FLAG)
		board.userBoard[poistion[0]][position[1]] = UNREVEALED;
	return true;
}

static bool Game::gameWon() {
	for (int i = 0; i < board.hiddenBoard.size(); i++)
		for (int j = 0; j < board.hiddenBoard.size(); j++)
			if ((board.hiddenBoard[i][j] == '0' && board.userBoard[i][j] != REVEALEDZERO) || (board.hiddenBoard[i][j] >= '1' && board.hiddenBoard[i][j] < MINE && board.hiddenBoard[i][j] != board.userBoard[i][j]))
				return false;
	return true;
}

Game::Game() {
	int difficulty = UserInterface::getDifficulty();
	while (difficulty != EASY && difficulty != MEDIUM && difficulty != HARD) {
		cout << "Incorrect input!" << endl;
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
	bool playOn = true;
	while (playOn) {
		UserInterface::printBoard(board.userBoard);
		bool flagAction=true;
		while (flagAction)
			flagAction = flagHandler();
		std::cout << "Reveal cell!";
		std::vector<int> position = UserInterface::getPosition;
		if (forceQuit(position)) {
			std::cout << "Game over!" << endl;
			break;
		}
		while (!checkInput(position)) {
			cout << "Invalid input!" << endl;
			position = UserInterface::getPosition;
		}
		playOn=board.checkCell(position[0], position[1]);
		if (gameWon()) {
			cout << "Congratulations! You won!" << endl;
			playOn = false;
		}
	}
	UserInterface::printFinalBoard(board.hiddenBoard, board.userBoard);
	
}