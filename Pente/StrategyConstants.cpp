/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : StrategyConstants class - implementation file.
* Date : 9/27/23
************************************************************/

#include "StrategyConstants.h"

/* *********************************************************************
Function Name: StrategyConstants - Default constructor
Purpose: To construct a StrategyConstants object.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
StrategyConstants::StrategyConstants()
{
}

//Represents the instructions for the 8 possible directions on the board. Left, Right, Down, Up, and the four possible diagonals.
const vector<vector<int>> StrategyConstants::DIRECTIONS = { {0,-1}, {0,1}, {1,0}, {-1,0}, {1, 1}, {-1,-1}, {1,-1}, {-1,1} };

//Represents the names of each of the eight directions.
const vector<string> StrategyConstants::DIRECTION_NAMES = { "horizontal", "horizontal", "vertical", "vertical", "main-diagonal", "main-diagonal", "anti-diagonal", "anti-diagonal"};