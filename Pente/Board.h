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

	//Represents the number of spaces needed to search from a current location on the board to find a capture.
	const int CAPTURE_DISTANCE = 3;

	//Represents the incremement required to skip over opposite directions. Ex: When searching horizontals, left & right directions searches would be the same.
	const int DIRECTIONAL_OFFSET = 2;

	//Represents the number of spaces needed to search from a current location on the board to find a consecutive four.
	const int CONSECUTIVE_4_DISTANCE = 3;
	
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
	bool IsValidIndices(int a_row, int a_column);
	bool IsEmptyLocation(char a_column, int a_row);
	int CountPieces(char a_color);
	bool IsEmptyBoard();
	int ClearCaptures(char a_column, int a_row, char a_color);
	char OpponentColor(char a_color);
	bool IsBoardFull();
	bool FiveConsecutive();
	int ScoreBoard(char a_color, int a_numCaptures);

	//Conversion Functions
	int CharacterToInt(char a_column);
	char IntToCharacter(int a_column);
	int ConvertRowIndex(int a_row);


	
private:
	//Holds all of the data for the entire board.
	vector<vector<char>> m_board;
};

