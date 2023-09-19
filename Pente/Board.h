#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "StrategyConstants.h"

using namespace std;

class Board
{
public:
	//Default Constructor
	Board();

	//Destructor
	~Board() {};

	//Selectors
	vector<vector<char>> GetBoard() const { return m_board; }

	//Mutators
	bool SetBoard(vector<vector<char>> a_board);
	bool PlaceStone(char a_column, int a_row, char a_pieceColor);
	bool RemoveStone(char a_column, int a_row);

	//Utility Functions
	void DisplayBoard();
	bool IsValidIndices(int a_row, int a_column);
	bool IsEmptyLocation(char a_column, int a_row);
	int CountPieces(char a_color);
	bool IsEmptyBoard();
	int ClearCaptures(char a_column, int a_row, char a_color);
	char OpponentColor(char a_color);
	bool IsBoardFull();
	bool FiveConsecutive(char a_color);
	int ScoreBoard(char a_color, int a_numCaptures);
	void ClearBoard();

	//Conversion Functions
	int CharacterToInt(char a_column);
	char IntToCharacter(int a_column);
	int ConvertRowIndex(int a_row);



private:
	//Holds all of the data for the entire board.
	vector<vector<char>> m_board;
};

