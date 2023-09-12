#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Board.h"
#include "StrategyConstants.h"

using namespace std;

class Player
{
public:
	//Default constructor - By default, the player's color is set to white if none is provided.
	Player();

	//Destructor
	~Player() {};

	//Selectors
	char GetColor() const { return m_color; }
	int GetScore() const { return m_score; }
	int GetCapturedPairs() const { return m_capturedPairs; }

	//Mutators
	bool SetColor(char a_color);
	bool SetScore(int a_score);
	bool SetCapturedPairs(int a_capturedPairs);

	//Utility Functions
	virtual void MakePlay(Board& a_board);
	pair<string, string> OptimalPlay(Board a_board, char a_color);


protected:
	//The color of the stones (black or white) that the player is playing as.
	char m_color;

	//The overall score for the player.
	int m_score;

	//The number of captured pairs for the player.
	int m_capturedPairs;
};

