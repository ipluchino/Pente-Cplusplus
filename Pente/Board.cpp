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
	//Must convert the location's column as a character to its numeric value so it can be located on the board.
	int numericColumn = CharacterToInt(a_column);

	//Must convert the location's row to its correct numeric value since the rows are labeled 1-19 starting from the bottom.
	a_row = ConvertRowIndex(a_row);

	m_board[a_row][numericColumn] = a_pieceColor;
}

void Board::RemoveStone(char a_column, int a_row)
{
	//Must convert the location's column as a character to its numeric value so it can be located on the board.
	int numericColumn = CharacterToInt(a_column);

	//Must convert the location's row to its correct numeric value since the rows are labeled 1-19 starting from the bottom.
	a_row = ConvertRowIndex(a_row);

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
bool Board::IsValidIndices(int a_row, int a_column)
{
	return (a_row >= 0 && a_row <= 18) && (a_column >= 0 && a_column <= 18);
}

//Checks to see whether a board location is empty or not.
bool Board::IsEmptyLocation(char a_column, int a_row)
{
	return m_board[ConvertRowIndex(a_row)][CharacterToInt(a_column)] == '-';
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
	int convertedColumn = CharacterToInt(a_column);
	int convertedRow = ConvertRowIndex(a_row);

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
			if (IsValidIndices(newRow, newCol)) newLocations.push_back({ newRow, newCol });
		}

		//There must be at least 3 valid board spaces going in the current direction being evaluated for a capture to be possible.
		if (newLocations.size() == CAPTURE_DISTANCE)
		{
			if (m_board[newLocations[0][0]][newLocations[0][1]] == opponentColor &&
				m_board[newLocations[1][0]][newLocations[1][1]] == opponentColor &&
				m_board[newLocations[2][0]][newLocations[2][1]] == a_color)
			{
				numCaptures++;

				//Remove the two captured pieces from the board. The first and second row/col pairs of 'newLocations' are the two pieces being captured.
				RemoveStone(IntToCharacter(newLocations[0][1]), ConvertRowIndex(newLocations[0][0]));
				RemoveStone(IntToCharacter(newLocations[1][1]), ConvertRowIndex(newLocations[1][0]));
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

//Returns true if the board is full, false otherwise.
bool Board::IsBoardFull()
{
	//Loop through every piece on the board, and if one is empty the board is not full. Otherwise, it is.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] == '-') return false;
		}
	}
	
	return true;
}

//Returns true if either player has achieved a 5 in a row.
bool Board::FiveConsecutive()
{
	//From every position on the board, every horizontal, vertical, and diagonal needs to be searched.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//Only have to loop through 4 of the directions, since searching opposite directions (left&right, up&down, etc. is redundant)
            //All horizontals are checked with just left, all verticals with just up, etc.
			for (int k = 0; k < NUM_DIRECTIONS; k += DIRECTIONAL_OFFSET)
			{
				int whiteCounter = 0;
				int blackCounter = 0;

				//For each direction, consider the current space and 4 spaces out (to make a consecutive 5).
				for (int l = 0; l < 5; l++)
				{
					int newRow = i + (DIRECTIONS[k][0] * l);
					int newCol = j + (DIRECTIONS[k][1] * l);

					//No need to keep searching if the 5 spaces go out of the board's bounds.
					if (!IsValidIndices(newRow, newCol)) break;

					if (m_board[newRow][newCol] == 'W') whiteCounter++;
					else if (m_board[newRow][newCol] == 'B') blackCounter++;
				}

				if (whiteCounter == 5 || blackCounter == 5) return true;
			}
		}
	}
	
	return false;
}

//Returns the tallied up score of a provided color based on the current board and number of captured pairs they have.
int Board::ScoreBoard(char a_color, int a_numCaptures)
{
	//Holds the overall score for a provided color (a_color).
	int totalScore = 0;

	for (int direction = 0; direction < DIRECTIONS.size(); direction += DIRECTIONAL_OFFSET)
	{
		//The first step in scoring is the find all 5 or more consecutives in each horizontal, vertical, and diagonal.
		//NOTE: There can be multiple 5 or more consecutives in an L shape if the last piece placed connects the L together.

		vector<vector<char>> boardCopy = GetBoard();

		//Loop through every piece and search the current direction for any consecutive 5 or more stones. This is considered a "winning move".
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				int totalConsecutive = 0;
				int row = i;
				int col = j;
				
				//If there is a winning move found in the current direction, it will need to be saved to be marked later.
				vector<vector<int>> seenLocations = {};

				while (IsValidIndices(row, col) && boardCopy[row][col] == a_color) 
				{
					seenLocations.push_back({ row, col });

					totalConsecutive++;

					row += DIRECTIONS[direction][0];
					col += DIRECTIONS[direction][1];
				}

				//If a winning move was found, the player is awarded 5 points.
				if (totalConsecutive >= 5) 
				{
					totalScore += 5;

					//Mark the winning move in this direction as "S" to represent seen. This ensures that the winning move does not also get counted as a consecutive 4.
					for (int k = 0; k < seenLocations.size(); k++) 
					{
						boardCopy[seenLocations[k][0]][seenLocations[k][1]] = 'S';
					}
				}

			}
		}

		//After the "winning move" in the current direction has been found and marked as seen, search for any consecutive 4s in that same direction.
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				int totalConsecutive = 0;

				//Search 3 more spaces out from the current stone.
				for (int k = 0; k <= CONSECUTIVE_4_DISTANCE; k++)
				{
					int row = i + DIRECTIONS[direction][0] * k;
					int col = j + DIRECTIONS[direction][1] * k;

					if (!IsValidIndices(row, col)) break;

					if (boardCopy[row][col] == a_color) totalConsecutive++;
				}

				//If there was a consecutive 4 found, the player is awarded 1 point.
				if (totalConsecutive == 4) totalScore++;
			}
		}
	}

	//Lastly, add 1 point for each captured pair.
	totalScore += a_numCaptures;

	return totalScore;
}

//Clears the entire board.
void Board::ClearBoard()
{
	m_board = vector<vector<char>>(19, vector<char>(19, '-'));
}

//Converts a alphabetical column to its numerical counterpart.
int Board::CharacterToInt(char a_column)
{
	return a_column - 'A';
}

//Converts a numerical column into its alphabetical counterpart.
char Board::IntToCharacter(int a_column)
{
	return a_column + 'A';
}

//Converts a row from its vector index to board view index or vice verca.
int Board::ConvertRowIndex(int a_row)
{
	return 19 - a_row;
}

