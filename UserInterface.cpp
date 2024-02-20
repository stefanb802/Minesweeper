#include "UserInterface.h"

static int UserInterface::getDifficulty() {
    int difficulty;
    std::cout << "Choose the difficulty! (1 for Beginner | 2 for Intermediate | 3 for Advanced)" << endl;
    std::cin >> difficulty;
}

static void UserInterface::printBoard(std::vector<std::vector<char>>& userBoard) {
    for (int i = 0; i < userBoard.size(); i++) {
        for (int j = 0; j < userBoard.size(); j++)
            std::cout << userBoard[i][j] << " ";
        std::cout << endl;
    }
}

static void UserInterface::printFinalBoard(const std::vector<std::vector<char>>& hiddenBoard, const std::vector<std::vector<char>>& userBoard) {
    for (int i = 0; i < hiddenBoard.size(); i++) {
        for (int j = 0; j < hiddenBoard.size(); j++)
            if (hiddenBoard[i][j] == MINE)
                std::cout << hiddenBoard[i][j];
            else
                std::cout << userBoard[i][j];
        std::cout << endl;
    }
}

static std::vector<int> UserInterface::getPosition() {
    std::vector<int> position(2);
    std::cout << "Insert the position![insert -1 -1 to exit]" << end;
    std::cin >> position[0] >> position[1];
    return position;
}