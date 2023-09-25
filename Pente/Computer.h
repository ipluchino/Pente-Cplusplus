/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Computer class - header file.
* Date : 9/27/23
************************************************************/

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

	//Utility Functions
	bool MakePlay(Board& a_board);

private:
	//UserInput object used to obtain input from the human player and is used when determining if the player wants to save before the computer places a stone.
	UserInput m_userInput;
};

