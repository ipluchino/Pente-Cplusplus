/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : UserInput class - header file.
* Date : 9/27/23
************************************************************/

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
	string GetComputerDecision();
	string GetFileNameLoad();
	string GetFileNameSave();
	string GetContinueDecision();
};

