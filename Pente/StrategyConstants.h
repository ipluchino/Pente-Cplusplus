/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : StrategyConstants class - header file.
* Date : 9/27/23
************************************************************/

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class StrategyConstants
{
public:
	//Default Constructor
	StrategyConstants();
	
	//Size of the board will always be 19x19.
	static const int BOARD_SIZE = 19;

	//Represents the instructions for the 8 possible directions on the board. Left, Right, Down, Up, and the four possible diagonals.
	static const vector<vector<int>> DIRECTIONS;

	//Represents the total number of possible directions, in this case 8.
	static const int NUM_DIRECTIONS = 8;

	//Represents the number of spaces needed to search from a current location on the board to find a capture.
	static const int CAPTURE_DISTANCE = 3;

	//Represents the incremement required to skip over opposite directions. Ex: When searching horizontals, left & right directions searches would be the same.
	static const int DIRECTIONAL_OFFSET = 2;

	//Represents the total number of spaces required to make three consecutive pieces.
	static const int CONSECUTIVE_3_DISTANCE = 3;

	//Represents the total number of spaces required to make four consecutive pieces.
	static const int CONSECUTIVE_4_DISTANCE = 4;

	//Represents the total number of spaces required to make five consecutive pieces.
	static const int CONSECUTIVE_5_DISTANCE = 5;
};

