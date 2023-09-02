#pragma once

#include <iostream>
#include <vector>
#include "Player.h"
#include "Human.h"
#include "Computer.h"

using namespace std;

class Round
{
public:
	//Default Constructor
	Round();

	//Parametric Constructor for starting a new game
	Round(char a_humanColor, char a_computerColor);

	//TO DO: Serialize constructor

	//Destructor
	~Round();

	//Selectors

	//Mutators

	//Utility Functions

private:
	//Holds a list of the players currently playing the game. In this case, there will be one human player and one computer player.
	vector<Player*> m_playerList;

	//Determins the current turn of the player. Will be either 'H' for human or 'C' for computer.
	char m_Turn;

};

