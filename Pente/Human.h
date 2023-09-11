#pragma once

#include <string>
#include "Player.h"
#include "UserInput.h"

class Human: public Player
{
public:
	//Default Constructor
	Human();
	
	//Destructor
	~Human() {};

	//Selectors

	//Mutators

	//Utility Functions
	void MakePlay(Board& a_board);

private:
	//UserInput object used to obtain input from the human player.
	UserInput m_userInput;
};

