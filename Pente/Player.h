#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
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
	virtual bool MakePlay(Board& a_board);
	string ExtractLocation(int a_row, int a_col, Board a_board);
	string GetDirection(int a_directionIndex);
	
	//Strategy Functions
	pair<string, string> OptimalPlay(Board a_board, char a_color);
	vector<int> MakeCapture(Board a_board, char a_color);
	int CanCaptureIfPlaced(Board a_board, char a_color, int a_row, int a_col);
	vector<int> PreventCapture(Board a_board, char a_color);
	vector<vector<vector<int>>> FindAllMoves(Board a_board, int a_numPlaced, char a_color, int a_distance);
	vector<int> FindEmptyIndices(Board a_board, vector<vector<int>> a_locations);
	int FindConsecutiveIfPlaced(Board a_board, vector<vector<int>> a_locations, int emptyIndex);
	vector<int> BuildInitiative(Board a_board, int a_numPlaced, char a_color, char a_dangerColor);
	vector<int> CounterInitiative(Board a_board, int a_numPlaced, char a_color);
	vector<int> MakeWinningMove(Board a_board, char a_color);
	vector<int> PreventWinningMove(Board a_board, char a_color);
	bool InDangerOfCapture(Board a_board, vector<int> a_location, char a_color);
	vector<int> FindFlanks(Board a_board, char a_color);
	vector<int> FindDeadlyTessera(Board a_board, char a_color);
	vector<int> FindThreeConsecutive(Board a_board, vector<vector<vector<int>>> a_possibleMoves, char a_dangerColor);
	vector<int> FindFourConsecutive(Board a_board, vector<vector<vector<int>>> a_possibleMoves, char a_dangerColor);

protected:
	//The color of the stones (black or white) that the player is playing as.
	char m_color;

	//The overall score for the player.
	int m_score;

	//The number of captured pairs for the player.
	int m_capturedPairs;
};

