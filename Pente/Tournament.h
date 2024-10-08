/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Tournament class - header file.
* Date : 9/27/23
************************************************************/

#pragma once

#include <iostream>
#include "UserInput.h"
#include "Round.h";

using namespace std;

class Tournament
{
public:
	//Default Constructor
	Tournament();

	//Utility Functions
	bool LoadGame();
	void StartTournament();
	bool Continue();
	string WhoWon();

private:
	//Round object used to play one round of Pente.
	Round m_round;

	//UserInput object used to obtain input from the human player.
	UserInput m_userInput;
};