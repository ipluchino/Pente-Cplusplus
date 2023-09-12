#pragma once

#include <iostream>
#include <vector>

using namespace std;

class StrategyConstants
{
public:
	//Size of the board will always be 19x19.
	static const int BOARD_SIZE = 19;

	////Represents the "instructions" for the 8 possible directions on the board. Left, Right, Down, Up, and the four possible diagonals.
	static const vector<vector<int>> DIRECTIONS;
	// { {0,-1}, {0,1}, {1,0}, {-1,0}, {1, 1}, {-1,-1}, {1,-1}, {-1,1} };

	//Represents the total number of possible directions, in this case 8.
	static const int NUM_DIRECTIONS = 8;

	//Represents the number of spaces needed to search from a current location on the board to find a capture.
	static const int CAPTURE_DISTANCE = 3;

	//Represents the incremement required to skip over opposite directions. Ex: When searching horizontals, left & right directions searches would be the same.
	static const int DIRECTIONAL_OFFSET = 2;

	//Represents the total number of spaces needed to search when searching for a consecutive 4 of the same piece.
	static const int CONSECUTIVE_4_DISTANCE = 4;

	//Represents the total number of spaces needed to search when searching for a consecutive 5 of the same piece.
	static const int CONSECUTIVE_5_DISTANCE = 5;
};

