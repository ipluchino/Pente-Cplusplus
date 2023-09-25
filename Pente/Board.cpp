/************************************************************
* Name:  Ian Pluchino
* Project : OPL Project 1 C++
* Class : Board class - implementation file.
* Date : 9/27/23
************************************************************/

#include "Board.h"

/* *********************************************************************
Function Name: Board - Default constructor
Purpose: To construct a Board object.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Board::Board() : m_board(vector<vector<char>>(StrategyConstants::BOARD_SIZE, vector<char>(StrategyConstants::BOARD_SIZE, '-')))
{
}

/* *********************************************************************
Function Name: Board - Copy constructor
Purpose: To construct a Board object from an existing one.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
Board::Board(Board& a_otherBoard)
{
	m_board = a_otherBoard.m_board;
}

/* *********************************************************************
Function Name: SetBoard
Purpose: To set the Board object's board information.
Parameters:
			a_board, a vector<vector<char>> representing all of the locations of the board, and what piece (if any) are there.
Return Value: Whether or not the board was successfully set, a boolean value.
Algorithm:
			1) Make sure the board passed to the function is 19x19 in size.
			2) Make sure all of the locations are valid, that is they are either empty, or have white or black pieces on them.
			3) If all is sufficient, set the board.
Assistance Received: None
********************************************************************* */
bool Board::SetBoard(vector<vector<char>> a_board)
{
	//The board must be 19x19 to be considered valid.
	if (a_board.size() != StrategyConstants::BOARD_SIZE) return false;

	for (int i = 0; i < a_board.size(); i++)
	{
		if (a_board[i].size() != StrategyConstants::BOARD_SIZE) return false;
	}

	//The only valid characters for the board are White ('W'), Black ('B'), and empty locations ('-')
	for (int row = 0; row < a_board.size(); row++)
	{
		for (int col = 0; col < a_board.size(); col++)
		{
			if (a_board[row][col] != '-' && a_board[row][col] != 'W' && a_board[row][col] != 'B')
			{
				return false;
			}
		}
	}

	m_board = a_board;

	return true;
}
/* *********************************************************************
Function Name: PlaceStone
Purpose: To place a stone on to the board.
Parameters:
			a_column, a character reperesenting the column on the board to place the stone on.
			a_row, an integer representing the the row on the board to place the stone on.
			a_pieceColor, a character representing the color of the stone to be placed on to the board.
Return Value: Whether or not the stone was successfully placed, a boolean value.
Algorithm:
			1) Make sure the column and row provided are valid in terms of the board size constraints.
			2) Convert the column and row from its board view representation to its vector index representation.
			3) Set the location of the board to be equal to the stone's color.
Assistance Received: None
********************************************************************* */
bool Board::PlaceStone(char a_column, int a_row, char a_pieceColor)
{
	if (a_column < 'A' || a_column > 'S') return false;

	if (a_row < 0 || a_row > 19) return false;
	
	//Must convert the location's column as a character to its numeric value so it can be located on the board.
	int numericColumn = CharacterToInt(a_column);

	//Must convert the location's row to its correct numeric value since the rows are labeled 1-19 starting from the bottom (opposite of index order).
	a_row = ConvertRowIndex(a_row);

	m_board[a_row][numericColumn] = a_pieceColor;

	return true;
}

/* *********************************************************************
Function Name: RemoveStone
Purpose: To remove a stone on the board.
Parameters: 
			a_column, a character reperesenting the column on the board to place the stone on.
			a_row, an integer representing the the row on the board to place the stone on.
Return Value: Whether or not the stone was successfully removed from the board.
Algorithm:
			1) Make sure the column and row provided are valid in terms of the board size constraints.
			2) Convert the column and row from its board view representation to its vector index representation.
			3) Set the location of the board to be empty.
Assistance Received: None
********************************************************************* */
bool Board::RemoveStone(char a_column, int a_row)
{
	if (a_column < 'A' || a_column > 'S') return false;

	if (a_row < 0 || a_row > 19) return false;
	
	//Must convert the location's column as a character to its numeric value so it can be located on the board.
	int numericColumn = CharacterToInt(a_column);

	//Must convert the location's row to its correct numeric value since the rows are labeled 1-19 starting from the bottom.
	a_row = ConvertRowIndex(a_row);

	m_board[a_row][numericColumn] = '-';

	return true;
}

/* *********************************************************************
Function Name: DisplayBoard
Purpose: To display the entire board to the screen.
Parameters: None
Return Value: None
Algorithm:
			1) Print the column headers A-S to the screen.
			2) Loop through each location on the board and print it to the screen.
				2a) Row headers are printed before the board locations for each row.
Assistance Received: None
********************************************************************* */
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
	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		cout << ConvertRowIndex(row) << "   ";
		if (row >= 10) cout << " ";

		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			cout << m_board[row][col] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

/* *********************************************************************
Function Name: IsValidIndices
Purpose: To determine if a row and column are valid within the constraints of the board size.
Parameters:
			a_row, an integer representing a row's vector index on the board.
			a_column, an integer representing a column's vector index on the board. 
Return Value: Whether or not the row and column passed is a valid location on the board, a boolean value.
Algorithm: None
Assistance Received: None
********************************************************************* */
bool Board::IsValidIndices(int a_row, int a_column)
{
	return (a_row >= 0 && a_row <= 18) && (a_column >= 0 && a_column <= 18);
}

/* *********************************************************************
Function Name: IsEmptyLocation
Purpose: To check whether a location on the board is empty or not.
Parameters:
			a_column, a character representing the column of a location on the board.
			a_row, an integer representing  the row of a location on the board.
Return Value: Whether or not the location on the board is empty, a boolean value.
Algorithm:
			1) Convert the passed column and row from its board view representation to its vector index representation.
			2) Return true if the location is empty, false if otherwise.
Assistance Received: None
********************************************************************* */
bool Board::IsEmptyLocation(char a_column, int a_row)
{
	return m_board[ConvertRowIndex(a_row)][CharacterToInt(a_column)] == '-';
}

/* *********************************************************************
Function Name: CountPieces
Purpose: To count the number of pieces on the board that are the color passed.
Parameters:
			a_color, a character representing the color to be counted.
Return Value: The number of pieces on the board, an integer.
Algorithm:
			1) Loop through every location on the board.
				1a) If the location contains a piece of the desired color, increment a running total.
			2) Return the running total.
Assistance Received: None
********************************************************************* */
int Board::CountPieces(char a_color)
{
	int total = 0;

	//Loop through the entire board and count up the number of pieces that are the color passed.
	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			if (m_board[row][col] == a_color)
			{
				total++;
			}
		}
	}

	return total;
}

/* *********************************************************************
Function Name: IsEmptyBoard
Purpose: To determine if the entire board is empty.
Parameters: None
Return Value: Whether or not the board is completely empty, a boolean value. 
Algorithm:
			1) Count the number of pieces on the board for both white and black.
			2) If the number of pieces placed for each color is both zero, the board is empty. If they aren't, the board is not empty.
Assistance Received: None
********************************************************************* */
bool Board::IsEmptyBoard()
{
	return CountPieces('W') == 0 && CountPieces('B') == 0;
}

/* *********************************************************************
Function Name: ClearCaptures
Purpose: To clear the captured pairs off of the board after a stone has been placed.
Parameters:
			a_column, a character representing the column of the stone just placed. 
			a_row, an integer representing the row of the stone was just placed.
			a_color, a character representing the color of the stone just placed.
Return Value: The number of captured pairs removed from the board, an integer.
Algorithm:
			1) Determine the opponent's stone color.
			2) Convert the row and column passed from their board view representation to their vector index representation.
			3) Loop through all eight possible directions.
			4) For each direction, store the locations of three spaces out in the current direction. 
			5) If there are three valid locations in the current direction being evaluated, check to see if a capture has been made. For example, 
			   if the color passed was white, a capture follows the pattern * B B W where * is the location passed to this function.
			6) If there is a capture that has been made in the direction being evaluated, remove the captured pieces from the board and increment a capture counter.
			7) Return the total number of captures that have been made after placing a stone at the location passed to this function.
Assistance Received: None
********************************************************************* */
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
	for (int direction = 0; direction < StrategyConstants::NUM_DIRECTIONS; direction++)
	{	
		//For each of the 8 directions, you must go three spaces out to check if a capture has occured.
		//For example, if the color passed was white, a capture follows the pattern * B B W where * is the location passed to this function.
		vector<vector<int>> newLocations = {};

		for (int distance = 1; distance <= StrategyConstants::CAPTURE_DISTANCE; distance++)
		{
			int newRow = convertedRow + (StrategyConstants::DIRECTIONS[direction][0] * distance);
			int newCol = convertedColumn + (StrategyConstants::DIRECTIONS[direction][1] * distance);

			//If the location is valid, it must be stored so the pieces there can be removed if it turns out to be a successful capture.
			if (IsValidIndices(newRow, newCol)) newLocations.push_back({ newRow, newCol });
		}

		//There must be at least 3 valid board spaces going in the current direction being evaluated for a capture to be possible.
		if (newLocations.size() == StrategyConstants::CAPTURE_DISTANCE)
		{
			if (m_board[newLocations[0][0]][newLocations[0][1]] == opponentColor &&
				m_board[newLocations[1][0]][newLocations[1][1]] == opponentColor &&
				m_board[newLocations[2][0]][newLocations[2][1]] == a_color)
			{
				numCaptures++;

				//Remove the two captured pieces from the board. The first and second row/col pairs of 'newLocations' are the two pieces being captured.
				//The column and row need to be converted to their board view representations when passed to the RemoveStone function.
				RemoveStone(IntToCharacter(newLocations[0][1]), ConvertRowIndex(newLocations[0][0]));
				RemoveStone(IntToCharacter(newLocations[1][1]), ConvertRowIndex(newLocations[1][0]));
			}
		}
	}

	return numCaptures;
}

/* *********************************************************************
Function Name: OpponentColor
Purpose: To determine the stone color of the opponent.
Parameters:
			a_color, a character representing the stone color of the current player.
Return Value: The stone color of the opponent, a character. 
Algorithm:
			1) If the current player's stone color is white, the opponent's stone color must be black.
			2) If the current player's stone color is black, the opponent's stone color must be white.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name: IsBoardFull
Purpose: To determine if the board is full.
Parameters: None
Return Value: Whether or not the board is full, a boolean value.
Algorithm:
			1) Loop through every location on the board.
			2) If any location on the board is empty, the board is not full, otherwise the board is full.
Assistance Received: None
********************************************************************* */
bool Board::IsBoardFull()
{
	//Loop through every piece on the board, and if one is empty the board is not full. Otherwise, it is.
	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			if (m_board[row][col] == '-') return false;
		}
	}
	
	return true;
}

/* *********************************************************************
Function Name: FiveConsecutive
Purpose: To determine if a player has achieved a consecutive five pieces. Used by the Round object to determine if the current round is over.
Parameters:
			a_color, a character representing the color of the stone to check for five consecutive pieces.
Return Value: Whether or not five consecutive pieces has been achieved, a boolean value.
Algorithm:
			1) Loop through every location on the board.
			2) For every location, loop through the four main directions (horizontally, vertically, and both diagonals).
			3) Check the current location and four additional locations out in the current direction being evaluated.
				3a) If any of the locations being evaluated go out of the board's bounds, move on to the next direction.
				3b) If the piece at any of these locations is the color being evaluated, increment a consecutive piece counter.
			4) If the consecutive piece counter is five, return true. Otherwise reset the consecutive counter and continue searching.
			5) If there are no consecutive five pieces found, return false.
Assistance Received: None
********************************************************************* */
bool Board::FiveConsecutive(char a_color)
{
	//From every position on the board, every horizontal, vertical, and diagonal needs to be searched.
	for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
	{
		for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
		{
			//Only have to loop through main directions, since searching opposite directions (left&right, up&down, etc. is redundant)
            //All horizontals are checked with just the left direction, all verticals with just the up direction, and so on.
			for (int direction = 0; direction < StrategyConstants::NUM_DIRECTIONS; direction += StrategyConstants::DIRECTIONAL_OFFSET)
			{
				int consecutiveCounter = 0;

				//For each direction, consider the current space and 4 spaces out (to make a consecutive 5).
				for (int distance = 0; distance < StrategyConstants::CONSECUTIVE_5_DISTANCE; distance++)
				{
					int newRow = row + (StrategyConstants::DIRECTIONS[direction][0] * distance);
					int newCol = col + (StrategyConstants::DIRECTIONS[direction][1] * distance);

					//No need to keep searching if the 5 spaces go out of the board's bounds.
					if (!IsValidIndices(newRow, newCol)) break;

					if (m_board[newRow][newCol] == a_color) consecutiveCounter++;
				}

				if (consecutiveCounter == 5) return true;
			}
		}
	}
	
	return false;
}

/* *********************************************************************
Function Name: ScoreBoard
Purpose: To tally up the score for a provided stone color based on the current board layout and the number of captured pairs they have.
Parameters:
			a_color, a character representing the stone color of the current player being evaluated.
			a_numCaptures, an integer representing the number of captured pairs the current player being evaluated has.
Return Value: The score for the round, an integer.
Algorithm:
			1) Loop through the four main directions (horizontally, vertically, and both diagonals). Create a copy of the board for each direction.
			2) First, check for any consecutive chains of the stone color passed that are five or greater.
				3a) Loop through every location on the board.
				3b) From the current location, continue going to new locations on the board in the current direction being evaluated.
					If the new location is valid and has a stone of the correct color, incremement a consecutive stone counter.
				3c) Stop checking new locations once the new location is either invalid or does not have a stone of the correct color.
				3d) If the consecutive stone counter is greater than or equal to five, add five points to the total score.
					Also, mark these locations as seen on the copied board, so that the consecutive five or more is not recounted as consecutive fours later on.
			3) Next, check for any consecutive chains of the stone color passed that are equal to four.
				3a) Loop through every location on the board.
				3b) From the current location, search three locations out in current direction being evaluated.
					If the new location is valid and has a stone of the correct color, incremement a consecutive stone counter.
				3c) If the consecutive stone counter is equal to four, add one point to the total score.
			4) Add one point for each captured pair the player has. 
			5) Return the overall total score earned for the round.

Assistance Received: None
********************************************************************* */
int Board::ScoreBoard(char a_color, int a_numCaptures)
{
	//Holds the overall score for a provided color (a_color).
	int totalScore = 0;

	for (int direction = 0; direction < StrategyConstants::NUM_DIRECTIONS; direction += StrategyConstants::DIRECTIONAL_OFFSET)
	{
		//The first step in scoring is the find all 5 or more consecutives in each horizontal, vertical, and diagonal.
		//NOTE: There can be multiple 5 or more consecutives in an L shape if the last piece placed connects the L together.
		vector<vector<char>> boardCopy = GetBoard();

		//Loop through every piece and search the current direction for any consecutive 5 or more stones. This is considered a "winning move".
		for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
		{
			for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
			{
				int totalConsecutive = 0;
				int newRow = row;
				int newCol = col;
				
				//If there is a winning move found in the current direction, it will need to be saved to be marked later.
				vector<vector<int>> seenLocations = {};

				while (IsValidIndices(newRow, newCol) && boardCopy[newRow][newCol] == a_color) 
				{
					seenLocations.push_back({ newRow, newCol });

					totalConsecutive++;

					newRow += StrategyConstants::DIRECTIONS[direction][0];
					newCol += StrategyConstants::DIRECTIONS[direction][1];
				}

				//If a winning move was found, the player is awarded 5 points.
				if (totalConsecutive >= 5) 
				{
					totalScore += 5;

					//Mark the winning move in this direction as "S" to represent seen. This ensures that the winning move does not also get counted as a consecutive 4.
					for (int i = 0; i < seenLocations.size(); i++) 
					{
						boardCopy[seenLocations[i][0]][seenLocations[i][1]] = 'S';
					}
				}

			}
		}

		//After the "winning move" in the current direction has been found and marked as seen, search for any consecutive 4s in that same direction.
		for (int row = 0; row < StrategyConstants::BOARD_SIZE; row++)
		{
			for (int col = 0; col < StrategyConstants::BOARD_SIZE; col++)
			{
				int totalConsecutive = 0;

				//Search 3 more spaces out from the current stone.
				for (int distance = 0; distance < StrategyConstants::CONSECUTIVE_4_DISTANCE; distance++)
				{
					int newRow = row + StrategyConstants::DIRECTIONS[direction][0] * distance;
					int newCol = col + StrategyConstants::DIRECTIONS[direction][1] * distance;

					if (!IsValidIndices(newRow, newCol)) break;

					if (boardCopy[newRow][newCol] == a_color) totalConsecutive++;
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

/* *********************************************************************
Function Name: ClearBoard
Purpose: To clear the board and make every location empty.
Parameters: None
Return Value: None
Algorithm: None
Assistance Received: None
********************************************************************* */
void Board::ClearBoard()
{
	m_board = vector<vector<char>>(StrategyConstants::BOARD_SIZE, vector<char>(StrategyConstants::BOARD_SIZE, '-'));
}

/* *********************************************************************
Function Name: CharacterToInt
Purpose: To convert an alphabetical column into its numerical counterpart.
Parameters:
			a_column, a character representing the column to be converted.
Return Value: The converted column, as an integer.
Algorithm: None
Assistance Received: None
********************************************************************* */
int Board::CharacterToInt(char a_column)
{
	return a_column - 'A';
}

/* *********************************************************************
Function Name: IntToCharacter
Purpose: To convert a numerical column into its alphabetical counterpart.
Parameters:
			a_column, an integer representing the column to be converted.
Return Value: The converted column, as a character.
Algorithm: None
Assistance Received: None
********************************************************************* */
char Board::IntToCharacter(int a_column)
{
	return a_column + 'A';
}

/* *********************************************************************
Function Name: ConvertRowIndex
Purpose: To convert a row from its vector index to board view index or vice verca.
Parameters:
			a_row, an integer representing the row to be converted.
Return Value: The row's converted index, an integer.
Algorithm: None
Assistance Received: None
********************************************************************* */
int Board::ConvertRowIndex(int a_row)
{
	return StrategyConstants::BOARD_SIZE - a_row;
}

