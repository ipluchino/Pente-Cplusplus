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
	void CreateNewGame();
	void LoadGame();
	void Continue();
	void StartTournament();

private:
	//Round object used to play one round of Pente.
	Round m_round;

	//UserInput object used to obtain input from the human player.
	UserInput m_UserInput;
};