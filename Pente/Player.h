#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Board.h"

using namespace std;

class Player
{
public:
	//Constants
	//Represents the "instructions" for the 8 possible directions on the board. Left, Right, Down, Up, and the four possible diagonals.
	const vector<vector<int>> DIRECTIONS = { {0,-1}, {0,1}, {1,0}, {-1,0}, {1, 1}, {-1,-1}, {1,-1}, {-1,1} };

	//Represents the total number of possible directions, in this case 8.
	const int NUM_DIRECTIONS = 8;

	//Default constructor - By default, the player's color is set to white if none is provided.
	Player();

	//Destructor
	~Player() {};

	//Selectors
	char GetColor() const { return m_color; }
	int GetScore() const { return m_score; }
	int GetCapturedPairs() const { return m_capturedPairs; }

	//Mutators
	void SetColor(char a_color) { m_color = a_color; }
	void SetScore(int a_score) { m_score = a_score; }
	void SetCapturedPairs(int a_capturedPairs) { m_capturedPairs = a_capturedPairs; }

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

