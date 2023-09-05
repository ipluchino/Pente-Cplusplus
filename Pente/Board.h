#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Board
{
public:
	//Constants
	//Size of the board will always be 19x19.
	const int BOARD_SIZE = 19;								//Should be unsigned?
	
	////Represents the "instructions" for the 8 possible directions on the board. Left, Right, Up, Down, and the four possible diagonals.
	const vector<vector<int>> DIRECTIONS = { {0,-1}, {0,1}, {1,0}, {-1,0}, {1, 1}, {-1,-1}, {1,-1}, {-1,1} };
	
	//Represents the total number of possible directions, in this case 8.
	const int NUM_DIRECTIONS = 8;
	
	//Default Constructor
	Board();

	//Destructor
	~Board() {};

	//Selectors
	vector<vector<char>> GetBoard() const { return m_board; }

	//Mutators
	void SetBoard(vector<vector<char>> a_board) { m_board = a_board; }
	void PlaceStone(char a_column, int a_row, char a_pieceColor);
	void RemoveStone(char a_column, int a_row);

	//Utility Functions
	void DisplayBoard();
	bool IsEmptyLocation(char a_column, int a_row);
	int CountPieces(char a_color);
	bool IsEmptyBoard();
	
private:
	//Holds all of the data for the entire board.
	vector<vector<char>> m_board;

};

