/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Human class - header file.
* Date : 9/27/23
************************************************************/

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

	//Utility Functions
	bool MakePlay(Board& a_board);
	string AskForHelp(Board a_board);

private:
	//UserInput object used to obtain input from the human player.
	UserInput m_userInput;
};

