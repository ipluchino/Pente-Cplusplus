#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Board.h"

using namespace std;

class UserInput
{
public:
	//Default Constructor
	UserInput();

	//Utility Functions
	string GetPlayLocation(Board a_board);
	string GetTournamentChoice();
	string GetCoinTossCall();
	string GetHumanDecision();
	string GetSaveDecision();

private:

};

