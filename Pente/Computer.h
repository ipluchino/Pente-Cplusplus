#pragma once

#include "Player.h"

class Computer: public Player
{
public:
	//Default Constructor
	Computer();

	//Parametric Constructor to start a new game.
	Computer(char a_computerColor);

	//Destructor
	~Computer() {};

	//Selectors
	
	//Mutators

	//Utility Functions
	void MakePlay(Board& a_board);



private:

};

