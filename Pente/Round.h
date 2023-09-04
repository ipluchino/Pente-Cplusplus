#pragma once

#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"

using namespace std;

class Round
{
public:
	//Default Constructor
	Round();

	//TO DO: Serialize constructor

	//Destructor
	~Round();

	//Selectors

	//Mutators

	//Utility Functions
	void StartRound();
	void DetermineFirstPlayer();
	bool CoinToss();
	void DisplayGame();

private:
	//Holds a list of the players currently playing the game. In this case, there will be one human player and one computer player.
	//m_playerList[0] will be the human player.
	//m_playerList[1] will be the computer player.
	vector<Player*> m_playerList;

	//The board for the round.
	Board m_board;

	//The current player whos turn it is. Will be either 'H' for human or 'C' for computer.
	char m_turn;

	//UserInput object used to obtain input from the human player.
	UserInput m_UserInput;

};

