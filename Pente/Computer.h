#pragma once

#include "Player.h"
#include "UserInput.h"

class Computer: public Player
{
public:
	//Default Constructor
	Computer();

	//Destructor
	~Computer() {};

	//Selectors
	
	//Mutators

	//Utility Functions
	bool MakePlay(Board& a_board);



private:
	//UserInput object used to obtain input from the human player and is used when determining if the player wants to save before the computer places a stone.
	UserInput m_userInput;
};

