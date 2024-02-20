#include "UserInterface.h"

int UserInterface::getDifficulty() {
    int difficulty;
    std::cout << "Choose the difficulty! (1 for Beginner | 2 for Intermediate | 3 for Advanced)" << std::endl;
    std::cin >> difficulty;
    return difficulty;
}

void UserInterface::printBoard(const std::vector<std::vector<char>>& userBoard) {
    for (int i = 0; i < userBoard.size(); i++) {
        for (int j = 0; j < userBoard.size(); j++)
            std::cout << userBoard[i][j];
        std::cout << std::endl;
    }
}

void UserInterface::printFinalBoard(const std::vector<std::vector<char>>& hiddenBoard, const std::vector<std::vector<char>>& userBoard) {
    for (int i = 0; i < hiddenBoard.size(); i++) {
        for (int j = 0; j < hiddenBoard.size(); j++)
            if (hiddenBoard[i][j] == MINE)
                std::cout << hiddenBoard[i][j];
            else
                std::cout << userBoard[i][j];
        std::cout << std::endl;
    }
}

std::vector<int> UserInterface::getPosition() {
    std::vector<int> position(2);
    std::cout << "Insert the position![insert -1 -1 to exit]" << std::endl;
    std::cin >> position[0] >> position[1];
    return position;
}