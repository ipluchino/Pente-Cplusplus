#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Board
{
public:
	//Constants
	const unsigned int BOARD_SIZE = 19;
	
	//Default Constructor
	Board();

	//Destructor
	~Board() {};

	//Selectors
	vector<vector<char>> GetBoard() { return m_board; }

	//Mutators
	void SetBoard(vector<vector<char>> a_board) { m_board = a_board; }
	void PlaceStone(char a_column, int a_row, char a_pieceColor);
	void RemoveStone(char a_column, int a_row);


	//Utility Functions
	void DisplayBoard();

private:
	//Holds all of the data for the entire board.
	vector<vector<char>> m_board;

};

