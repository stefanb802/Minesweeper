#pragma once
#include <iostream>
#include <string>

class UserInterface {
public:
	static int getDifficulty();
	static void printBoard(const std::vector<std::vector<char>>& userBoard);
	//Reveals all the mines when the game ends
	static void printFinalBoard(const std::vector<std::vector<char>>& hiddenBoard, const std::vector<std::vector<char>>& userBoard);
	static std::vector<int> getPosition();
};