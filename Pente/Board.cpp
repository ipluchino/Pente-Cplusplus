#include "Board.h"

//Default Constructor
Board::Board() : m_board(vector<vector<char>>(19, vector<char>(19, '-')))
{
}

/*
//Copy Constructor
Board::Board(const Board& a_board)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			m_board[i][j] = a_board.m_board[i][j];
		}
	}
}

//Copy Assignment
Board& Board::operator=(const Board& a_board)
{
	//Make sure to avoid self assignment.
	if (&a_board != this)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				m_board[i][j] = a_board.m_board[i][j];
			}
		}
	}

	return *this;
}
*/

//Places a stone, given a row, column and color onto the board.
void Board::PlaceStone(char a_column, int a_row, char a_pieceColor)
{
	//PLAY MUST BE VALIDATED BEFORE PLACING (DONE BEFORE IT GETS TO THIS FUNCTION)

	//Must convert the location's column as a character to its numeric value so it can be located on the board.
	int numericColumn = a_column - 'A';

	//Must convert the location's row to its correct numeric value since the rows are labeled 1-19 starting from the bottom.
	a_row = 19 - a_row;

	m_board[a_row][numericColumn] = a_pieceColor;
}

void Board::RemoveStone(char a_column, int a_row)
{
	//REMOVE MUST BE VALIDATED BEFORE REMOVING (DONE BEFORE IT GETS TO THIS FUNCTION)

	//Must convert the location's column as a character to its numeric value so it can be located on the board.
	int numericColumn = a_column - 'A';

	//Must convert the location's row to its correct numeric value since the rows are labeled 1-19 starting from the bottom.
	a_row = 19 - a_row;

	m_board[a_row][numericColumn] = '-';
}

//Displays the entire board to the screen
void Board::DisplayBoard()
{
	//Print the column headers at the top of the board (A-S going from left to right)
	cout << "     ";
	for (char col = 'A'; col <= 'S'; col++)
	{
		cout << col << " ";
	}
	cout << "\n\n";

	//Print the entire board and the row headers to the left of each row (1-19 going from bottom to top)
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << BOARD_SIZE - i << "   ";
		if (i >= 10) cout << " ";

		for (int j = 0; j < BOARD_SIZE; j++) 
		{
			cout << m_board[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

//Checks to see whether a board location is empty or not.
bool Board::IsEmptyLocation(char a_column, int a_row)
{
	return m_board[19 - a_row][a_column - 'A'] == '-';
}

//Counts the number of pieces on the board that corresponds to the color passed.
int Board::CountPieces(char a_color)
{
	int total = 0;

	//Loop through the entire board and count up the number of pieces that are the color passed.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] == a_color)
			{
				total++;
			}
		}
	}

	return total;
}


//Determines if the entire board is empty.
bool Board::IsEmptyBoard()
{
	return CountPieces('W') == 0 && CountPieces('B') == 0;
}
