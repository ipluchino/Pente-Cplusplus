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

//Determins if a column and row passed is valid within the constraints of the board.
bool Board::IsValidLocation(char a_column, int a_row)
{
	return (a_column >= 'A' && a_column <= 'S') && (a_row >= 1 && a_row <= 19);
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

//Clears captured pieces off the board, and returns the number of captures cleared.
int Board::ClearCaptures(char a_column, int a_row, char a_color)
{
	//Represents the total number of pairs captured after placing a stone at this current location.
	int numCaptures = 0;

	//Represents the color of the opponent's stone.
	char opponentColor = OpponentColor(a_color);
	
	//Represents the numerical representation of the alphabetical column and correctly converted index of the row.
	int convertedColumn = a_column - 'A';
	int convertedRow = 19 - a_row;

	//Must loop through all 8 of the possible directions starting from the location passed since captures can happen in any direction.
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{	
		//For each of the 8 directions, you must go three spaces out to check if a capture has occured.
		//For example, if the color passed was white, a capture follows the pattern * B B W where * is the location passed to this function.
		vector<vector<int>> newLocations = {};

		for (int j = 1; j <= CAPTURE_DISTANCE; j++)
		{
			int newRow = convertedRow + (DIRECTIONS[i][0] * j);
			int newCol = convertedColumn + (DIRECTIONS[i][1] * j);

			//If the location is valid, it must be stored so the pieces there can be removed if it turns out to be a successful capture.
			if (IsValidLocation(newCol + 'A', newRow)) newLocations.push_back({ newRow, newCol });
		}

		//There must be at least 3 valid board spaces going in the current direction being evaluated for a capture to be possible.
		if (newLocations.size() == CAPTURE_DISTANCE)
		{
			cout << DIRECTIONS[i][0] << " " << DIRECTIONS[i][1] << endl;
			//cout << newLocations[0][0] << " " << newLocations[0][1] << endl;
			//cout << newLocations[1][0] << " " << newLocations[1][1] << endl;
			//cout << newLocations[2][0] << " " << newLocations[2][1] << endl << endl;
			
			if (m_board[newLocations[0][0]][newLocations[0][1]] == opponentColor &&
				m_board[newLocations[1][0]][newLocations[1][1]] == opponentColor &&
				m_board[newLocations[2][0]][newLocations[2][1]] == a_color)
			{
				numCaptures++;

				//Remove the two captured pieces from the board.
				char x = newLocations[0][1] + 'A';
				char y = newLocations[1][1] + 'A';
				
				cout << x << " " << 19 - newLocations[0][0] << endl;
				cout << y << " " << 19 - newLocations[1][0] << endl << endl;
				//RemoveStone(newLocations[0][1] + 'A', newLocations[0][0]);
				//RemoveStone(newLocations[1][1] + 'A', newLocations[1][0]);
			}
		}
	}

	return numCaptures;
}

//Given a color, returns the color of the opponent.
char Board::OpponentColor(char a_color)
{
	if (a_color == 'W')
	{
		return 'B';
	}
	else
	{
		return 'W';
	}
}

