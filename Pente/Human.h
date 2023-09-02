#pragma once

#include "Player.h"

class Human: public Player
{
public:
	//Default Constructor
	Human();

	//Parametric Constructor used to start a new game.
	Human(char a_humanColor);
	
	//Destructor
	~Human() {};

	//Selectors

	//Mutators

	//Utility Functions
	void MakePlay(Board& a_board);

private:

};

