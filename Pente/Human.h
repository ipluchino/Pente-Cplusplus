#pragma once

#include "Player.h"

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

};

