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

const vector<vector<int>> StrategyConstants::DIRECTIONS = { {0,-1}, {0,1}, {1,0}, {-1,0}, {1, 1}, {-1,-1}, {1,-1}, {-1,1} };

