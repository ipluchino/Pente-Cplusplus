#pragma once

#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

class Player
{
public:
	//Default constructor - By default, the player's color is set to white if none is provided.
	Player();

	//Parametric contructor
	Player(char a_color, unsigned int a_score, unsigned int a_capturedPairs);

	//Destructor
	~Player() {};

	//Selectors
	char GetColor() const { return m_color; }
	unsigned int GetScore() const { return m_score; }
	unsigned int GetCapturedPairs() const { return m_capturedPairs; }

	//Mutators
	void SetColor(char a_color) { m_color = a_color; }
	void SetScore(unsigned int a_score) { m_score = a_score; }
	void SetCapturedPairs(unsigned int a_capturedPairs) { m_capturedPairs = a_capturedPairs; }

	//Utility Functions
	virtual void MakePlay(Board& a_board);

	//Strategy Function

protected:
	//The color of the stones (black or white) that the player is playing as.
	char m_color;

	//The overall score for the player.
	unsigned int m_score;

	//The number of captured pairs for the player.
	unsigned int m_capturedPairs;
};

